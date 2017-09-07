#! /bin/bash

clear

echo "Building the Linux Kernel"

cp /boot/config-4.8.0-53-generic .config
# make default config from old config
make olddefconfig
# use debug to see output and -j 4 to use all cores
sudo make --debug=v -j 4 
sudo make --debug=v modules_install -j 4
sudo make install --debug=v -j 4

echo "Build finished"


