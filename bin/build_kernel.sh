#! /bin/bash

clear

echo "Building the Linux Kernel"

sudo cp /boot/config-4.8.0-53-generic .config
# make default config from old config
make olddefconfig
# use debug to see output and -j 4 to use all cores
sudo make --debug=b -j 4 
#sudo make_modules --debug=v -j 4
sudo make --debug=b modules_install -j 4
sudo make install --debug=b -j 4

echo "Build finished"


