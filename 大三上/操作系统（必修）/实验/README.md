# IMX6ULL_STM32MP157鸿蒙系统
> 支持IMX6ULL和STM32MP157 系列开发板的鸿蒙系统补丁

## 1. 介绍

这是百问网科技制作的鸿蒙系列课程，本仓库含有源码、文档、工具等。
视频在www.100ask.net


## 2. 配置开发环境
> 在Ubuntu上，使用我们的一键配置环境脚本在ubuntu-18.04系统上一键配置鸿蒙系统运行环境

```
book@100ask:~$  wget --no-check-certificate -O Configuring_ubuntu.sh https://weidongshan.coding.net/p/DevelopmentEnvConf/d/DevelopmentEnvConf/git/raw/master/Configuring_ubuntu.sh && sudo chmod +x Configuring_ubuntu.sh && sudo ./Configuring_ubuntu.sh
```

## 3. 编译鸿蒙系统

### 3.1 配置repo工具

> 首先需要设置GIT用户名和密码

```
book@100ask:~$ git config --global user.name "100ask"
book@100ask:~$ git config --global user.email "weidongshan@qq.com"
book@100ask:~$ git config --global credential.helper store
```

> 获取并安装repo工具

```
book@100ask:~$ curl https://gitee.com/oschina/repo/raw/fork_flow/repo-py3 > repo
book@100ask:~$ sudo cp repo  /usr/local/bin/repo && sudo chmod a+x /usr/local/bin/repo
book@100ask:~$ sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple requests
```

### 3.2 同步源码

```
book@100ask:~$ cd /home/book
book@100ask:~$ mkdir  openharmony && cd  openharmony
book@100ask:~$ repo init -u https://gitee.com/openharmony/manifest.git -b OpenHarmony-1.0
book@100ask:~$ repo sync -c -j8

```

### 3.3 打补丁
> 获取补丁文件

```
book@100ask:~$ cd  /home/book
book@100ask:~$ git  clone  https://e.coding.net/weidongshan/openharmony/doc_and_source_for_openharmony.git
```

补丁文件`openharmony_100ask_v1.2.patch`位于如下目录，这两个目录里的文件是一样的：

```
doc_and_source_for_openharmony\IMX6ULL\source\01_文档配套的源码\patch\
    openharmony_100ask_v1.2.patch
doc_and_source_for_openharmony\STM32MP157\source\01_文档配套的源码\A7\patch\
    openharmony_100ask_v1.2.patch
```

> 给鸿蒙系统打补丁

```
// 为方便使用，先把补丁文件复制到/home/book目录
// 然后如下打补丁
book@100ask:~$ cd  /home/book/openharmony
book@100ask:~$ patch -p1 < /home/book/openharmony_100ask_v1.2.patch
```

### 3.4 为IMX6ULL编译

```
book@100ask:~$ cd  /home/book/openharmony/kernel/liteos_a
book@100ask:~$ cp  tools/build/config/debug/imx6ull_clang.config .config   // 配置
book@100ask:~$ make clean      // 前面为hi3518ev300编译过，先清除一下
book@100ask:~$ make  -j  8     // 编译内核，可以得到out/imx6ull/liteos.bin
book@100ask:~$ make  rootfs    // 编译根文件系统，可以得到rootfs.img
book@100ask:~$ cp  out/imx6ull/rootfs.img out/imx6ull/rootfs.jffs2 // 改个名易辨认，烧写工具使用rootfs.jffs2
```
### 3.5 为STM32MP157编译

```
book@100ask:~$ cd  /home/book/openharmony/kernel/liteos_a
book@100ask:~$ cp tools/build/config/debug/stm32mp157_clang.config .config   // 配置
book@100ask:~$ make clean      // 先清除一下，否则会提示错误
book@100ask:~$ make  -j  8     // 编译内核，可以在out/stm32mp157/目录下，
                               // 得到liteos.stm32 和liteos_with_uboot_header.bin
book@100ask:~$ make  rootfs    // 编译根文件系统，可以得到rootfs.jffs2.bin
```

liteos.stm32是在liteos.bin前面加了STM32的头部，可以烧写到板子上去。
liteos_with_uboot_header.bin在liteos.bin前面加了u-boot的头部，可以使用u-boot启动。
rootfs.jffs2.bin和rootfs.jffs2、rootfs.img是一样的，烧写软件STM32CubeProgrammer只识别bin等后缀名。

## 4. 烧写运行鸿蒙系统

### 4.1 烧写IMX6ULL
使用百问网独家烧写工具点击鸿蒙按钮进行烧写，请参考：

```c
doc_and_source_for_openharmony\IMX6ULL\基于IMX6ULL的鸿蒙开发手册.docx
```

### 4.2 烧写STM32MP157

使用STM32CubeProgrammer，请参考：

```c
doc_and_source_for_openharmony\STM32MP157\基于STM32MP157的鸿蒙开发手册.docx
```

## 5. 参与贡献
1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request