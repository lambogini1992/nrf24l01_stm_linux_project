#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/device.h>

#include "nrf24l01_core.h"
#include "nrf24l01_functions.h"
#include "nrf24l01_sysfs.h"

static char* nrf24l01_sanitize_string(const char* data, size_t len)
{
	char* str = vzalloc(len + 1);
	if(!str)
		return str;
	memcpy(str, data, len);
	return str;
}

ssize_t nrf24l01_sysfs_show_channel(struct device* dev, struct device_attribute* attr, char* buf)
{
	unsigned int channel;
	int err;
	nrf24l01_struct_t *nrf = dev_get_drvdata(dev);
	if((err = nrf24l01_get_channel(nrf, &channel)))
		return err;
	return sprintf(buf, "%d\n", channel);
}

ssize_t nrf24l01_sysfs_store_channel(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	unsigned int channel;
	ssize_t err;
	nrf24l01_struct_t *nrf = dev_get_drvdata(dev);
	char* buff = nrf24l01_sanitize_string(buf, count);
	if(!buff)
		return -ENOMEM;
	if((err = kstrtouint(buff, 10, &channel)))
		goto exit_buffalloc;
	err = nrf24l01_set_channel(nrf, channel);	
	if(err)
		goto exit_buffalloc;
	return count;
exit_buffalloc:
	vfree(buff);
	return err;
}

static ssize_t nrf24l01_sysfs_show_address(struct device* dev, char* buf, unsigned int pipe)
{
	int err;
	unsigned int addr_width;
	u64 addr = 0;
	char fmt[10];
	struct nrf24l01_t* nrf = dev_get_drvdata(dev);
	if((err = nrf24l01_get_address_u64(nrf, &addr, pipe)))
		return err;
	if(pipe <= 1)
	{
		if((err = nrf24l01_get_address_width(nrf, &addr_width)))
			return err;
		sprintf(fmt, "%%0%ullX\n", addr_width * 2);
		return sprintf(buf, fmt, addr);
	}
	else
		return sprintf(buf, "%02llX\n", addr);
}

ssize_t nrf24l01_sysfs_show_address_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_address_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_address_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_address_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_address_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_address_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_address(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_address(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	u64 addr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));

	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtou64(str, 16, &addr))) 
		goto exit_stralloc;

	if((err = nrf24l01_set_address_u64(nrf, addr, pipe))) 
		goto exit_stralloc;

	err = count;

exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_address_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_address_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_address_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_address_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_address_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_address_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_address(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_payload_width(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int width;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_pipe_pld_width(nrf, pipe, &width)))
		goto exit_err;
	return sprintf(buf, "%u\n", width);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_payload_width_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_payload_width(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_payload_width(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int width;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &width)))
		goto exit_stralloc;
	if((err = nrf24l01_set_pipe_pld_width(nrf, pipe, width)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_payload_width_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_payload_width(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_enable(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_en_rxaddr(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_enable_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_enable_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_enable_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_enable_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_enable_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_enable_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enable(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_enable(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_en_rxaddr(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_enable_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_enable_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_enable_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_enable_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_enable_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_enable_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enable(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_dynpd(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_dynpd(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_dynpd_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_dynpd(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_dynpd(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_dynpd(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_dynpd_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_dynpd(dev, buf, count, 5);
}

static ssize_t nrf24l01_sysfs_show_enaa(struct device* dev, char* buf, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_enaa(nrf, pipe, &state)))
		goto exit_err;
	return sprintf(buf, "%u\n", state);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_enaa_pipe0(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 0);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe1(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 1);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe2(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 2);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe3(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 3);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe4(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 4);
}

ssize_t nrf24l01_sysfs_show_enaa_pipe5(struct device* dev, struct device_attribute* attr, char* buf)
{
	return nrf24l01_sysfs_show_enaa(dev, buf, 5);
}

static ssize_t nrf24l01_sysfs_store_enaa(struct device* dev, const char* buf, size_t count, unsigned int pipe)
{
	ssize_t err;
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &state)))
		goto exit_stralloc;
	if((err = nrf24l01_set_enaa(nrf, pipe, state)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_enaa_pipe0(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 0);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe1(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 1);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe2(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 2);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe3(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 3);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe4(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 4);
}

ssize_t nrf24l01_sysfs_store_enaa_pipe5(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	return nrf24l01_sysfs_store_enaa(dev, buf, count, 5);
}

ssize_t nrf24l01_sysfs_show_addr_width(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int width;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_address_width(nrf, &width)))
		goto exit_err;
	return sprintf(buf, "%u\n", width);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_addr_width(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int width;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &width)))
		goto exit_stralloc;
	if((err = nrf24l01_set_address_width(nrf, width)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_pwr_up(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int pwr_up;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_pwr_up(nrf, &pwr_up)))
		goto exit_err;
	return sprintf(buf, "%u\n", pwr_up);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_pwr_up(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int pwr_up;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &pwr_up)))
		goto exit_stralloc;
	if((err = nrf24l01_set_pwr_up(nrf, pwr_up)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_dr(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int dr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_dr(nrf, &dr)))
		goto exit_err;
	return sprintf(buf, "%u\n", dr);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_dr(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int dr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &dr)))
		goto exit_stralloc;
	if((err = nrf24l01_set_dr(nrf, dr)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_ce(struct device* dev, struct device_attribute* attr, char* buf)
{
	unsigned int state;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	state = nrf24l01_get_ce(nrf);
	return sprintf(buf, "%u\n", state);
}

ssize_t nrf24l01_sysfs_store_ce(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int ce;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &ce)))
	{
		goto exit_stralloc;
	}
	switch(ce)
	{
		case 0:
			NRF24L01_CE_LO(nrf);
			break;
		case 1:
			NRF24L01_CE_HI(nrf);
			break;
		default:
			err = -EINVAL;
			goto exit_stralloc;
	}
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_crc(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int crc;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_crc(nrf, &crc)))
		goto exit_err;
	return sprintf(buf, "%u\n", crc);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_crc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int crc;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &crc)))
		goto exit_stralloc;
	if((err = nrf24l01_set_crc(nrf, crc)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_tx_address(struct device* dev, struct device_attribute* attr, char* buf)
{
	int err;
	unsigned int addr_width;
	u64 addr = 0;
	char fmt[10];
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_tx_address_u64(nrf, &addr)))
		return err;
	if((err = nrf24l01_get_address_width(nrf, &addr_width)))
		return err;
	sprintf(fmt, "%%0%ullX\n", addr_width * 2);
	return sprintf(buf, fmt, addr);
}

ssize_t nrf24l01_sysfs_store_tx_address(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	u64 addr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtou64(str, 16, &addr)))
		goto exit_stralloc;
	if((err = nrf24l01_set_tx_address_u64(nrf, addr)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_retr_ard(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int ard;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_retr_ard(nrf, &ard)))
		goto exit_err;
	return sprintf(buf, "%u\n", ard);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_retr_ard(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int ard;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &ard)))
		goto exit_stralloc;
	if((err = nrf24l01_set_retr_ard(nrf, ard)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_retr_arc(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	unsigned int arc;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_retr_arc(nrf, &arc)))
		goto exit_err;
	return sprintf(buf, "%u\n", arc);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_retr_arc(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	unsigned int arc;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtouint(str, 10, &arc)))
		goto exit_stralloc;
	if((err = nrf24l01_set_retr_arc(nrf, arc)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_show_tx_pwr(struct device* dev, struct device_attribute* attr, char* buf)
{
	ssize_t err;
	int pwr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	if((err = nrf24l01_get_tx_power(nrf, &pwr)))
		goto exit_err;
	return sprintf(buf, "%d\n", pwr);
exit_err:
	return err;
}

ssize_t nrf24l01_sysfs_store_tx_pwr(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	ssize_t err;
	int pwr;
	struct nrf24l01_t* nrf = (dev_get_drvdata(dev));
	char* str = nrf24l01_sanitize_string(buf, count);
	if(!str)
	{
		err = -ENOMEM;
		goto exit_err;
	}
	if((err = kstrtoint(str, 10, &pwr)))
		goto exit_stralloc;
	if((err = nrf24l01_set_tx_power(nrf, pwr)))
		goto exit_stralloc;
	err = count;
exit_stralloc:
	vfree(str);
exit_err:
	return err;
}



/***************************************
 * 		SYSFS File System Device
***************************************/
static DEVICE_ATTR(txpower, 0644, nrf24l01_sysfs_show_tx_pwr, nrf24l01_sysfs_store_tx_pwr);
static DEVICE_ATTR(channel, 0644, nrf24l01_sysfs_show_channel, nrf24l01_sysfs_store_channel);
static DEVICE_ATTR(datarate, 0644, nrf24l01_sysfs_show_dr, nrf24l01_sysfs_store_dr);

static struct attribute* attr_rf[] = {
	&dev_attr_txpower.attr,
	&dev_attr_channel.attr,
	&dev_attr_datarate.attr,
	NULL
};

static struct attribute_group group_rf = {
	.attrs = attr_rf,
	.name = "rf"
};

static DEVICE_ATTR(delay, 0644, nrf24l01_sysfs_show_retr_ard, nrf24l01_sysfs_store_retr_ard);
static DEVICE_ATTR(count, 0644, nrf24l01_sysfs_show_retr_arc, nrf24l01_sysfs_store_retr_arc);

static struct attribute* attr_retr[] = {
	&dev_attr_delay.attr,
	&dev_attr_count.attr,
	NULL
};

static struct attribute_group group_retr = {
	.attrs = attr_retr,
	.name = "retransmit"
};

static DEVICE_ATTR(address_width, 0644, nrf24l01_sysfs_show_addr_width, nrf24l01_sysfs_store_addr_width);
static DEVICE_ATTR(pwr_up, 0644, nrf24l01_sysfs_show_pwr_up, nrf24l01_sysfs_store_pwr_up);
static DEVICE_ATTR(gpio_ce, 0644, nrf24l01_sysfs_show_ce, nrf24l01_sysfs_store_ce);
static DEVICE_ATTR(crc, 0644, nrf24l01_sysfs_show_crc, nrf24l01_sysfs_store_crc);
static DEVICE_ATTR(tx_address, 0644, nrf24l01_sysfs_show_tx_address, nrf24l01_sysfs_store_tx_address);

static struct attribute* attr_general[] = {
	&dev_attr_address_width.attr,
	&dev_attr_pwr_up.attr,
	&dev_attr_gpio_ce.attr,
	&dev_attr_crc.attr,
	&dev_attr_tx_address.attr,
	NULL
};

static struct attribute_group group_general = {
	.attrs = attr_general,
	.name = NULL
};

static struct device_attribute attr_pipe0_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe0,
	.store = nrf24l01_sysfs_store_payload_width_pipe0
};

static struct device_attribute attr_pipe0_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe0,
	.store = nrf24l01_sysfs_store_address_pipe0
};

static struct device_attribute attr_pipe0_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe0,
	.store = nrf24l01_sysfs_store_enable_pipe0
};

static struct device_attribute attr_pipe0_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe0,
	.store = nrf24l01_sysfs_store_dynpd_pipe0
};

static struct device_attribute attr_pipe0_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe0,
	.store = nrf24l01_sysfs_store_enaa_pipe0
};

static struct attribute* attr_pipe0[] = {
	&attr_pipe0_pw.attr,
	&attr_pipe0_addr.attr,
	&attr_pipe0_state.attr,
	&attr_pipe0_dpl.attr,
	&attr_pipe0_enaa.attr,
	NULL
};

static struct attribute_group group_pipe0 = {
	.attrs = attr_pipe0,
	.name = "pipe0"
};

static struct device_attribute attr_pipe1_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe1,
	.store = nrf24l01_sysfs_store_payload_width_pipe1
};

static struct device_attribute attr_pipe1_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe1,
	.store = nrf24l01_sysfs_store_address_pipe1
};

static struct device_attribute attr_pipe1_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe1,
	.store = nrf24l01_sysfs_store_enable_pipe1
};

static struct device_attribute attr_pipe1_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe1,
	.store = nrf24l01_sysfs_store_dynpd_pipe1
};

static struct device_attribute attr_pipe1_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe1,
	.store = nrf24l01_sysfs_store_enaa_pipe1
};

static struct attribute* attr_pipe1[] = {
	&attr_pipe1_pw.attr,
	&attr_pipe1_addr.attr,
	&attr_pipe1_state.attr,
	&attr_pipe1_dpl.attr,
	&attr_pipe1_enaa.attr,
	NULL
};

static struct attribute_group group_pipe1 = {
	.attrs = attr_pipe1,
	.name = "pipe1"
};

static struct device_attribute attr_pipe2_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe2,
	.store = nrf24l01_sysfs_store_payload_width_pipe2
};

static struct device_attribute attr_pipe2_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe2,
	.store = nrf24l01_sysfs_store_address_pipe2
};

static struct device_attribute attr_pipe2_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe2,
	.store = nrf24l01_sysfs_store_enable_pipe2
};

static struct device_attribute attr_pipe2_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe2,
	.store = nrf24l01_sysfs_store_dynpd_pipe2
};

static struct device_attribute attr_pipe2_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe2,
	.store = nrf24l01_sysfs_store_enaa_pipe2
};

static struct attribute* attr_pipe2[] = {
	&attr_pipe2_pw.attr,
	&attr_pipe2_addr.attr,
	&attr_pipe2_state.attr,
	&attr_pipe2_dpl.attr,
	&attr_pipe2_enaa.attr,
	NULL
};

static struct attribute_group group_pipe2 = {
	.attrs = attr_pipe2,
	.name = "pipe2"
};

static struct device_attribute attr_pipe3_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe3,
	.store = nrf24l01_sysfs_store_payload_width_pipe3
};

static struct device_attribute attr_pipe3_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe3,
	.store = nrf24l01_sysfs_store_address_pipe3
};

static struct device_attribute attr_pipe3_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe3,
	.store = nrf24l01_sysfs_store_enable_pipe3
};

static struct device_attribute attr_pipe3_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe3,
	.store = nrf24l01_sysfs_store_dynpd_pipe3
};

static struct device_attribute attr_pipe3_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe3,
	.store = nrf24l01_sysfs_store_enaa_pipe3
};

static struct attribute* attr_pipe3[] = {
	&attr_pipe3_pw.attr,
	&attr_pipe3_addr.attr,
	&attr_pipe3_state.attr,
	&attr_pipe3_dpl.attr,
	&attr_pipe3_enaa.attr,
	NULL
};

static struct attribute_group group_pipe3 = {
	.attrs = attr_pipe3,
	.name = "pipe3"
};

static struct device_attribute attr_pipe4_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe4,
	.store = nrf24l01_sysfs_store_payload_width_pipe4
};

static struct device_attribute attr_pipe4_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe4,
	.store = nrf24l01_sysfs_store_address_pipe4
};

static struct device_attribute attr_pipe4_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe4,
	.store = nrf24l01_sysfs_store_enable_pipe4
};

static struct device_attribute attr_pipe4_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe4,
	.store = nrf24l01_sysfs_store_dynpd_pipe4
};

static struct device_attribute attr_pipe4_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe4,
	.store = nrf24l01_sysfs_store_enaa_pipe4
};

static struct attribute* attr_pipe4[] = {
	&attr_pipe4_pw.attr,
	&attr_pipe4_addr.attr,
	&attr_pipe4_state.attr,
	&attr_pipe4_dpl.attr,
	&attr_pipe4_enaa.attr,
	NULL
};

static struct attribute_group group_pipe4 = {
	.attrs = attr_pipe4,
	.name = "pipe4"
};

static struct device_attribute attr_pipe5_pw = {
	.attr = {
		.name = "payloadwidth",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_payload_width_pipe5,
	.store = nrf24l01_sysfs_store_payload_width_pipe5
};

static struct device_attribute attr_pipe5_addr = {
	.attr = {
		.name = "address",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_address_pipe5,
	.store = nrf24l01_sysfs_store_address_pipe5
};

static struct device_attribute attr_pipe5_state = {
	.attr = {
		.name = "enable",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enable_pipe5,
	.store = nrf24l01_sysfs_store_enable_pipe5
};

static struct device_attribute attr_pipe5_dpl = {
	.attr = {
		.name = "dynamicpayload",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_dynpd_pipe5,
	.store = nrf24l01_sysfs_store_dynpd_pipe5
};

static struct device_attribute attr_pipe5_enaa = {
	.attr = {
		.name = "autoack",
		.mode = 0644
	},
	.show = nrf24l01_sysfs_show_enaa_pipe5,
	.store = nrf24l01_sysfs_store_enaa_pipe5
};

static struct attribute* attr_pipe5[] = {
	&attr_pipe5_pw.attr,
	&attr_pipe5_addr.attr,
	&attr_pipe5_state.attr,
	&attr_pipe5_dpl.attr,
	&attr_pipe5_enaa.attr,
	NULL
};

static struct attribute_group group_pipe5 = {
	.attrs = attr_pipe5,
	.name = "pipe5"
};

static const struct attribute_group* attribute_groups[] = {
	&group_general,
	&group_rf,
	&group_retr,
	&group_pipe0,
	&group_pipe1,
	&group_pipe2,
	&group_pipe3,
	&group_pipe4,
	&group_pipe5,
	NULL
};


int nrf24l01_sysfscreate(struct spi_device *spidev)
{
	int ret;
	dev_info(&spidev->dev, "%s:Start to create sysfs file\r\n", __func__);
	ret = sysfs_create_groups(&spidev->dev.kobj, (const struct attribute_group **)attribute_groups);
	if(ret)
	{
		dev_err(&spidev->dev, "%s: Failed to create sysfs file\r\n", __func__);
		ret = -ENOSYS;
	}
	return ret;
}

void nrf24l01_sysfsdetroy(struct spi_device *spidev)
{
	dev_info(&spidev->dev, "%s:Start to remove sysfs file\r\n", __func__);
	sysfs_remove_groups(&spidev->dev.kobj, (const struct attribute_group **)attribute_groups);
}