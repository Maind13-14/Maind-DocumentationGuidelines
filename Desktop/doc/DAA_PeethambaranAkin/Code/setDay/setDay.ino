#include <Encoder.h>
Encoder knob(2, 3);
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

long dayLevel = -999;
void setup() {
  Wire.begin();
  Serial.begin(9600);
   //Serial.println("Day Forecast");
  //AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  myMotor->setSpeed(300);  // 10 rpm
  //myMotor->release();
}

unsigned long StartTime = 0;
unsigned long CurrentTime;
unsigned long ElapsedTime;

unsigned long StartTimeForecast = 0;
unsigned long CurrentTimeForecast;
unsigned long ElapsedTimeForecast;
int day = 1;
int flag = 0;
int previousDayLevel = 0;
char start='!';

void loop() {

  if(Serial.available())
  {
    start=Serial.read();
  }
    if(start=='!')
 { dayLevel = knob.read();
  delay(200);


  if (dayLevel != 0)
  {
    if (previousDayLevel == dayLevel)
    {
      if (StartTime == 0)
        StartTime = millis();
      else
      {
        CurrentTime = millis();
        ElapsedTime = CurrentTime - StartTime;
      }
    }
    else
      previousDayLevel = dayLevel;
  }
  //Write day to the yun if the dayLevel remains constant for 1 minute
  if (ElapsedTime > 10000)
  {
   
    if ((dayLevel > -29) && ( dayLevel < 30))
      day = 1;
    else if (((dayLevel > 29) && ( dayLevel < 89)) || ((dayLevel < -209) && ( dayLevel > - 279)))
      day = 5;
    else if (((dayLevel > 88) && ( dayLevel < 149)) || ((dayLevel < -148) && ( dayLevel > -209)))
      day = 4;
    else if (((dayLevel > 148) && ( dayLevel < 209)) || ((dayLevel < -88) && ( dayLevel > -149)))
      day = 3;
    else if (((dayLevel > 209) && ( dayLevel < 279)) || ((dayLevel < -29) && ( dayLevel > -89)))
      day = 2;

  

    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(day);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    //Wait 2 minutes and turn motor back to initial position and set knob to 0
    StartTime = 0;
    ElapsedTime = 0;
    knob.write(0);
    flag = 1;
    StartTimeForecast = millis();
  }

  CurrentTimeForecast = millis();

  if (flag == 1)
  {
    ElapsedTimeForecast = CurrentTimeForecast - StartTimeForecast;
    if (ElapsedTimeForecast > 10000)
    {

      Serial.println(previousDayLevel);
      start=0;
      knob.write(0);
      Wire.beginTransmission(4);
      Wire.write(1);
      Wire.endTransmission();
      previousDayLevel = 0;
      flag=0;
      
    }
  }

  myMotor->release();
  }
  }

