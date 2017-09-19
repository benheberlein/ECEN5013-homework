################################################################################
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
## @brief Builds the project 
## 
## This  file provides the build configuration for the project. Valid targets 
## are 'build' (default) and 'clean' to clean the /build folder. The build 
## uses GCC as the compiler. 
##
## @author Ben Heberlein
## @date September 7 2017
## @version 1.1
##
###############################################################################

VPATH		= src:test
INC_DIR		= inc
BUILD_DIR	= build
BIN_DIR		= bin
3P_DIR		= 3rd-party
3P_INC_DIR  = 3rd-party/build/cmocka/include
3P_SRC_DIR  = 3rd-party/build/cmocka/src
3P_LIB_DIR  = 3rd-party/build/cmocka/lib
CMOCKA		= cmocka
CMOCKA_LIB  = libcmocka.a

MKDIR_P = mkdir -p
RM_F    = rm -f
MV_F    = mv -f

OUTPUT_NAME = homework2

TEST_OUTPUT_NAME = test_homework2

SRCS  = main.c \
		circbuf.c \
        ll2.c

TEST_SRCS = circbuf.c \
            ll2.c \
            test_ll2.c 

OBJS := $(SRCS:.c=.o)

TEST_OBJS := $(TEST_SRCS:.c=.o)

CFLAGS = -std=c99 -g -O0 -Wall -Wextra -I$(INC_DIR) -I$(3P_INC_DIR)
LDFLAGS =

CC = gcc

# Targets
##############################################################################

all: build

$(BIN_DIR)/$(OUTPUT_NAME): $(addprefix $(BUILD_DIR)/, $(OBJS))
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/$(TEST_OUTPUT_NAME): $(addprefix $(BUILD_DIR)/, $(TEST_OBJS))
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -l$(CMOCKA)

# Remaps an individual object file to the correct folder
.PHONY: %.o
%.o: $(BUILD_DIR)/%.o
	@echo Output will be in build folder

# Build all files and link
.PHONY: build
build: $(BIN_DIR)/$(OUTPUT_NAME)

# Build cmocka testing framework and any future 3rd party libraries
.PHONY: 3rd-party
3rd-party:
	$(MAKE) --no-print-directory --directory=$(3P_DIR) CC=$(CC) CFLAGS="$(CFLAGS)" $(CMOCKA);

# Build test suite and execute
.PHONY:
test:  $(BIN_DIR)/$(TEST_OUTPUT_NAME)
	$(BIN_DIR)/$(TEST_OUTPUT_NAME)

# Deletes build files, leaves executables
.PHONY: clean
clean:
	@$(RM_F) $(BUILD_DIR)/*
	@$(RM_F) $(BIN_DIR)/*
	@echo Successfully cleaned.


