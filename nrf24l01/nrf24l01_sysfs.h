#ifndef _NRF24L01_SYSFS_H_
#define _NRF24L01_SYSFS_H_

#include <linux/device.h>


#if 0
ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_address_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_address_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_payload_width_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_payload_width_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_enable_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enable_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_enable_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enable_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_dynpd_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_dynpd_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_dynpd_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_dynpd_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_enaa_pipe0(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_enaa_pipe5(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_enaa_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_enaa_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_addr_width(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_addr_width(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_pwr_up(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_pwr_up(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_dr(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_dr(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_ce(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_ce(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_crc(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_crc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_tx_address(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_tx_address(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_retr_ard(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_retr_ard(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_retr_arc(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_retr_arc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_tx_pwr(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_tx_pwr(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
#endif

int nrf24l01_sysfscreate(struct spi_device *spidev);
void nrf24l01_sysfsdetroy(struct spi_device *spidev);

#endif
