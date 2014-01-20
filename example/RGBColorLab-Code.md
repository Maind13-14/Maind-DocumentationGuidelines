RGB Color Lab - Code
================


Title
--------
Different ways of displaying RGB colors through LEDs 

Description
--------
The code is developed on the Arduino framework. The project uses two Arduino (UNO and LEONARDO) because of the need of many pins to manage all the interface LEDs. The Arduino UNO is the main one, and the second drives the shift registers for the LED bars. The description is divided in two for the two codes.
RGB manager (main Arduino, UNO)
After the pin declaration for LEDs, photodiodes, sliders and the input switch and the variables to store their values comes the “extremities values” part relied to the photodiodes calibration:
Upper limits: maximum value achievable by using the white board as input.

Used values:   valinR_upL = 525, valinG_upL = 495, valinB_upL = 380
(see the table below)

Lower limits: much more tricky to find out. The process is the following:
1)	Reading the RGB channel values of each color board by printing the raw values of the photodiodes on the serial monitor.
2)	For each color board highlight the R, G or B channel needed to generate them.
3)	The lower limit value for each channel is between the lower highlight value and the most closed non-highlighted value of the channel list.

Used values:	valinR_lowL = 300, valinG_lowL = 190, valinB_lowL = 180
Here there are the calibration values we get:

R	G	B  
White	522	508	395  
Black	108	109	65  
Magenta	502	182	204  
Green	167	234	132  
Cyan	283	358	284  
Blue	175	207	203  
Orange	493	200	158  
Red	494	192	160  


In the setup() the serial connection is started and the pins defined.
The loop() part is divided in two main parts, one for the physical colors (switch == 1), and the second the sliders (switch == 0).
The physical colors (color boards) part read the values of the photodiodes on the analog input pins and set up the upper and lover limit of it using the calibrated values. Then it map them between 0 and 255 for the PWM outputs. After that it adjusts the sensibility by multiplying for 20 each RGB channel to have the maximum value once a primary color board is placed on front of the photodiodes.
The last operation is to send the RGB values divided by a comma on the serial port for the second Arduino.
The slider part stores each slider channel value in a variable by reading them from the analog input pins and it maps to 0-255 for the output. Then it sends the values on the serial port as before.
The last part of the program updates the single channel LEDs and the RGB LEDs to the new color values.

**Shift register manager (second ARDUINO, Leonardo)**

To manage each 595 shift register three pins are needed: clock, latch and data. The first part assigns the pins for each one. Three variables are declared to store the red, green and blue values send from the main Arduino.

In the setup() the serial connection is started and the pinMode defined.
In the loop() the program start by dividing the serial data once available in the three variable corresponding to each color. When the return command ‘\n’  is received the program enter in the LED bars updating part.
For each bar the values are sampled down from 0-255 to a range of 7 values each one corresponding an odd binary number to switch on the LEDs as a bar, that means:

from,	… to,	New value,	Binary equivalent
0	36	1	00000001  
37	72	3	00000011  
73	108	7	00000111  
109	144	15	00001111  
145	180	31	00011111  
181	216	63	00111111  
217	255	127	01111111  

After that the shift register 595 are updated with the new values: as first the program turn low (0) the latch pin to switch off the LED bars during the values sanding. Then whit the shiftOut() function it send the new value by updating all the 595 output pins and at the and he switch on the LEDs by touring high (1) the latch pin.

Libraries 
--------
None

Reference to other codes and projects
--------

[Arduino trcece svjetlo sa dva 74HC595](http://fritzing.org/projects/arduino-trcece-svjetlo-sa-dva-74hc595/ "Title")


License
--------
<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.

File
--------
Github path

Upload the source files of your application
