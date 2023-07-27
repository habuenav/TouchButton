# TouchButton
Esp32 library for touch pins, detect click, release, hold press and number of taps. 
Biblioteca Esp32 para pines táctiles, detecta clic, soltar, mantener presionado y numero de toques


#### English
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

#### Spanish
#### ¿Cómo usar la biblioteca?
1) Incluimos la biblioteca
*#include "tb.h"*
2) Inicialización del botón de una de las siguientes maneras:
*tb button1 (pin);*
*tb button1(pin, umbral);*
*umbral* - es un valor de tolerancia para lecturas táctiles
3) Es necesario que la información sobre clics esté siempre actualizada, por lo que lanzamos
*button1.update();* en void loop()
4) Funciones de la biblioteca:
   
*button1.isClicks(count)* - verdadero si los clics son iguales al valor de conteo, click(1) dobleclick(2), tres o más clics dependen del valor de conteo, de lo contrario falso

*button1.isHold()* - verdadero si el botón se mantiene presionado y ha transcurrido más tiempo desde que se mantuvo presionado que con un clic normal; de lo contrario, falso

*button1.isHolded()* - lo mismo que isHold(), pero con una pulsación devuelve verdadero solo una vez

*button1.isRelease()* - devuelve verdadero solo después de soltar el pin táctil

*button1.getTaps()* - devuelve el número de toques en los que se hizo clic
