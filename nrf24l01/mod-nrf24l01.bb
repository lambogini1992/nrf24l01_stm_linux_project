SUMMARY = "Example of how to build an external NRF24L01 Linux kernel module"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

CUSTOME_DEVICETREE = "bcm2709-rpi-2-b.dts"

SRC_URI = "file://Makefile \
           file://Kbuild \
           file://*.c \
           file://*.h \
           file://COPYING \
           "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES_${PN} += "kernel-module-nrf24l01"