TOP := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
ROOT = $(TOP)/../..

SRC_DIR = $(ROOT)/src
LIB_DIR = $(ROOT)/lib

CC=gcc 
CFLAGS=-Wall
LDFLAGS=-L$(ROOT)/lib/x86_64
INCLUDES=-I$(ROOT)/inc
LDLIBS=-lvoxel3d

all: voxel3d_tools

voxel3d_tools: voxel3d_app.o
	$(CC) $(INCLUDES) $(LDFLAGS) -Wl,-R -Wl,$(LIB_DIR) $(CFLAGS) -o voxel3d_tools voxel3d_app.o $(LDLIBS)

voxel3d_app.o:
	$(CC) $(INCLUDES) $(LDFLAGS) $(CFLAGS) -c $(SRC_DIR)/voxel3d_app.cpp $(LDLIBS)

clean:
	rm -f voxel3d_tools voxel3d_app.o
