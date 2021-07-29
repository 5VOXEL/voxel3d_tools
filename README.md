# voxel3d_tools
Library and utilities for working with 5Voxel 5Z01A 3D-ToF Camera

Usage: ./voxel3d_tools [options]

Version 1.3
Options:
-h | --help             Print this message
-a | --get_auto_expo    get auto exposure mode
-A | --set_auto_expo    set auto exposure mode
-b | --build_date       show firmware build date
-c | --count            Number of frames to grab [70]
-p | --prod_sn          show product serial number
-r | --get_mode         get range mode
-R | --set_mode         set range mode
-t | --get_conf         get confidence threshold
-T | --set_conf         set confidence threshold
-v | --version          show firmware version


Example:
./voxel3d_tools -c 100


Supported Deivce(s)
-------------------------------------------------------------------------------
5Voxel 5Z01A

Supported OS/Platform
-------------------------------------------------------------------------------
$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 18.04.5 LTS
Release:	18.04
Codename:	bionic


Kernel module needed
-------------------------------------------------------------------------------

Steps
-------------------------------------------------------------------------------
1. go to platform/linux and do 'make'
2. run './voxel3d_tools -h' to show menu
