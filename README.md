# voxel3d_tools
Library and utilities for working with 5Voxel 5Z01A 3D-ToF Camera  

Note: Multi-devices on single host is supported starting from V1.1.0 library & V1.5 app

-------------------------------------------------------------------------------
# Ubuntu
Usage: ./voxel3d_tools [options]  
  
Version 1.5  
Options:  
-h | --help&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;Print this message  
-a | --get_auto_expo&emsp;get auto exposure mode  
-A | --set_auto_expo&emsp;set auto exposure mode  
-b | --build_date&emsp;&emsp;&nbsp;&nbsp;&nbsp;show firmware build date  
-c | --count&emsp;&emsp;&emsp;&emsp;&emsp;Number of frames to grab [70]  
-r | --get_mode&emsp;&emsp;&emsp;&nbsp;get range mode  
-R | --set_mode&emsp;&emsp;&emsp;&nbsp;set range mode  
-S | --scan_dev&emsp;&emsp;&emsp;&nbsp;&nbsp;scan devices and list device S/N  
-s | --dev_sn&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;specify device S/N to access 
-t | --get_conf&emsp;&emsp;&emsp;&nbsp;get confidence threshold  
-T | --set_conf&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;set confidence threshold  
-u | --fw_upgrade&emsp;&emsp;&nbsp;device firmware upgrade  
-v | --version&emsp;&emsp;&emsp;&emsp;&nbsp;show firmware version  
  
  
Example:  
./voxel3d_tools -s PX2011090052 -c 100  
  
  
Supported Deivce(s)
-------------------------------------------------------------------------------
5Voxel 5Z01A  
  
Supported OS/Platform
-------------------------------------------------------------------------------
* ### OS  
  $ lsb_release -a  
  No LSB modules are available.  
  Distributor ID:	Ubuntu  
  Description:	Ubuntu 18.04.5 LTS  
  Release:	18.04  
  Codename:	bionic  
  
* ### Platform  
  * x86_64
  * aarch64 (Jetson Nano / Raspberry Pi4)
  
Kernel module needed
-------------------------------------------------------------------------------

Build steps
-------------------------------------------------------------------------------
1. Go to platform/linux and do 'make'  
2. Run './voxel3d_tools -h' to show menu  
  
  
  
-------------------------------------------------------------------------------
# Windows
Usage: voxel3d_tools.exe [options]  
  
Version 1.5  
Options:  
-h | --help&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;Print this message  
-a | --get_auto_expo&emsp;get auto exposure mode  
-A | --set_auto_expo&emsp;set auto exposure mode  
-b | --build_date&emsp;&emsp;&nbsp;&nbsp;&nbsp;show firmware build date  
-c | --count&emsp;&emsp;&emsp;&emsp;&emsp;Number of frames to grab [70]  
-r | --get_mode&emsp;&emsp;&emsp;&nbsp;get range mode  
-R | --set_mode&emsp;&emsp;&emsp;&nbsp;set range mode  
-S | --scan_dev&emsp;&emsp;&emsp;&nbsp;&nbsp;scan devices and list device S/N  
-s | --dev_sn&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;specify device S/N to access 
-t | --get_conf&emsp;&emsp;&emsp;&nbsp;get confidence threshold  
-T | --set_conf&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;set confidence threshold  
-u | --fw_upgrade&emsp;&emsp;&nbsp;device firmware upgrade  
-v | --version&emsp;&emsp;&emsp;&emsp;&nbsp;show firmware version  
  
  
Example:  
voxel3d_tools.exe -s PX2011090052 -c 100  
  
  
Supported Deivce(s)
-------------------------------------------------------------------------------
5Voxel 5Z01A  

Supported OS/Platform
-------------------------------------------------------------------------------
$ Windows10 (Visual Studio Community 2017)  
  
  
Kernel module needed
-------------------------------------------------------------------------------

Build steps
-------------------------------------------------------------------------------
1. Install Vistual Studion Community 2017  
2. Go to platform/win and click on 'voxel3d_tools.sln' (Visual Studio Solution File)  
3. Build x86/x64 release project  
4. Open a command window and go to following directory  
        platform/win/Bin/[x86/x64]-Release/voxel3d_tools  
5. Execute 'voxel3d_tools.exe -h' to show menu  
