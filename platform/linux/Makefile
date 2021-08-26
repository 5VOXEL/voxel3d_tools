TOP := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
ROOT = $(TOP)/../..
include $(TOP)/Makefile.check

SRC_DIR = $(ROOT)/src

CC=g++
CFLAGS=-Wall
INCLUDES=-I$(ROOT)/inc
LDLIBS=-lvoxel3d

all: voxel3d_tools

voxel3d_tools: voxel3d_app.o
	$(CC) $(INCLUDES) $(LDFLAGS) -Wl,-R -Wl,$(LIB_DIR) $(CFLAGS) -o voxel3d_tools voxel3d_app.o $(LDLIBS)

voxel3d_app.o:
	$(CC) $(INCLUDES) $(LDFLAGS) $(CFLAGS) -c $(SRC_DIR)/voxel3d_app.cpp $(LDLIBS)

clean:
	rm -f voxel3d_tools voxel3d_app.o
