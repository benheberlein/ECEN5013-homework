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
## @brief Builds the 3rd party libraries
## 
## This file contatins the build configuration for the cmocka test framework.
## This is based on the example given by Alex Fosdick at
## https://github.com/afosdick/ecen5013/blob/develop/tutorials/unit_tests/
##
## @author Ben Heberlein
## @date September 18 2017
## @version 1.0
##
###############################################################################

BUILD_DIR=build
INC_DIR=inc
SRC_DIR=src
LIB_DIR=lib
INSTALL_DIR=$(BUILD_DIR)

MKDIR_P = mkdir -p
RM_RF = rm -rf

.PHONY: 3rd-party
3rd-party : cmocka

.PHONY: cmocka
cmocka:
	@$(MKDIR_P) $(BUILD_DIR)/$@;
	cd $(BUILD_DIR)/$@; cmake \
        -DCMAKE_INSTALL_PREFIX=.. \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCC=$(CC) \
        -DWITH_STATIC_LIB=ON \
        ../../cmocka; make install

.PHONY: clean
clean:
	$(RM_RF) $(BUILD_DIR)
	$(RM_RF) *~
