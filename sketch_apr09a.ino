#include <NanodeUNIO.h>

static void status(boolean r)
{
  if (r) Serial.println("(success)");
  else Serial.println("(failure)");
}

static void dump_eeprom(void)
{
  byte buf[256];
  char lbuf[80];
  char *x;
  int i, j;

  NanodeUNIO unio(NANODE_MAC_DEVICE);

  memset(buf, 0, 256);
  status(unio.read(buf, 0, 256));

  for (i = 0; i < 256; i += 16) {
    x = lbuf;
    sprintf(x, "%02X: ", i);
    x += 4;
    for (j = 0; j < 16; j++) {
      sprintf(x, "%02X", buf[i + j]);
      x += 2;
    }
    *x = 32;
    x += 1;
    for (j = 0; j < 16; j++) {
      if (buf[i + j] >= 32 && buf[i + j] < 127) *x = buf[i + j];
      else *x = 46;
      x++;
    }
    *x = 0;
    Serial.println(lbuf);
  }
}

void setup() {
  char dumpInData[5][16] = {
               /*颜色*/              /*    编号   */  /*       总长        */  /*       总长        */
    {'Z' , 'A' , 'W' , 0x00, 0x00,  '4',  '3',  'V', 0x80, 0xA9, 0x03, 0x00, 0x80, 0xA9, 0x03, 0x00}, //00
     //喷头温度// //底板温度//   /*    ===============编号===============   */
    {0xD2, 0x00, 0x5A, 0x00,  'T',  'H',  'G',  'B',  '0',  '1',  '3',  '2', 0x00, 0x00, 0x00, 0x00}, //10
    
    {0x00, 0x00, 0x00, 0x00,  '4', 0x00, 0x00, 0x00,  'Z',  'A',  'W', 0x00, 0xAA, 0x55, 0xAA, 0x55}, //20
                             //剩余量              //
    {0x88, 0x33, 0x55, 0xAA, 0x80, 0xA9, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0xED, 0x00, 0xE0}, //30
                             /*       总长        */
    {0x88, 0x33, 0x55, 0xAA, 0x80, 0xA9, 0x03, 0x00, 0xAA, 0x55, 0xAA, 0x55, 0x07, 0x83, 0x0A, 0x00} //70
  };
  
char serialNum[4]; //读取编号

  byte sr;
  NanodeUNIO unio(NANODE_MAC_DEVICE);

  Serial.begin(38400);
  Serial.println("NanodeUNIO test\n");

  Serial.println("Read status register...");
  status(unio.read_status(&sr));
  Serial.println(sr, HEX);

  Serial.println("Read the device...");
  dump_eeprom();

  status(unio.read((byte *)serialNum, 0x18, 4)); //读取编号
  add1_Array(serialNum, 4, 0); // SERIAL ADD 1
  dumpInData[1][8] = serialNum[0];
  dumpInData[1][9] = serialNum[1];
  dumpInData[1][10] = serialNum[2];
  dumpInData[1][11] = serialNum[3];

  Serial.println("Write to the device...");
  // status(unio.simple_write((const byte *)x,0,strlen(x)));
  status(unio.simple_write((const byte *)dumpInData[0], 0x00, 16));
  status(unio.simple_write((const byte *)dumpInData[0], 0X40, 16));

  status(unio.simple_write((const byte *)dumpInData[1], 0x10, 16));
  status(unio.simple_write((const byte *)dumpInData[1], 0x50, 16));

  status(unio.simple_write((const byte *)dumpInData[2], 0x20, 16));
  status(unio.simple_write((const byte *)dumpInData[2], 0x60, 16));

  status(unio.simple_write((const byte *)dumpInData[3], 0x30, 16));
  status(unio.simple_write((const byte *)dumpInData[4], 0x70, 16));
  Serial.println("Read again...");
  dump_eeprom();

  //  Serial.println("Try writing in the write-protected area...");
  //  status(unio.simple_write((const byte *)x,0xd0,strlen(x)+1));
  //
  //  Serial.println("Read again...");
  //  dump_eeprom();
}

void loop() {
  pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second

}

void add1_Array( char *src, int length, int offset){
  src[offset + length - 1]++;
  for(int i = 1; i <= length; i++){
    if(src[offset + length - i] > '9'){
      src[offset + length - i] = '0';
      if(i != length){
        src[offset + length - (i + 1)]++;
      }
  
      }
  }
}
