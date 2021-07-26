#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/device.h>

#include "nrf24_sysfs.h"

const uint8_t data_rate_transmit[][10] =
{
    "250 Kbps",
    "1 Mbps",
    "2 Mbps"
};

const uint8_t power_transmit_data[][12] =
{
    "-18dBm",
    "-12dBm",
    "-6dBm",
    "0dBm"
};

const uint8_t auto_retransmit_delay_us[][10] =
{
    "250",
    "500",
    "750",
    "1000",
    "1250",
    "1500",
    "1750",
    "2000",
    "2250",
    "2500",
    "2750",
    "3000",
    "3250",
    "3500",
    "3750",
    "4000",
};

static ssize_t nrf24l01_sysfs_show_address_for_pipe(char* buf, int pipe_idx)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}


//Because, PIPE 0 and TX have same address
ssize_t nrf24l01_sysfs_show_address_device(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 0);
}

ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 1);
}

ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 2);
}

ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 3);
}

ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 4);
}

ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_sysfs_show_address_for_pipe(buf, 5);
}

static ssize_t nrf24l01_sysfs_store_address_for_pipe(const char* buf, int pipe_idx)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

ssize_t nrf24l01_sysfs_store_address_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 0);
}

ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 1);
}

ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 2);
}

ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 3);
}

ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 4);
}

ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_sysfs_store_address_for_pipe(buf, 5);
}

static ssize_t nrf24l01_show_payload_width_for_pipe(uint8_t pipe_idx, char* buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

static ssize_t nrf24l01_store_payload_width_for_pipe(uint8_t pipe_idx, const char* buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

ssize_t nrf24l01_sysfs_store_payload_width_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_payload_width_for_pipe(5, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_device(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_payload_width_for_pipe(5, buf);
}

static ssize_t nrf24l01_show_active_status_for_pipe(uint8_t pipe_idx, char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

static ssize_t nrf24l01_store_active_status_for_pipe(uint8_t pipe_idx, const char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

ssize_t nrf24l01_sysfs_show_status_active_device(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_show_status_active_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_show_status_active_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_show_status_active_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_show_status_active_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_show_status_active_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_active_status_for_pipe(5, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_store_status_active_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_active_status_for_pipe(5, buf);
}

static ssize_t nrf24l01_set_dynamic_payload_for_pipe(uint8_t pipe_idx, const char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

static ssize_t nrf24l01_show_dynamic_payload_status_of_pipe(uint8_t pipe_idx, char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}


ssize_t nrf24l01_sysfs_store_status_dynamic_payload_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_set_dynamic_payload_for_pipe(5, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_device(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_show_dynamic_payload_status_of_pipe(5, buf);
}

static ssize_t nrf24l01_store_auto_ack_for_pipe(uint8_t pipe_idx, const char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

static ssize_t nrf24l01_get_auto_ack_for_pipe(uint8_t pipe_idx, char *buf)
{
    printk("%s for pipe %d\r\n", __func__, pipe_idx);
    return 1;
}

ssize_t nrf24l01_sysfs_show_auto_ack_device(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_show_auto_ack_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_show_auto_ack_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_show_auto_ack_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_show_auto_ack_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_show_auto_ack_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
    return nrf24l01_get_auto_ack_for_pipe(5, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(0, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(1, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(2, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(3, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(4, buf);
}

ssize_t nrf24l01_sysfs_store_auto_ack_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    return nrf24l01_store_auto_ack_for_pipe(5, buf);
}


//--This is device data--//
ssize_t nrf24l01_sysfs_store_address_width(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_address_width(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_pwr_mode(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}


ssize_t nrf24l01_sysfs_store_pwr_mode(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_data_rate(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_store_data_rate(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}


ssize_t nrf24l01_sysfs_store_crc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_crc(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_store_autoretransmit_delay(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_autoretransmit_delay(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_store_autoretransmit_count(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_autoretransmit_count(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_store_transmit_power(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{    
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_transmit_power(struct device* dev, struct device_attribute* attr, char* buf)
{    
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    uint8_t *test_data = dev_get_drvdata(dev);
    printk("%s for device test_data %d\r\n", __func__, *test_data);
    return 1;
}

#if 0
static DEVICE_ATTR(trasnmit_power, 0644, nrf24l01_sysfs_show_transmit_power, nrf24l01_sysfs_store_transmit_power);
static DEVICE_ATTR(auto_retransmit_count, 0644, nrf24l01_sysfs_show_autoretransmit_count, nrf24l01_sysfs_store_autoretransmit_count);
static DEVICE_ATTR(auto_retransmit_delay, 0644, nrf24l01_sysfs_show_autoretransmit_delay, nrf24l01_sysfs_store_autoretransmit_delay);
static DEVICE_ATTR(crc_encoder, 0644, nrf24l01_sysfs_show_crc, nrf24l01_sysfs_store_crc);
static DEVICE_ATTR(data_rate, 0644, nrf24l01_sysfs_show_data_rate, nrf24l01_sysfs_store_data_rate);
static DEVICE_ATTR(power_mode, 0644, nrf24l01_sysfs_show_pwr_mode, nrf24l01_sysfs_store_pwr_mode);
static DEVICE_ATTR(address_witdh, 0644, nrf24l01_sysfs_show_address_width, nrf24l01_sysfs_store_address_width);
static DEVICE_ATTR(rf_channel, 0644, nrf24l01_sysfs_show_channel, nrf24l01_sysfs_store_channel);

static struct attribute* attr_rf_dev[] = {
	&dev_attr_trasnmit_power.attr,
    &dev_attr_auto_retransmit_count.attr,
    &dev_attr_auto_retransmit_delay.attr,
    &dev_attr_crc_encoder.attr,
    &dev_attr_data_rate.attr,
    &dev_attr_power_mode.attr,
    &dev_attr_address_witdh.attr,
    &dev_attr_rf_channel.attr,
	NULL
};

static struct attribute_group group_rf = {
	.attrs = attr_rf_dev,
	.name = "rf_device"
};

/* Attribute of Device NRF24L01*/
static DEVICE_ATTR(dev_address, 0644, nrf24l01_sysfs_show_address_device, nrf24l01_sysfs_store_address_device);
static DEVICE_ATTR(dev_payload_width, 0644, nrf24l01_sysfs_show_payload_width_device, nrf24l01_sysfs_store_payload_width_device);
static DEVICE_ATTR(dev_active, 0644, nrf24l01_sysfs_show_status_active_device, nrf24l01_sysfs_store_status_active_device);
static DEVICE_ATTR(dev_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_device, nrf24l01_sysfs_store_status_dynamic_payload_device);
static DEVICE_ATTR(dev_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_device, nrf24l01_sysfs_store_auto_ack_device);

static struct attribute* attr_device_nrf24[] = {
	&dev_attr_dev_address.attr,
    &dev_attr_dev_payload_width.attr,
    &dev_attr_dev_active.attr,
    &dev_attr_dev_payload_dynamic.attr,
    &dev_attr_dev_auto_ack.attr,
	NULL
};

static struct attribute_group group_device_nrf24 = {
	.attrs = attr_device_nrf24,
	.name = "device_nrf24"
};

/* Attribute of Device NRF24L01 PIPE1*/
static DEVICE_ATTR(pipe1_address, 0644, nrf24l01_sysfs_show_address_pipe1, nrf24l01_sysfs_store_address_pipe1);
static DEVICE_ATTR(pipe1_payload_width, 0644, nrf24l01_sysfs_show_payload_width_pipe1, nrf24l01_sysfs_store_payload_width_pipe1);
static DEVICE_ATTR(pipe1_active, 0644, nrf24l01_sysfs_show_status_active_pipe1, nrf24l01_sysfs_store_status_active_pipe1);
static DEVICE_ATTR(pipe1_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_pipe1, nrf24l01_sysfs_store_status_dynamic_payload_pipe1);
static DEVICE_ATTR(pipe1_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_pipe1, nrf24l01_sysfs_store_auto_ack_pipe1);

static struct attribute* attr_pipe1[] = {
	&dev_attr_pipe1_address.attr,
    &dev_attr_pipe1_payload_width.attr,
    &dev_attr_pipe1_active.attr,
    &dev_attr_pipe1_payload_dynamic.attr,
    &dev_attr_pipe1_auto_ack.attr,
	NULL
};

static struct attribute_group group_pipe1 = {
	.attrs = attr_pipe1,
	.name = "pipe1"
};

/* Attribute of Device NRF24L01 PIPE2*/
static DEVICE_ATTR(pipe2_address, 0644, nrf24l01_sysfs_show_address_pipe2, nrf24l01_sysfs_store_address_pipe2);
static DEVICE_ATTR(pipe2_payload_width, 0644, nrf24l01_sysfs_show_payload_width_pipe2, nrf24l01_sysfs_store_payload_width_pipe2);
static DEVICE_ATTR(pipe2_active, 0644, nrf24l01_sysfs_show_status_active_pipe2, nrf24l01_sysfs_store_status_active_pipe2);
static DEVICE_ATTR(pipe2_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_pipe2, nrf24l01_sysfs_store_status_dynamic_payload_pipe2);
static DEVICE_ATTR(pipe2_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_pipe2, nrf24l01_sysfs_store_auto_ack_pipe2);

static struct attribute* attr_pipe2[] = {
	&dev_attr_pipe2_address.attr,
    &dev_attr_pipe2_payload_width.attr,
    &dev_attr_pipe2_active.attr,
    &dev_attr_pipe2_payload_dynamic.attr,
    &dev_attr_pipe2_auto_ack.attr,
	NULL
};

static struct attribute_group group_pipe2 = {
	.attrs = attr_pipe2,
	.name = "pipe2"
};

/* Attribute of Device NRF24L01 PIPE3*/
static DEVICE_ATTR(pipe3_address, 0644, nrf24l01_sysfs_show_address_pipe3, nrf24l01_sysfs_store_address_pipe3);
static DEVICE_ATTR(pipe3_payload_width, 0644, nrf24l01_sysfs_show_payload_width_pipe3, nrf24l01_sysfs_store_payload_width_pipe3);
static DEVICE_ATTR(pipe3_active, 0644, nrf24l01_sysfs_show_status_active_pipe3, nrf24l01_sysfs_store_status_active_pipe3);
static DEVICE_ATTR(pipe3_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_pipe3, nrf24l01_sysfs_store_status_dynamic_payload_pipe3);
static DEVICE_ATTR(pipe3_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_pipe3, nrf24l01_sysfs_store_auto_ack_pipe3);

static struct attribute* attr_pipe3[] = {
	&dev_attr_pipe3_address.attr,
    &dev_attr_pipe3_payload_width.attr,
    &dev_attr_pipe3_active.attr,
    &dev_attr_pipe3_payload_dynamic.attr,
    &dev_attr_pipe3_auto_ack.attr,
	NULL
};

static struct attribute_group group_pipe3 = {
	.attrs = attr_pipe3,
	.name = "pipe3"
};

/* Attribute of Device NRF24L01 PIPE4*/
static DEVICE_ATTR(pipe4_address, 0644, nrf24l01_sysfs_show_address_pipe4, nrf24l01_sysfs_store_address_pipe4);
static DEVICE_ATTR(pipe4_payload_width, 0644, nrf24l01_sysfs_show_payload_width_pipe4, nrf24l01_sysfs_store_payload_width_pipe4);
static DEVICE_ATTR(pipe4_active, 0644, nrf24l01_sysfs_show_status_active_pipe4, nrf24l01_sysfs_store_status_active_pipe4);
static DEVICE_ATTR(pipe4_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_pipe4, nrf24l01_sysfs_store_status_dynamic_payload_pipe4);
static DEVICE_ATTR(pipe4_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_pipe4, nrf24l01_sysfs_store_auto_ack_pipe4);

static struct attribute* attr_pipe4[] = {
	&dev_attr_pipe4_address.attr,
    &dev_attr_pipe4_payload_width.attr,
    &dev_attr_pipe4_active.attr,
    &dev_attr_pipe4_payload_dynamic.attr,
    &dev_attr_pipe4_auto_ack.attr,
	NULL
};

static struct attribute_group group_pipe4 = {
	.attrs = attr_pipe4,
	.name = "pipe4"
};

/* Attribute of Device NRF24L01 PIPE5*/
static DEVICE_ATTR(pipe5_address, 0644, nrf24l01_sysfs_show_address_pipe5, nrf24l01_sysfs_store_address_pipe5);
static DEVICE_ATTR(pipe5_payload_width, 0644, nrf24l01_sysfs_show_payload_width_pipe5, nrf24l01_sysfs_store_payload_width_pipe5);
static DEVICE_ATTR(pipe5_active, 0644, nrf24l01_sysfs_show_status_active_pipe5, nrf24l01_sysfs_store_status_active_pipe5);
static DEVICE_ATTR(pipe5_payload_dynamic, 0644, nrf24l01_sysfs_show_status_dynamic_payload_pipe5, nrf24l01_sysfs_store_status_dynamic_payload_pipe5);
static DEVICE_ATTR(pipe5_auto_ack, 0644, nrf24l01_sysfs_show_auto_ack_pipe5, nrf24l01_sysfs_store_auto_ack_pipe5);

static struct attribute* attr_pipe5[] = {
	&dev_attr_pipe5_address.attr,
    &dev_attr_pipe5_payload_width.attr,
    &dev_attr_pipe5_active.attr,
    &dev_attr_pipe5_payload_dynamic.attr,
    &dev_attr_pipe5_auto_ack.attr,
	NULL
};

static struct attribute_group group_pipe5 = {
	.attrs = attr_pipe5,
	.name = "pipe5"
};

/* General Attribute*/
const struct attribute_group* attribute_groups[] = {
    &group_rf,
    &group_device_nrf24,
    &group_pipe1,
    &group_pipe2,
    &group_pipe3,
    &group_pipe4,
    &group_pipe5,
    NULL,
};
#endif