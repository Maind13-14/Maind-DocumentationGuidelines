WEATHER CUCKOO CLOCK
====================

Code Title
—————————-
Display temperature and show different birds with music based on weather read from yahoo.

Description
——————————-
The code works on the arduino IDE 1.5.5

**Arduino YUN**:*GetWeather*: This function reads weather from yahoo weather api using temboo libraries to connect from an arduino yun via Internet. A temboo choreo object is created with the address for which the weather is to be read, the day for forecast, the units for temperature. Temboo returns the high temperature and weather condition forecast based on the inputs. Tempoo returns the forecast for 5 days depending on the day selected the required weather and temperature is filtered out of the response. The weather and temperature difference from the previous weather is calculated and the motors are moved the corresponding steps. The servo is then turned 90 degree to push the bird out. By default the weather is read every 30 loops. Also once the weather is set the city and day are set to previous values so that if there is a change in the city or day the weather can be read again. The motors are controlled using the adafruit motor shield libraries.*SetWeather*: This function is used to convert the 47 different weather conditions returned by yahoo to a broader 8 different conditions.*SelectCity*: This function reads the potentiometer connected to the yun and maps the analog signal to 5 different cities.*recieveEvent*: Even registered to read the wire transmission from the uno and sets the day for which weather is to be forecasted. (Based on wired IC2 transmission)**Arduino UNO**:
The function checks for the rotary knob reading and selects the day for which the forecast is to be shown. The position is transmitted to the arduino Yun using IC2 communication. 
The level of the rotary is continuously read and when the change is stable for 100 seconds the day is calculated and transmitted using the wire library.

Libraries
————————-a.Adafruit motor shield libraries : Wire, Adafruit_MotorShield, utility/Adafruit_PWMServoDriver.h"b.Servo c.Library for yun : Bridge, tembooFor Setting Dayd.Encoder library for rotatory encoder: encodere.Wire for I2C communication.
