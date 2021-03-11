# 智能电子秤

## 一、简介

​		此系统采用STM32F103C8T6或STM32H750XB为下位机主控芯片，单片机处理来自HX711称重传感器模块的数据来达到称重的目的，本系统称重范围0~5KG，称重精度经校准后可达1g，系统具备称重、去皮、报警等功能。此系统还配备一个上位机，上位机采用PyQt5编写，上下位机之间通过串口通信。

## 二、使用说明

​		系统上电自动归零，所以上电前请不要在称重台上放置物体。同时按住A、B键去皮，同时长按A、B键进入称重报警值设置界面，报警值的设置范围为1~5000g。

​		系统通过USB线与电脑相连，双击上位机程序运行，选择串口<img src="C:\Users\Xuhuajin\Desktop\DianZiChen\Doc\win1.jpg" alt="win1" style="zoom: 50%;" />点击连接按钮即可进入主界面，主界面如图所示：<img src="C:\Users\Xuhuajin\Desktop\DianZiChen\Doc\win2.jpg" style="zoom:50%;" />

## 三、目录结构

```
DianZiChen
├─HardWare						下位机硬件相关
│  └─stm32f103c8t6_dzc			基于stm32f103的下位机工程文件夹
│      │ 
│      ├─cmake-build-debug		编译输出文件夹，包含.hex及.bin烧录文件
│      │  
│      ├─Core					用户核心文件夹，包含各类驱动
│      │  ├─Inc					.h文件存放文件夹
│      │  ├─Src					.c文件存放文件夹
│      │  └─Startup				存放启动文件
│      └─Drivers				st官方驱动
│  └─stm32h750xb_dzc			基于stm32H750的下位机工程文件夹
│      │ 
│      ├─cmake-build-debug		编译输出文件夹，包含.hex及.bin烧录文件
│      │  
│      ├─Core					用户核心文件夹，包含各类驱动
│      │  ├─Inc					.h文件存放文件夹
│      │  ├─Src					.c文件存放文件夹
│      │  └─Startup				存放启动文件
│      └─Drivers				st官方驱动
|
├─Doc							存放一些文档及图片，非工程文件
│          
└─PyQt5GUI						上位机工程文件夹
    ├─.idea
    │  └─inspectionProfiles
    ├─build						存放pyinstaller打包时编译生成的文件啊
    │  
    ├─communication				串口驱动
    │  
    ├─dist						存放.exe文件
    │  
    ├─PyQt5Ui					界面文件
    │  
    └─resource					资源文件
    
```

## 四、开发环境

1. 下位机
   
   - MinGW：工具链
   
   - Clion 2020.3.x：代码编写及编译工具
   - STM32CubeMX：代码自动生成工具
   - secureCRT 8.3：串口调试助手
   - 编码：utf-8
   
2. 上位机
   - Pycharm 2020.3.x：代码编辑器
   - QtDesigner：可视化界面设计工具
   - 所依赖的三方库：PyQt5、pyserial