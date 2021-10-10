#/bin/bash
sudo dmesg -C
sudo modprobe mac802154
sudo modprobe ieee802154_socket
sudo insmod nrf24l01.ko

# Private Area Network ID
panid="0xbeef"
# Index of the wpan interface
i=0

# Set the PANID of the wpan interface
sudo iwpan dev wpan${i} set pan_id $panid
# Create a lowpan interface over the wpan interface
sudo ip link add link wpan${i} name lowpan${i} type lowpan
# Bring up the wpan and lowpan interfaces
sudo ip link set wpan${i} up
sudo ip link set lowpan${i} up