#include <Bridge.h>
#include <Temboo.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *myMotor = AFMS.getStepper(25, 2);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(600, 1);
Servo servo1;

String ADDRESS_FOR_FORECAST = "Lugano";

int condition;

const int COLD = 3;
const int RAIN = 2;
const int CLOUDY = 8;
const int WINDY = 4;
const int HOT = 6;
const int NIGHT = 5;
const int FAIRWEATHER = 1;
const int SNOW = 7;

int weather = 1;
int temp = 0;
int steps = 0;
int weatherSteps = 0;
int previousTemp = 0;
int previousWeather = 1;
int servoTurn = 90;
int weatherSet = 0;

int count = 0;

String currentCity;


long dayLevel = -999;
int day = 1;
int previousDay = 0;

void setup() {
  Serial.begin(9600);
  delay(4000);
  while (!Serial);
  Bridge.begin();

  AFMS.begin();

  servo1.attach(10);

  myMotor->setSpeed(300);  // 10 rpm
  myMotor2->setSpeed(300);

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  Serial.println("Starting...");
}

void loop()
{
  selectCity();
  Serial.print("Day:");
  Serial.println(day);

  if ((ADDRESS_FOR_FORECAST != currentCity) || (weatherSet != 2) || (count > 30) || (previousDay != day))
  {
    servoTurn = 90;
    servo1.write(servoTurn);
    weatherSet = 0;
    getWeather();
    count = 0;

  }


  Serial.println("Waiting...");
  Serial.print(count);
  Serial.println("");
  delay(10000); // wait 30 seconds between GetWeatherByAddress calls
  count++;
}


void getWeather() {
  // print status
  Serial.println("Running GetWeatherByAddress");

  // create a TembooChoreo object to send a Choreo request to Temboo
  TembooChoreo GetWeatherByAddressChoreo;

  // invoke the Temboo client
  GetWeatherByAddressChoreo.begin();

  GetWeatherByAddressChoreo.setSettingsFileToRead("/mnt/sda1/cuckooSettings");

  GetWeatherByAddressChoreo.addInput("Address", ADDRESS_FOR_FORECAST);

  GetWeatherByAddressChoreo.run();

  // when the choreo results are available, print them to the serial monitor
  while (GetWeatherByAddressChoreo.available()) {

    //char c = GetWeatherByAddressChoreo.read();
    //Serial.print(c);

    // read the name of the output item
    String name1 = GetWeatherByAddressChoreo.readStringUntil('\x1F');
    name1.trim();
    Serial.println(name1);
    // read the value of the output item
    String data = GetWeatherByAddressChoreo.readStringUntil('\x1E');
    data.trim();


    if ((name1 == "day1condition") && (day == 1)) {
      condition = data.toInt();
      Serial.print("day1Condition: ");
      Serial.println(condition);
      setWeather();
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day1High") && (day == 1)) {
      temp = data.toInt();
      Serial.print("day1High(C): ");
      Serial.println(temp);
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day2condition") && (day == 2)) {
      condition = data.toInt();
      setWeather();
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day2High") && (day == 2)) {
      temp = data.toInt();
      Serial.print("day2High(C): ");
      Serial.println(temp);
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day3condition") && (day == 3)) {
      condition = data.toInt();
      setWeather();
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day3High") && (day == 3)) {
      temp = data.toInt();
      Serial.print("day3High(C): ");
      Serial.println(temp);
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day4condition") && (day == 4)) {
      condition = data.toInt();
      setWeather();
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day4High") && (day == 4)) {
      temp = data.toInt();
      Serial.print("day4High(C): ");
      Serial.println(temp);
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day5condition") && (day == 5)) {
      condition = data.toInt();
      setWeather();
      weatherSet = weatherSet + 1;
    }
    else if ((name1 == "day5High") && (day == 5)) {
      temp = data.toInt();
      Serial.print("day5High(C): ");
      Serial.println(temp);
      weatherSet = weatherSet + 1;
    }
    else if (name1 == "Error") {
      weatherSet = 0;
    }
  }
  GetWeatherByAddressChoreo.close();


  if (weatherSet > 1)
  {

    Serial.print("Weather:");
    Serial.println(weather);
    steps = 4 * (temp - previousTemp);
    if (weather == 8)
      weatherSteps = 25 * (weather - previousWeather);
    else
      weatherSteps = 22 * (weather - previousWeather);
    servoTurn = 150;
  }

  Serial.print("Steps:");
  Serial.println(steps);

  if (steps > 0)
    myMotor2->step(steps, FORWARD, MICROSTEP);
  else
    myMotor2->step(steps * (-1), BACKWARD, MICROSTEP);

  Serial.print("Weather Steps:");
  Serial.println(weatherSteps);

  if (weatherSteps > 0)
    myMotor->step(weatherSteps, FORWARD, MICROSTEP);
  else
    myMotor->step(weatherSteps * (-1), BACKWARD, MICROSTEP);

  servo1.write(servoTurn);

  previousTemp = temp;
  previousWeather = weather;
  previousDay = day;

  currentCity = ADDRESS_FOR_FORECAST;
  myMotor2->release();
  myMotor->release();
}

//Convert different weather code into 8 of the different states
void setWeather()
{
  if ((condition == 5) || (condition == 8) || (condition == 25) )
  {
    weather = COLD;
  }
  else if ((condition == 26) || (condition == 27) || (condition == 28) || (condition == 29) || (condition == 30) || (condition == 44))
  {
    weather = CLOUDY;
  }
  else if ((condition == 9) || (condition == 10) || (condition == 11) || (condition == 12) || (condition == 35) || (condition == 40) || (condition == 45) || (condition == 47))
  {
    weather = RAIN;
  }
  else if (condition == 31)
  {
    weather = NIGHT;
  }
  else if ((condition == 0) || (condition == 1) || (condition == 2) || (condition == 3) || (condition == 4) || (condition == 19) || (condition == 20) || (condition == 21) || (condition == 22) || (condition == 23) || (condition == 24) || (condition == 37) || (condition == 38) || (condition == 39))
  {
    weather = WINDY;
  }
  else if ((condition == 32) || (condition == 36))
  {
    weather = HOT;
  }
  else if ((condition == 33) || (condition == 34))
  {
    weather = FAIRWEATHER;
  }
  else if ((condition == 6) || (condition == 7) || (condition == 13) || (condition == 14) || (condition == 15) || (condition == 17) || (condition == 18) || (condition == 41) || (condition == 42) || (condition == 43) || (condition == 46) )
  {
    weather = SNOW;
  }
}




//
////Code to select city based on the potentiometer reading
void selectCity()
{

  int val = analogRead(A0);

  Serial.println("*************");
  Serial.println(val);

  if ((val >= 13) && (val <= 79))
  {
    ADDRESS_FOR_FORECAST = "Lugano";
  }
  else if ((val > 79) && (val <= 300))
  {
    ADDRESS_FOR_FORECAST = "Zurich";
  }
  else if ((val > 300) && (val <= 526))
  {
    ADDRESS_FOR_FORECAST = "London";
  }
  else if ((val > 526) && (val <= 760))
  {
    ADDRESS_FOR_FORECAST = "Barcelona";
  }
  else if ((val > 760) && (val < 970))
  {
    ADDRESS_FOR_FORECAST = "New York";
  }
  else if (val > 970)
  {
    ADDRESS_FOR_FORECAST = "Hawaiian Beaches";
  }
  Serial.println(ADDRESS_FOR_FORECAST);
}

void receiveEvent(int howMany) {
  Serial.println("Recieved data");
  day = Wire.read();    // receive byte as an integer
}

