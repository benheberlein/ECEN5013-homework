#! /bin/bash

echo "Deleting kernels with *ECEN*"

sudo rm /boot/*ECEN*
sudo rm -r /lib/modules/*ECEN*
sudo rm /var/lib/initramfs-tools/*ECEN*

sudo update-grub

echo "Successfully removed modules"
