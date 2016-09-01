# DaVinci-chip-hack
复位 DaVinci xyz 3D printer 料盒的芯片中内容。

#使用方法
使用Arduino nano开发板（ATMEGA328P）为料盒芯片供电，D7引脚连接料盒芯片的SCIO引脚。  
将开发板连接芯片并给开发板通电，等开发板的LED灯闪烁后代表以下操作以完成：  
料盒芯片后四位编号+1（0000~9999循环），长度恢复到最大（不能超过40米）。

xyz printer使用一枚11LC010芯片存储料盒信息。经过各种测试加上报废了好多芯片（其实才两个=3=）整理出了下方的字节定义：  

  char dumpInData[5][16] = {
               /*颜色*/              /*    编号   */  /*       总长        */  /*       总长        */
    {'Z' , 'A' , 'W' , 0x00, 0x00,  '4',  '3',  'V', 0x80, 0xA9, 0x03, 0x00, 0x80, 0xA9, 0x03, 0x00}, //00
     //喷头温度// //底板温度//   /*    ===============编号===============   */
    {0xD2, 0x00, 0x5A, 0x00,  'T',  'H',  'G',  'B',  '0',  '1',  '3',  '2', 0x00, 0x00, 0x00, 0x00}, //10
    
    {0x00, 0x00, 0x00, 0x00,  '4', 0x00, 0x00, 0x00,  'Z',  'A',  'W', 0x00, 0xAA, 0x55, 0xAA, 0x55}, //20
                             //剩余量              //
    {0x88, 0x33, 0x55, 0xAA, 0x80, 0xA9, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0xED, 0x00, 0xE0}, //30
                             /*       总长        */
    {0x88, 0x33, 0x55, 0xAA, 0x80, 0xA9, 0x03, 0x00, 0xAA, 0x55, 0xAA, 0x55, 0x07, 0x83, 0x0A, 0x00}  //70
  };
  
  有关该项目的任何问题快去找个作者能看见地方留言=3=
  
  #参考文献：
  [另一种实现该功能的方法](https://github.com/voltivo/davinci_filament_reset_arduino)  
  [本项目中使用到的UNI/O驱动](https://github.com/sde1000/NanodeUNIO)  
  [MICROCHIP 11LC010 芯片资料](http://ww1.microchip.com/downloads/en/DeviceDoc/22067J.pdf)
  
