### STM32H750基于HX711的电子秤

#### 1、开发环境
- 硬件平台：ART-PI开发板（STM32H750XB）
- 自动代码生成：STM32CodeMX  
- 代码编写：Clion  
- 串口调试助手：SecureCRT  
- 编码：utf-8
#### 2、接线连接     
- HX711  
  
  | HX711| ART-PI|
  | ---- | ---- |
  | VCC  |  5V  |
  | GEN  | GEN  |
  | DOUT | PH15 |
  | SCK  | PH13 |
  
- 串口屏

  | HX711| ART-PI|
  | ---- | ---- |
  | VCC  | 5V   |
  | TX   | PA9  |
  | RX   | PA10 |
  | GND  | GND  |

#### 3、使用

​		串口屏工程文件在Accessory目录下

