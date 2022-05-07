# grow_clock

### Gro-Clock project
Designed to teach my children to stay in bed until an arbitrarily set time 

Has a nifty little OLED that displayst the time and day in front. An RGB LED that cycles through some arbitrary colors for a duration of six minutes (can be edited only from within the source code) aftwer a button push. and a micro servo that either shows a sun or hides it, indicating weather its time to get up or not. It is powered by a 9V wall wart adapter

### Setting the Time and Date
There are some constants defined in the begining of the source code that can be edited to personal preferrence

For the Real time clock unit to function you need to uncomment and edit the line //setDS3231time(25,36,21,6,6,5,22);
and within that line edit the seconds, minutes, hours, day, date, month, year
the clock is 24 hour format and the days start from Monday being 1, Tuesday 2 etc.

### Required Libs
editing the arduino source code requires downloading the SafeString library which can be found at 
https://www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html
which i used for the millisDelay functions

The OLED used  adafruit_SSD1306.h and the adafruit_GFX.h, the adafruit_SSD1306.h has dependancy requirements that the arduino IDE should auto download 


### part list
* Arduino Nano
* KY66 servo 
* HW-111 RTC module
* 1 x push button
* 3 x 220 ohm resistors
* 1 x common cathode RGB LED
* 1 x 12C 0.96-inch OLED display SSD1306 128x64 pixel IIC 3.3V 5V White Character Display
* WTA12-0901000-E 9v DC wall wart adaptor
* 1 x PCB mount DC005 5.5mm x 2.1mm 3 pin DC power connector socket
