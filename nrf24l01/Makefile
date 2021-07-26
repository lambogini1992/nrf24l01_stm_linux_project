export ARCH ?= arm
export CROSS_COMPILE ?= arm-linux-gnueabihf-

KERNEL_DIR ?= $(HOME)/raspberry/linux

default:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
