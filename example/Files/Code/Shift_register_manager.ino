/* 
 Title: RGB Color Lab
 Author: Marco Lurati and Orly Golan
 Teacher: Massimo Banzi
 Course: 1.7 Creating Tangible
 Year: 2013
 
 Code title: Shift register manager
 Hardware: Arduino Leonardo
 */

const int clockPinR = 2;       // Red Pin connected to clock pin (SH_CP) pin 11 of 74HC595
const int latchPinR = 3;       // Red Pin connected to latch pin (ST_CP) pin 12 of 74HC595
const int dataPinR = 4;        // Red Pin connected to Data in (DS) pin 14 of 74HC595

const int clockPinG = 5;       // Green Pin connected to clock pin (SH_CP) pin 11 of 74HC595
const int latchPinG = 6;       // Green Pin connected to latch pin (ST_CP) pin 12 of 74HC595
const int dataPinG = 7;        // Green Pin connected to Data in (DS) pin 14 of 74HC595

const int clockPinB = 8;       // Blue Pin connected to clock pin (SH_CP) pin 11 of 74HC595
const int latchPinB = 9;       // Blue Pin connected to latch pin (ST_CP) pin 12 of 74HC595
const int dataPinB = 10;       // Blue Pin connected to Data in (DS) pin 14 of 74HC595

int red;                   // variables for the values of each color channel received from the main Arduino on the serial port
int green;
int blue;


void setup() {

  Serial1.begin(115200);           // start of the serial connection


  pinMode(latchPinR, OUTPUT);       // pinout setup
  pinMode(latchPinG, OUTPUT);
  pinMode(latchPinB, OUTPUT);

  pinMode(dataPinR, OUTPUT); 
  pinMode(dataPinG, OUTPUT); 
  pinMode(dataPinB, OUTPUT);  

  pinMode(clockPinR, OUTPUT);
  pinMode(clockPinG, OUTPUT);
  pinMode(clockPinB, OUTPUT);

}

void loop() {  

  while (Serial1.available() > 0) {            // once the connection is on

    red = Serial1.parseInt();                   // value storage for each color channel by reading them between the comma divider
    green = Serial1.parseInt();
    blue = Serial1.parseInt();
 
    
    if (Serial1.read() == '\n') {                // the '\n' is sended once all the three color channels have been sended. That means that the led bars can be updated

      // Channel sampling. By sending to the shift register an odd number the leds light up in a continous line.
       
      // RED bar 
       
      if(red == 0) red = 0;                              // 0 leds on
      else if(red > 0 && red <= 36) red = 1;             // 1 led on (binary system 1  =    00000001)
      else if(red > 36 && red <= 72) red = 3;            // 2 led on (binary system 3  =    00000011)
      else if(red > 72 && red <= 108) red = 7;           // 3 led on (binary system 7  =    00000111)
      else if(red > 108 && red <= 144) red = 15;         // 4 led on (binary system 15  =   00001111)
      else if(red > 144 && red <= 180) red = 31;         // 5 led on (binary system 31  =   00011111)
      else if(red > 180 && red <= 216) red = 63;         // 6 led on (binary system 63  =   00111111)
      else if(red > 216 && red <= 255) red = 127;        // 7 led on (binary system 127 =   01111111)

      // GREEN bar
    
      if(green == 0) green = 0;                                // 0 leds on
      else if(green > 0 && green <= 36) green = 1;             // 1 led on (binary system 1  =    00000001)
      else if(green > 36 && green <= 72) green = 3;            // 2 led on (binary system 3  =    00000011)
      else if(green > 72 && green <= 108) green = 7;           // 3 led on (binary system 7  =    00000111)
      else if(green > 108 && green <= 144) green = 15;         // 4 led on (binary system 15  =   00001111)
      else if(green > 144 && green <= 180) green = 31;         // 5 led on (binary system 31  =   00011111)
      else if(green > 180 && green <= 216) green = 63;         // 6 led on (binary system 63  =   00111111)
      else if(green > 216 && green <= 255) green = 127;        // 7 led on (binary system 127 =   01111111)

      // BLUE bar

      if(blue == 0) blue = 0;                               // 0 leds on
      else if(blue > 0 && blue <= 36) blue = 1;             // 1 led on (binary system 1  =    00000001)
      else if(blue > 36 && blue <= 72) blue = 3;            // 2 led on (binary system 3  =    00000011)
      else if(blue > 72 && blue <= 108) blue = 7;           // 3 led on (binary system 7  =    00000111)
      else if(blue > 108 && blue <= 144) blue = 15;         // 4 led on (binary system 15  =   00001111)
      else if(blue > 144 && blue <= 180) blue = 31;         // 5 led on (binary system 31  =   00011111)
      else if(blue > 180 && blue <= 216) blue = 63;         // 6 led on (binary system 63  =   00111111)
      else if(blue > 216 && blue <= 255) blue = 127;        // 7 led on (binary system 127 =   01111111)


      // updating the shift registers 74HC595

      // RED shift register
      digitalWrite(latchPinR, LOW);                      // switching off the leds
      shiftOut(dataPinR, clockPinR, MSBFIRST, red);      // updating the values
      digitalWrite(latchPinR, HIGH);                     // switching on the leds

      // GREEN shift register
      digitalWrite(latchPinG, LOW);
      shiftOut(dataPinG, clockPinG, MSBFIRST, green);
      digitalWrite(latchPinG, HIGH);

      // BLUE shift register
      digitalWrite(latchPinB, LOW);
      shiftOut(dataPinB, clockPinB, MSBFIRST, blue);
      digitalWrite(latchPinB, HIGH);

    }
  }
}







