#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/spi/spi.h>

#include "nrf24_sysfs.h"

static struct test_device{
    struct kobject *kobj_dev;
}tst_dev;


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
static struct attribute_group *attribute_nrfdev[] = {
    &group_rf,
    &group_device_nrf24,
    &group_pipe1,
    &group_pipe2,
    &group_pipe3,
    &group_pipe4,
    &group_pipe5,
    NULL,
};


static const struct of_device_id test_dev_dts_id[] = {
	{ .compatible = "nordic,nrf24" },
	{},
};

MODULE_DEVICE_TABLE(of, test_dev_dts_id);

static int test_dev_probe(struct spi_device *spi)
{
    int ret;
    uint8_t *test_data= 0;
    test_data = vmalloc(1);
    dev_info(&spi->dev, "%s: Probe test device\r\n", __func__);
    *test_data = 26;
    dev_set_drvdata(&spi->dev, test_data);
    ret = sysfs_create_groups(&spi->dev.kobj, (const struct attribute_group **)attribute_nrfdev);
    if(ret) 
    {
        dev_err(&spi->dev, "%s: Failed to create system file  group\r\n", __func__);
        return -1;
    }
    return 0; 
}

static int test_dev_remove(struct spi_device *spi)
{
    uint8_t *test_data = dev_get_drvdata(&spi->dev);
    dev_info(&spi->dev, "%s: Remove test device\r\n", __func__);
    sysfs_remove_groups(&spi->dev.kobj, (const struct attribute_group **)attribute_nrfdev);
    vfree(test_data);
    return 0;
}

static  struct spi_driver test_spi_driver = {
	.driver = {
		.name = "nrf24l01_net",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(test_dev_dts_id),
	},
	.probe = test_dev_probe,
	.remove = test_dev_remove,
};

#define USING_DTS 1
static int __init test_dev_init(void)
{
    int ret;
    printk(KERN_INFO "%s: Init Test device kernel\r\n", __func__);
#if USING_DTS
    spi_register_driver(&test_spi_driver);
#else
    tst_dev.kobj_dev = kobject_create_and_add("kobject_example", kernel_kobj);
    if(!tst_dev.kobj_dev)
    {
        printk(KERN_ERR "%s: Failed to create kobject\r\n", __func__);
        return -1;
    }
    
    ret = sysfs_create_groups(tst_dev.kobj_dev, (const struct attribute_group **)attribute_nrfdev);
    if(ret) 
    {
        printk(KERN_ERR "%s: Failed to create system file  group\r\n", __func__);
        return -1;
    }
#endif
    return 0;
}

static void __exit test_dev_exit(void)
{
    printk(KERN_INFO "%s: Exit Test device Kernel\r\n", __func__);
#if USING_DTS
    spi_unregister_driver(&test_spi_driver);
#else
    if(!tst_dev.kobj_dev) 
    {
      sysfs_remove_groups(tst_dev.kobj_dev, (const struct attribute_group **)attribute_nrfdev);
      kobject_put(tst_dev.kobj_dev);
    }
#endif
}

module_init(test_dev_init);
module_exit(test_dev_exit);

MODULE_AUTHOR("Pham Tuan Anh <lambogini1992@gmail.com>");
MODULE_DESCRIPTION("Driver for nrf24_net+");
MODULE_LICENSE("GPL");
