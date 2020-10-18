#include <Arduino.h>
#include <LedControl.h>

/*
 * 組み立てるときに気づかなかったけど、電源はデイジーチェーンさすがにできない。
 * VCCとGRANDに関しては直接とらないとおかしな動きになる。
 * デイジーチェーンをするのは、設定した３ピンのみなので注意。 
 */

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 第4引数はつないでいるMAX72198の数（最大8）
 ※8を超えるデバイスを制御する場合は、新しいLedControlインスタンスを作ること（追加でピンが必要になるので注意）
 */
LedControl lc=LedControl(12,11,10,3);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  for(int index=0;index<lc.getDeviceCount();index++) {
      lc.shutdown(index,false); 
  } 
  /* Set the brightness to a medium values */
  for(int index=0;index<lc.getDeviceCount();index++) {
      lc.setIntensity(index,8);
  }
  /* and clear the display */
  for(int index=0;index<lc.getDeviceCount();index++) {
      lc.clearDisplay(index);
  } 
  
  
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  // 一番左
  lc.setDigit(0,0,0x00,false);
  lc.setDigit(0,1,0x01,false);
  lc.setDigit(0,2,0x02,false);
  lc.setDigit(0,3,0x03,false);
  lc.setDigit(0,4,0x04,false);
  lc.setDigit(0,5,0x05,false);
  lc.setDigit(0,6,0x06,false);
  lc.setDigit(0,7,0x07,false);
  // 真ん中
  lc.setDigit(1,0,0x00,false);
  lc.setDigit(1,1,0x01,false);
  lc.setDigit(1,2,0x02,false);
  lc.setDigit(1,3,0x03,false);
  lc.setDigit(1,4,0x04,false);
  lc.setDigit(1,5,0x05,false);
  lc.setDigit(1,6,0x06,false);
  lc.setDigit(1,7,0x07,false);
  // 右
  lc.setDigit(2,0,0x00,false);
  lc.setDigit(2,1,0x01,false);
  lc.setDigit(2,2,0x02,false);
  lc.setDigit(2,3,0x03,false);
  lc.setDigit(2,4,0x04,false);
  lc.setDigit(2,5,0x05,false);
  lc.setDigit(2,6,0x06,false);
  lc.setDigit(2,7,0x07,false);
  

} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() {
  writeArduinoOn7Segment();
}