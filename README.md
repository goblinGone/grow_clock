# grow_clock

Gro clock project.

you need to un comment the line //setDS3231time(25,36,21,6,6,5,22);
and within that line edit the seconds, minutes, hours, day, date, month, year
the clock is 24 hour format and the days start from Monday being 1, Tuesday 2 etc.

editing the arduino source code requires downloading the SafeString library which can be found at 

https://www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html

## part list
* Arduino Nano
* KY66 servo 
* HW-111 RTC module
* 1 push button
* 3 220 ohm resistors
* 1 common cathode RGB LED
