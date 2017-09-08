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
## @version 1.0
##
###############################################################################

VPATH		= src
INC_DIR		= inc
BUILD_DIR	= build
BIN_DIR		= bin

MKDIR_P = mkdir -p
RM_F    = rm -f
MV_F    = mv -f

OUTPUT_NAME = homework1

SRCS  = main.c \
		circbuf.c \
        ll2.c

OBJS := $(SRCS:.c=.o)

CFLAGS = -std=c99 -g -O0 -Wall -Wextra -I$(INC_DIR)
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

# Remaps an individual object file to the correct folder
.PHONY: %.o
%.o: $(BUILD_DIR)/%.o
	@echo Output will be in build folder

# Build all files and link
.PHONY: build
build: $(BIN_DIR)/$(OUTPUT_NAME)

# Deletes build files and executables
.PHONY: clean
clean:
	@$(RM_F) $(BUILD_DIR)/*
	@echo Successfully cleaned.
