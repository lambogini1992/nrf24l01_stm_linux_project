obj-m += sys_dev.o
sys_dev-objs := test_dev.o nrf24_sysfs.o
export ARCH ?= arm
export CROSS_COMPILE ?= arm-linux-gnueabihf-
KERNEL_DIR ?= ../../linux

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean