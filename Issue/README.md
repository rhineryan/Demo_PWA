Issue track 
## 1.使用gpu105登陆，GPUPWA 2.1，使用GammKK测试时，编译通过了，运行时报错。
![](1.png)
### 解决办法
gpu105只能运行1.9的程序；注释掉BOSS的环境

## 2.硬件问题，需要机器重启
![](2.png)
编译时报错：
![](2_2.png)
### 解决办法
在终端输入以下命令看看输出
fglrxinfo
aticonfig --adapter=all --odgt
aticonfig --adapter=all --odgc
重启机器。
