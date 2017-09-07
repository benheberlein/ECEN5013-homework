###########################################################
# Makefile
#
# Date: 09/07/2017
# Author: Ben Hebrlein
#
# Description:
# This is the Makefile for data structures implementations
# for homework 1.
#
###########################################################

VPATH		= src
INC_DIR		= inc
BUILD_DIR	= build
BIN_DIR		= bin

MKDIR_P = mkdir -p
RM_F    = rm -f
MV_F    = mv -f

OUTPUT_NAME = homework1

SRCS  = main.c \
		circbuf.c

OBJS := $(SRCS:.c=.o)

CFLAGS = -std=c99 -g -O0 -Wall -Wextra -I$(INC_DIR)
LDFLAGS =

CC = gcc

# Targets
###########################################################

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
