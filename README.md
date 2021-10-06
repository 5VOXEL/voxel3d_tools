# voxel3d_tools
Library and utilities for working with 5Voxel 5Z01A 3D-ToF Camera  

-------------------------------------------------------------------------------
# Ubuntu
Usage: ./voxel3d_tools [options]  
  
Version 1.4  
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
-u | --fw_upgrade       device firmware upgrade  
-v | --version          show firmware version  
  
  
Example:  
./voxel3d_tools -c 100  
  
  
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
-u | --fw_upgrade       device firmware upgrade  
-v | --version          show firmware version  
  
  
Example:  
voxel3d_tools.exe -c 100  
  
  
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
