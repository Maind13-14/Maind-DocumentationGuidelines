RGB Color Lab - Hardware and Electronics
================

Title
--------
Detecting colors and displaying them using LEDs

Description
--------
The project is based on Arduino boards. The function is to analyze color and display them in different ways. There are two input options. The first is by reading the light intensity reflected by physical colored boards placed on front of three photodiodes covered by a color filter (red, blue and green respectively). Each one returns the amount of light it’s measuring, equivalent to the R,G and B color channels. Thanks to this system, each colored board is translated in RGB values. For a clear reading of the filtered photodiodes, they are placed in a black box and lighted with white LEDs on the box edges. The second input is a set of three sliders representing the RGB channels, which allow mixing and generating colors, displayed on the output panel part.
The upper box part is divided in three different displays representing the color outputs. The first display consists in three LED bars, one for each channel (RGB). The led bars are made out of 7 LEDs and display the amount of the relative color channel (255 means 7 LEDs on). Each LED bar is driven by a shift register 74HC595N controlled by a second Arduino. The second Arduino receive the information through the serial port from the main Arduino that manages the raw data of sliders and photodiodes.
The second display is made by three LEDs displaying the brightness of each RGB channel. The third display is a set of two RGB LEDs that display the mixed channel and show the final color. The second and third displays are connected to the main Arduino.
The electronic is mounted on two proto-boards and all the interface components (slider, LEDs, switch and photodiodes) are glued on the front panel and connected to the Arduino and proto boards by wires. Each LED is connected to a resistor to adjust the current.
The power supply is a 6VDC 800mA charger connected to the Vin pin of both Arduino.

Components list
--------


Reference to other projects
--------
None

License
--------

Files
--------
Github path
