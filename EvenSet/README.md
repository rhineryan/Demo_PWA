# GPUPWA环境设置
======================================================

****
	
|Author|xian xiong|
|---|---
|E-mail|xxa2010@126.com
****

## 1. [系统安装](#系统安装)
## 2. [软件安装编译](#软件安装编译)
1. ### NVIDIA卡
2. ### AMD卡
## 4. 前台例子测试

======================================================
## 系统安装
SLC5，6，7皆可，ISO镜像文件请移步CERN官方网站。[SLC5](http://linuxsoft.cern.ch/cern/slc5X/iso/)

## 软件安装编译
### NVIDIA卡
1. 下载驱动(选择你对应支持的驱动)：

	1. (建议下载*.run文件,可以直接./*.run)

2. 安装驱动：

	1. 按照引导就可以了./*run即可（安装前注意以下两点）

	2. 关闭X windows : 进入命令行模式Kill掉gdm或kde

	3. 屏蔽Nouveau(由第三方为NVIDIA显卡开发的一个开源3D驱动)

	4. Step1.把驱动加入黑名单: 
	
		1. vim /etc/modprobe.d/blacklist.conf ，在文件后面加入blacklist nouveau

	5. Step2.备份与重建initramfs: 
	
		1. mv /boot/initramfs-$(uname -r).img /boot/initramfs-$(uname -r).img.bak
	
		2. dracut -v /boot/initramfs-$(uname -r).img $(uname -r)

	6. Step3.重启系统至文本格式

	7. reboot

	8. init 3(进入文本格式)

	9. (P.S. lsmod|grep nouveau 可以查看nouveau是否被屏蔽)

3. 检查驱动是否安装成功

	1. cat /proc/driver/nvidia/version
4. CUDA
	1. lspci | grep -i nvidia 查看显卡型号(一般都支持CUDA)
	2. uname -m && cat /etc/*release 查看系统版本(一般也是支持CUDA的)
	3. uname –r 查看kernel版本
	4. 官网下载CUDA(链接为CUDA8.0的 我们选对应kernel的你安装SLC对应的REDHAT版本的runfile)
	5. sudo sh cuda_8.0.61_375.26_linux.run 然后按引导安装
	7. 检查安装是否成功
		1. Step1. 添加环境变量到.bashrc(然后source)
			1. export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CUDAROOT}/lib64:/usr/local/lib
			2. export PATH=${PATH}:${CUDAROOT}/bin:
		2. Step2.检查
			1. nvcc –V    输出CUDA的版本信息 (输出正常即安装成功)
5. ROOT
	1. 下载ROOT5,6皆可
	2. 解压之后(配置安装)
		1. ./configure linuxx8664gcc --enable-mathmore --enable-minuit2 --enable-roofit --enable-soversion --enable-tmva
	3. make -j4 (调用4核心编译)
	4. Minuit2 (按下图所示修改，保险起见改完再去root第一级目录下编译一遍)
	![](https://github.com/rhineryan/Demo_PWA/blob/master/EvenSet/root_minuit.png)
6. 编译GPUPWA
	1. clone当前目录下的所有文件
	2. 修改envset文件
	
	export ROOTSYS= （你root的安装目录）
	
	export CUDAROOT=/usr/local/cuda-8.0 （你CUDA的安装目录）
	
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CUDAROOT}/lib64:${ROOTSYS}/lib:/usr/local/lib
	
	export PATH=${PATH}:${CUDAROOT}/bin:$ROOTSYS/bin:
	
	export GPUPWA= （你存放GPUPWA的目录）
	
	export GPUPWA_GPU_NR=0
	
	export DISPLAY=0.0
	
	export _NVIDIA=1
	
	3. source envset
	4. make clean； make
	5. 编译大概需要20分钟，如果一切顺利，将不会有报错信息。
	
### AMD卡

1. AMD卡驱动
2. AMD APP ADK 

目前GPUPWA使用的版本是AMDAPPSDK-2.9-1 ，官网没找到下载链接。可以去这个网站下载。[AMDAPPSDK2.9](http://hc.csdn.net/resources/resource_detail?id=13)

安装AMDAPPSDK参照官方文档。[安装文档](http://developer.amd.com/wordpress/media/2012/10/AMD_APP_SDK_Installation_Notes2.pdf)
	
