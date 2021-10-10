#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */
#include <linux/of.h>
#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>
#include <linux/spi/spi.h>
#include <linux/of_net.h>
#include <linux/of_device.h>
#include <net/mac802154.h>

#include "nrf24l01_netdev.h"
#include "nrf24l01_core.h"
#include "nrf24l01_functions.h"

#define NRF24L01_MAX_PLAYLOAD_LEN			(32)
static struct mutex nrf24l01_net_mutex;

static int32_t nrf24l01_pwr_tx[] =
{
	-18, -12, -6, 0
};

static uint8_t nrf24l01_txpwr_map(s32 txpwr_input)
{
	uint8_t idx;

	for(idx = 0; idx < sizeof(nrf24l01_pwr_tx); idx++)
	{
		if(nrf24l01_pwr_tx[idx]  == txpwr_input) return idx;
	}
	return 0xFF;
}

static int
nrf24l01_ieee_set_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct nrf24l01_t *nrfdev = hw->priv;
	struct spi_device *spidev = nrfdev->spi;
	int ret;
	dev_info(&spidev->dev, "%s\r\n", __func__);

	//Check channel is valid or not
	if(channel > 0x7F)
	{
		dev_err(&spidev->dev, "%s Setting channel value is invalid\r\n", __func__);
		ret = -EINVAL;
		return ret;
	}

	ret = nrf24l01_set_channel(nrfdev, channel);
	if(ret)
	{
		dev_err(&spidev->dev, "%s: failed to set channel communication to device\r\n", __func__);
		return ret;
	}

	return 0;
}

static int
nrf24l01_ieee_set_txpower(struct ieee802154_hw *hw, s32 mbm)
{
	struct nrf24l01_t *nrfdev = hw->priv;
	struct spi_device *spidev = nrfdev->spi;
	s32 dbm = mbm/100;//conver mbm to dbm
	uint8_t txpwr_cfg = nrf24l01_txpwr_map(dbm);
	int ret;
	dev_info(&spidev->dev, "%s\r\n", __func__);

	if(txpwr_cfg ==  0xFF)
	{
		dev_err(&spidev->dev, "%s Setting tx power value is invalid\r\n", __func__);
		ret = -EINVAL;
		return ret;
	}

	ret = nrf24l01_set_tx_power(nrfdev, txpwr_cfg);
	if(ret)
	{
		dev_err(&spidev->dev, "%s: failed to set tx power\r\n", __func__);
		ret = -EINVAL;
		return ret;
	}

	return 0;
}

static int
nrf24l01_ieee_rx_complete(struct ieee802154_hw *hw)
{
	struct nrf24l01_t *nrfdev = hw->priv;
	struct spi_device *spidev = nrfdev->spi;
	struct sk_buff *skb;
	int err;
	uint8_t *rx_pkt_data;
	size_t rx_pkt_len;

	skb = dev_alloc_skb(IEEE802154_MTU);
	if (!skb) {
		err = -ENOMEM;
		dev_err(&spidev->dev,"%s: driver is out of memory\n", __func__);
		goto nrf24l01_ieee_rx_err;
	}

	rx_pkt_len = 32 + 2;
	err = nrf24l01_read_packet(nrfdev, nrfdev->rx_data_dry, rx_pkt_data, rx_pkt_len);
	if(err)
	{
		dev_err(&spidev->dev, "%s: Failed to read data format from nrf24l01 device\r\n", __func__);
		err = -EINVAL;
		goto nrf24l01_ieee_rx_err;
	}
	memcpy(skb_put(skb, rx_pkt_len), rx_pkt_data, rx_pkt_len);
	//Because, nrf24l01  prx packet dosen't have RSSI parameter
	dev_info(&spidev->dev, "%s: Public rx packet\r\n", __func__);
	ieee802154_rx_irqsafe(hw, skb, 1);

	err = 0;
nrf24l01_ieee_rx_err:
	return err;
}

void nrf24l01_ieee_tx_complete(struct spi_device *spidev)
{
	struct nrf24l01_t *nrfdev = dev_get_drvdata(&spidev->dev);
	struct ieee802154_hw *hw = nrfdev->nethw;
	struct sk_buff *skb = nrfdev->txskb;

	dev_dbg(&spidev->dev, "%s\n", __func__);

	ieee802154_xmit_complete(hw, skb, false);

}

static int
nrf24l01_ieee_xmit(struct ieee802154_hw *hw, struct sk_buff *skb)
{
	struct nrf24l01_t *nrfdev = hw->priv;
	struct spi_device *spidev = nrfdev->spi;
	uint8_t *tx_pkt_data;
	uint8_t tx_pkt_len;
	uint8_t get_offset;
	int ret;

	dev_dbg(&spidev->dev, "%s\n", __func__);
	nrfdev->txskb = skb;
	get_offset = 0;
	tx_pkt_len = skb->data_len;
	while(tx_pkt_len)
	{
		if(tx_pkt_len > NRF24L01_MAX_PLAYLOAD_LEN)
		{
			tx_pkt_data = kzalloc(NRF24L01_MAX_PLAYLOAD_LEN, GFP_KERNEL);
			tx_pkt_len -= NRF24L01_MAX_PLAYLOAD_LEN;
			memcpy(tx_pkt_data, skb->data + get_offset, NRF24L01_MAX_PLAYLOAD_LEN);	
		}
		else
		{
			tx_pkt_data = kzalloc(tx_pkt_len, GFP_KERNEL);
			tx_pkt_len = 0;
			memcpy(tx_pkt_data, skb->data + get_offset, NRF24L01_MAX_PLAYLOAD_LEN);
		}
		ret = nrf24l01_send_packet(nrfdev, nrfdev->tx_fifo_dry, tx_pkt_data, tx_pkt_len);
		if(ret)
		{
			dev_err(&spidev->dev, "%s: failed for sending data to nrf24l01 device\r\n", __func__);
			goto err_write_data_device;
		}
		get_offset +=NRF24L01_MAX_PLAYLOAD_LEN;
		kfree(tx_pkt_data);
	}
err_write_data_device:
	return ret;
}

static int
nrf24l01_ieee_start(struct ieee802154_hw *hw)
{
	struct nrf24l01_t *phy = hw->priv;
	struct spi_device *spi = phy->spi;
	int ret;
	dev_dbg(&spi->dev, "interface up\n");


	if(phy->shutdown)
	{
		ret = -ESHUTDOWN;
		dev_err(&spi->dev, "%s: NRF24L01 Device is Shutdown\r\n", __func__);
		return ret;
	}

	nrf24l01_ieee_set_channel(hw, 0, hw->phy->current_channel);
	return 0;
}

static void
nrf24l01_ieee_stop(struct ieee802154_hw *hw)
{
	struct nrf24l01_t *phy = hw->priv;
	struct spi_device *spi = phy->spi;

	dev_info(&spi->dev, "%s:interface down\r\n", __func__);
}

//If we not implement this src, we will fail ieee802154_alloc_hw
static int nrf24l01_ieee_ed(struct ieee802154_hw *hw, u8 *level)
{
	struct nrf24l01_t *phy = hw->priv;
	struct spi_device *spi = phy->spi;

	dev_info(&spi->dev, "%s:Because nrf24l01 dosen't have detect rssi\r\n", __func__);
}

static int
nrf24l01_ieee_set_promiscuous_mode(struct ieee802154_hw *hw, const bool on)
{
	return 0;
}


const struct ieee802154_ops nrf24l01_hw_ops = {
	.owner = THIS_MODULE,
	.xmit_async = nrf24l01_ieee_xmit,// Must have this function for allocate HW network memory success
	.set_channel = nrf24l01_ieee_set_channel,// Must have this function for allocate HW network memory success
	.set_txpower = nrf24l01_ieee_set_txpower,// Must have this function for allocate HW network memory success
	.start = nrf24l01_ieee_start,// Must have this function for allocate HW network memory success
	.stop = nrf24l01_ieee_stop,// Must have this function for allocate HW network memory success
	.ed   = nrf24l01_ieee_ed,// Must have this function for allocate HW network memory success
	.set_promiscuous_mode = nrf24l01_ieee_set_promiscuous_mode,
};



static void nrf24l01_rx_workstruct(struct work_struct *work)
{
	struct nrf24l01_t *priv;
	struct ieee802154_hw *hw;
	int ret;
	printk(KERN_INFO "%s\n", __func__);
	priv = container_of(work, struct nrf24l01_t, rx_workstruct);
	if(priv)
	{
		hw = priv->nethw;
		ret = nrf24l01_ieee_rx_complete(hw);
		if(ret)
		{
			dev_err(&priv->spi->dev, "%s: failed to public rx packet\r\n", __func__);
		}
	}
}

int nrf24l01_netdeviceregister(struct ieee802154_hw *net_hw, struct spi_device *spi)
{
	nrf24l01_struct_t *nrf_dev = net_hw->priv;
	int ret;
	unsigned int channel;

	dev_info(&spi->dev, "%s: Start\r\n", __func__);

	ret = nrf24l01_get_channel(nrf_dev, &channel);
	net_hw->phy->supported.channels[0] = &channel;
	/* nrf24l01 phy channel get as default */
	net_hw->phy->current_channel = channel;

	/* Define RF power. */
	net_hw->phy->supported.tx_powers = nrf24l01_pwr_tx;
	net_hw->phy->supported.tx_powers_size = ARRAY_SIZE(nrf24l01_pwr_tx);
	net_hw->phy->transmit_power = nrf24l01_pwr_tx[0];

	ieee802154_random_extended_addr(&net_hw->phy->perm_extended_addr);
	net_hw->flags = IEEE802154_HW_TX_OMIT_CKSUM
				  | IEEE802154_HW_RX_OMIT_CKSUM
				  | IEEE802154_HW_PROMISCUOUS;

	dev_info(&spi->dev,  "%s: Function Initialize Success\r\n", __func__);
	mutex_init(&nrf24l01_net_mutex);
	nrf_dev->rx_data_dry = false;
	nrf_dev->tx_fifo_dry = false;
	nrf_dev->shutdown = false;
	INIT_WORK(&nrf_dev->rx_workstruct, nrf24l01_rx_workstruct);

	ret  = ieee802154_register_hw(net_hw);
	if(ret)
	{
		dev_err(&spi->dev,  "%s: failed to register network  device\r\n", __func__);
		goto err_return_null_pointer;
	}

	dev_info(&spi->dev, "%s: Net device initialize and register success\r\n", __func__);
	return 0;
err_return_null_pointer:
	return ret;;
}

void nrf24_netdeinit(struct spi_device *spi)
{
	nrf24l01_struct_t *nrf_dev = dev_get_drvdata(&spi->dev);
	struct ieee802154_hw *net_hw;
	net_hw = nrf_dev->nethw;
	ieee802154_unregister_hw(net_hw);
	ieee802154_free_hw(net_hw);
}