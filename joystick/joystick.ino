#include "DigiJoystick.h"
#include <Wire.h>
//#define DEBUG

#define SENDXY 1

int slave_address = 9;
char sendxy=0;
void setup() {
  char buf [8] = {127,127,127,127,127,127,0,0};
  // don't need to set anything up to use DigiKeyboard
  //Wire.setClock(400000);
  pinMode(SENDXY, OUTPUT);
  Wire.begin(); 
  DigiJoystick.setValues(buf);
  digitalWrite(SENDXY, sendxy);
}

unsigned char buf[2];
char flag = 0;
void loop() {
  DigiJoystick.update(); // call this at least every 50ms
  if (sendxy) {
    Wire.requestFrom(slave_address, 2);
  } else {
    Wire.requestFrom(slave_address, 1);
  }
  buf[0] = Wire.read();
  if (sendxy) {
    buf[1] = Wire.read();
  } else {
    buf[1] = 0;
  }
  DigiJoystick.setButtons(buf[0],buf[1]);

  if (buf[0] == B11000010) { // Z+START+DOWN    
    if (!flag) {
      sendxy = 1-sendxy;
      digitalWrite(SENDXY, sendxy);
    }
    flag = 1;
  } else {
    flag = 0;
  }
  #ifdef DEBUG
   Wire.beginTransmission(slave_address);
   Wire.write(buf[0]);
   Wire.write(buf[1]);
   Wire.endTransmission();
  #endif
  //DigiJoystick.delay(50); // wait 50 milliseconds
}
