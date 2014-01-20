/* 
 Title: RGB Color Lab
 Author: Marco Lurati and Orly Golan
 Teacher: Massimo Banzi
 Course: 1.7 Creating Tangible
 Year: 2013
 
 Code title: RGB manager
 Hardware: Arduino uno
 */

// LEDS

const int pLR = 6;          // Channel LEDs pins (PWM)
const int pLG = 5;
const int pLB = 3;

const int pRGB_R = 11;        // single RGB LED pins (PWM)
const int pRGB_G = 10;
const int pRGB_B = 9;

// SLIDERS

int valpotR;              // sliders values
int valpotG;
int valpotB;


// PHOTODIODES

int valinR;              // light intensity values from photodiods
int valinG;
int valinB;

int valLR;                // between values (for calculations) for each channel
int valLG;
int valLB;


int valChR;              // used to store the value of each single channel used to set up the various leds
int valChG;
int valChB;


// SWITCH BUTTON

const int pinChoice = 2;        // switch pin to choose the input between physical colors (photodiodes) and sliders
int inChoice;                   // value of the witch state (0 or 1)


// EXTREMITIES VALUES (from calibration)                            

int valinR_upL = 525;       // maximum values of the photodiodes by using the white board (they will be used to set the value 255)
int valinG_upL = 495;
int valinB_upL = 380;

int valinR_lowL = 300;      // lower limit of the photodiodes by picking up from the readout of the RGB values of each colored board,
int valinG_lowL = 190;      // which is the limit value that allow to distingue one color of an other (they will be used to set the vlaue 0)
int valinB_lowL = 180;


void setup(){

  pinMode(pLR, OUTPUT);            // channel leds pins definition
  pinMode(pLG, OUTPUT);
  pinMode(pLB, OUTPUT);

  pinMode(pRGB_R, OUTPUT);            // RGB leds pins definition
  pinMode(pRGB_G, OUTPUT);
  pinMode(pRGB_B, OUTPUT);

  Serial.begin(115200);            // starting serial communication (heigher bitrate to properly send all the values)

}

void loop(){

  inChoice = digitalRead(pinChoice);          // read the state of the switch

  // PHYSICAL COLORS MANAGING //

  if(inChoice == 1){                    // switch to 1 means read color from photodiodes

    valinR = analogRead(0);                      // red photodiode readout
    valinG = analogRead(1);                      // green photodiode readout
    valinB = analogRead(2);                      // blue photodiode readout

    /*
     Serial.print(valinR);                // Uncomment to read the photodiodes raw data for the calibration to define the lower limits to distingue the colors
     Serial.print(" - ");
     Serial.print(valinG);
     Serial.print(" - ");
     Serial.println(valinB);
     */

    if(valinR > valinR_upL) valinR = valinR_upL;         // set up of the maximum value for the three channels (upper limit, white)      
    if(valinG > valinG_upL) valinG = valinG_upL;
    if(valinB > valinB_upL) valinB = valinB_upL;

    if(valinR < valinR_lowL) valinR = valinR_lowL;       // set up of the minimum value for the three channels (lower limit, black) 
    if(valinG < valinG_lowL) valinG = valinG_lowL;
    if(valinB < valinB_lowL) valinB = valinB_lowL;

    valLR = map(valinR, valinR_lowL, valinR_upL, 0, 255);      // mapping function to reduce the value range to 0-255 
    valLG = map(valinG, valinG_lowL, valinG_upL, 0, 255);
    valLB = map(valinB, valinB_lowL, valinB_upL, 0, 255);



    // SENSIBILITY ADJUSTMENT

    if(valLR > 0){                    // sensibility increasing of each colors (20x) and limiting to a maximum value of 255
      valChR = valLR * 20;
      valChR = min(valChR, 255);
    }
    else valChR = 0;                 // default value of the channel to 0

      if(valLG > 0){
      valChG = valLG * 20;
      valChG = min(valChG, 255);
    }
    else valChG = 0;

    if(valLB > 0){
      valChB = valLB * 20;
      valChB = min(valChB, 255);
    }
    else valChB = 0;


    // Serial transmission to the shift register Arduino

    Serial.print(valChR);           // values of each channel sended by a comma division
    Serial.print(',');
    Serial.print(valChG);
    Serial.print(',');
    Serial.print(valChB);
    Serial.write('\n');            // end value of the transmission

  }

  // SLIDERS COLORS MANAGING

  if(inChoice == 0){                     // switch to 0

      valpotR = analogRead(3);                // potentiometer colors radout
    valpotG = analogRead(4);
    valpotB = analogRead(5);   

    valChR = map(valpotR, 0, 1024, 0, 254);        // analog values mapping to 0-255
    valChG = map(valpotG, 0, 1024, 0, 254);
    valChB = map(valpotB, 0, 1024, 0, 254);


    // Serial transmission to the shift register Arduino

    Serial.print(valChR);         // values of each channel sended by a comma division
    Serial.print(',');
    Serial.print(valChG);
    Serial.print(',');
    Serial.print(valChB);
    Serial.write('\n');          // end value of the transmission

  }

  // Leds update

    analogWrite(pLR, valChR);          // Channels leds updating
  analogWrite(pLG, valChG);
  analogWrite(pLB, valChB);

  // RGB led update

  analogWrite(pRGB_R, map(valChR, 0, 255, 0, 70));         // Red value adaption to obtain a reliable white once all the three channel are to the maximum
  analogWrite(pRGB_G, valChG);
  analogWrite(pRGB_B, map(valChB, 0, 255, 0, 15));         // Blue value adaption to obtain a reliable white once all the three channel are to the maximum

}








