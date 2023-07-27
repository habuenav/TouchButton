# TouchButton
Esp32 library for touch pins, detect click, release, hold press and number of taps. Biblioteca Esp32 para pines táctiles, detecta clic, soltar, mantener presionado y numero de toques

#### How to use the library?
1) We connect the library
*#include "tb.h"*
2) Button initialization in one of the following ways:
*tb button1(pin);*
*tb button1(pin, threshold);*
*threshold* - is a tolerance value for readings touchs
3) It is necessary that information about clicks is always update, so we throw
*button1.update();* in void loop()
4) Library functions:
   
*button1.isClicks(count)* - true if clicks is equal to count value you can single(1) double(2), three or more clicks depend of count value , otherwise false

*button1.isHold()* - true if the button is held down and more time has elapsed since the start of holding it than with a normal click, otherwise false

*button1.isHolded()* - the same as isHold(), but with one hold it returns true only once

*button1.isRelease()* - returns true only after release touch pin

*button1.getTaps()* - returns the number of clicked taps
