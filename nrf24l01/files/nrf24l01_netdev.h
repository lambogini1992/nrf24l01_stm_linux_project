#ifndef _NRF24L01_NETDEV_H_
#define _NRF24L01_NETDEV_H_


#include <net/mac802154.h>
#include "nrf24l01_core.h"

#define NRF24L01_TIMEOUT_TRANSFER		(3)//Time of check to change PTX-PRX and timer change

extern const struct ieee802154_ops nrf24l01_hw_ops;

int nrf24l01_netdeviceregister(struct ieee802154_hw *net_hw, struct spi_device *spi);
void nrf24_netdeinit(struct spi_device *spi);


void nrf24l01_ieee_tx_complete(struct spi_device *spidev);


#endif //_NRF24L01_NETDEV_H_
