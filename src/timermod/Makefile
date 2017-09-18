###############################################################################
# Copyright (C) 2017 by Ben Heberlein
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. This file
# was created for the University of Colorado Boulder course Advanced Practical
# Embedded Software Development. Ben Heberlein and the University of Colorado 
# are not liable for any misuse of this material.
#
###############################################################################
##
## @file Makefile
## @brief Builds the timermod module
##
## This file builds the associated timermod kernel module. 
##
## @author Ben Heberlein
## @date September 7 2017
## @version 1.0
##
###############################################################################

obj-m += timermod.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
