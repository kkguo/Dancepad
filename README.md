# Dancepad
Hack the Dance pad to used on PC.

The oringinal dancepad I got from Temu has a gamecube interface, and I tried couple of adapters on the market, non of them working.
![image](https://github.com/kkguo/Dancepad/assets/485503/8f1d9966-4519-4039-a223-36a8cb674579)

I Used a arduino pro mini for reading buttons and send data via I2C to an attiny85 board for USB Joystick function.
Not using shift-reg for scanning buttons because I don't have the part and attiny85 really doesn't have many IO can be used.

## Steps:
1. solder all the button pin to the pro mini (pin 2-11)
2. solder the i2c interface to attiny85 (SCL-> SCL SDA-> SDA)
3. connect the GND pins on both board
4. upload readstatus sketch to pro mini with a TTL to USB adapter, and joystick to attiny85
5. solder 5V on attiny85 to VCC on pro mini
6. put back the shell

## Extra:
Because stepmania doesn't use down-left and down-right key, by default only 8 keys are scanned.
That also helps on scanning rate, because 8 bits data takes 2 ocelet cycle on I2C (Read command + DATA), other than 10 bits data takes 3 ocelet. 
Potentially it saves almost 1/3 time on I2C.

Hold the 2 function buttons and press down will enable scanning the 2 leftover keys.
![image](https://github.com/kkguo/Dancepad/assets/485503/48af59d6-75a5-4ffe-ae5a-5f677e5023fb)


