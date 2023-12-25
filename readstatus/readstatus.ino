
#include <digitalWriteFast.h>
#include <Wire.h>
#define K_START 2
#define K_A 3
#define K_RIGHT 5
#define K_X 4
#define K_UP 6
#define K_DOWN 8
#define K_Y 9
#define K_LEFT 7
#define K_B 11
#define K_Z 10
#define SENDXY 12
int slave_address = 9;

//#define DEBUG
void setup() {
  pinModeFast(K_START, INPUT_PULLUP);
  pinModeFast(K_A,     INPUT_PULLUP);
  pinModeFast(K_RIGHT, INPUT_PULLUP);
  pinModeFast(K_X,     INPUT_PULLUP);
  pinModeFast(K_UP,    INPUT_PULLUP);
  pinModeFast(K_DOWN,  INPUT_PULLUP);
  pinModeFast(K_Y,     INPUT_PULLUP);
  pinModeFast(K_LEFT,  INPUT_PULLUP);
  pinModeFast(K_B,     INPUT_PULLUP);
  pinModeFast(K_Z,     INPUT_PULLUP);
  pinModeFast(SENDXY,  INPUT);
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  //Wire.setClock(400000);
  Wire.begin(slave_address);
  Wire.onRequest(requestEvent);
  #ifdef DEBUG
  Wire.onReceive(receiveEvent);
  #endif
}

unsigned char buf[2];
void requestEvent() {
  #ifdef DEBUG
  Serial.print("Request!\n");
  #endif
  char sendxy = digitalReadFast(SENDXY);
  buf[0] = 0;
  buf[0] |= (digitalReadFast(K_UP)   ==0)     ;
  buf[0] |= (digitalReadFast(K_DOWN) ==0) << 1;
  buf[0] |= (digitalReadFast(K_LEFT) ==0) << 2;
  buf[0] |= (digitalReadFast(K_RIGHT)==0) << 3;
  buf[0] |= (digitalReadFast(K_A)    ==0) << 4;
  buf[0] |= (digitalReadFast(K_B)    ==0) << 5;
  buf[0] |= (digitalReadFast(K_START)    ==0) << 6;
  buf[0] |= (digitalReadFast(K_Z)        ==0) << 7;
  Wire.write(buf[0]);
  if (sendxy) {
    buf[1] = 0;
    buf[1] |= (digitalReadFast(K_X)    ==0) << 0;
    buf[1] |= (digitalReadFast(K_Y)    ==0) << 1;
    Wire.write(buf[1]);
  }

  #ifdef DEBUG
  Serial.print("Status:\t");
  Serial.print(buf[0],BIN);
  if (sendxy) {
    Serial.print("\t");
    Serial.print(buf[2],BIN);
  }
  Serial.println();
  #endif
}

#ifdef DEBUG
void receiveEvent(int bytes) {
  unsigned char rbuf[2];
  Serial.print("Recieved ");
  rbuf[1] = Wire.read();
  rbuf[2] |= Wire.read();
  Serial.print(rbuf[1], BIN);
  Serial.print("\t");
  Serial.print(rbuf[2], BIN);
  Serial.println();
}
#endif

void loop() {
  
}
