#ifndef _NRF24_SYSFS_H_
#define _NRF24_SYSFS_H_

#include <linux/device.h>

ssize_t nrf24l01_sysfs_show_address_device(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf);

ssize_t nrf24l01_sysfs_store_address_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

ssize_t nrf24l01_sysfs_store_payload_width_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

ssize_t nrf24l01_sysfs_show_payload_width_device(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf);

ssize_t nrf24l01_sysfs_show_status_active_device(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_active_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_active_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_active_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_active_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_active_pipe5(struct device* dev, struct device_attribute* attr, char* buf);

ssize_t nrf24l01_sysfs_store_status_active_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_active_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_active_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_active_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_active_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_active_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

ssize_t nrf24l01_sysfs_store_status_dynamic_payload_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_status_dynamic_payload_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

ssize_t nrf24l01_sysfs_show_status_dynamic_payload_device(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_status_dynamic_payload_pipe5(struct device* dev, struct device_attribute* attr, char* buf);

ssize_t nrf24l01_sysfs_show_auto_ack_device(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_auto_ack_pipe1(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_auto_ack_pipe2(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_auto_ack_pipe3(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_auto_ack_pipe4(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_auto_ack_pipe5(struct device* dev, struct device_attribute* attr, char* buf);

ssize_t nrf24l01_sysfs_store_auto_ack_device(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_auto_ack_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_auto_ack_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_auto_ack_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_auto_ack_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_auto_ack_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);

ssize_t nrf24l01_sysfs_store_address_width(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_address_width(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_pwr_mode(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_pwr_mode(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_data_rate(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_data_rate(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_store_crc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_crc(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_autoretransmit_delay(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_autoretransmit_delay(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_autoretransmit_count(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_autoretransmit_count(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_transmit_power(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);
ssize_t nrf24l01_sysfs_show_transmit_power(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf);
ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count);



#endif