# GPUPWA环境设置
======================================================

****
	
|Author|xian xiong|
|---|---
|E-mail|xxa2010@126.com
****

## 1.[系统安装](#系统安装)
## 2.[基本软件安装](#基本软件安装)
## 3.GPUPWA环境设置
## 4.前台例子测试

======================================================
## 系统安装
SLC5，6，7皆可，ISO镜像文件请移步CERN官方网站。[SLC5](http://linuxsoft.cern.ch/cern/slc5X/iso/)

## 基本软件安装
### NVIDIA 卡
1. 下载驱动(选择你对应支持的驱动)：

    1. (建议下载*.run文件,可以直接./*.run)

2. 安装驱动：

	2. 按照引导就可以了./*run即可（安装前注意以下两点）

(1).关闭X windows : 进入命令行模式Kill掉gdm或kde

(2).屏蔽Nouveau(由第三方为NVIDIA显卡开发的一个开源3D驱动)

Step1.把驱动加入黑名单

vim /etc/modprobe.d/blacklist.conf ，在文件后面加入blacklist nouveau

Step2.备份与重建initramfs

mv /boot/initramfs-$(uname -r).img /boot/initramfs-$(uname -r).img.bakdracut -v /boot/initramfs-$(uname -r).img $(uname -r)

Step3.重启系统至文本格式

reboot

init 3(进入文本格式)

(P.S. lsmod|grep nouveau 可以查看nouveau是否被屏蔽)

III.检查驱动是否安装成功

cat /proc/driver/nvidia/version

### AMD卡
