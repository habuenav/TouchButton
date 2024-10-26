#### **[[ENGLISH]](#spanish)**

# Breath

`Breath` es una librería que facilita el uso del sensor de presión (MPS20N0040D - HX710B) para la detección de soplo en proyectos como instrumentos electrónicos de viento (EWI).

<p align="center">
<img width="100%" src='https://i.postimg.cc/15tXcXJD/touch.png' title=''/>
</p>

## Características

- Codigo optimizado para obtener lecturas rapidas.
- Creado para Leer valores de soplo con el sensor (MPS20N0040D - HX710B), no funciona para obtener valores de presion.
- Calibración automática del valor inicial del sensor a 0.
- Ajuste de sensibilidad mediante un factor de resistencia.
- Configuración de límites de lectura y de salida máxima para adaptarse a las necesidades del proyecto.

## Requisitos

- **Placa**: Probado en placas Esp32, Esp32-S2, Esp32-C3 y Esp32-S3
- **Sensor**: (MPS20N0040D - HX710B)
- **IDE de Arduino**: Recomendado 1.8.10 o superior

## Instalación

1. Descarga el archivo ZIP de la librería desde [GitHub](https://github.com/habuenav/Breath).
2. En el IDE de Arduino, ve a **Sketch** > **Include Library** > **Add .ZIP Library...**.
3. Selecciona el archivo ZIP descargado para instalar la librería.

O tambien puedes Extraer el archivo ZIP del paso 1 en tu directorio de librerías de Arduino.

### Codigo de ejemplo
```
#include <Breath.h>
#define OUTPUT_PIN 13
#define CLOCK_PIN 12
Breath breath(OUTPUT_PIN, CLOCK_PIN);

void setup() {
  Serial.begin(115200);
  breath.setResistance(3);  // Ajustar la resistencia de soplo (1 = mínima, 5 = máxima).
  breath.setMaxOut(127);    // Establecer el valor máximo de salida.
}

void loop() {
  int16_t breathValue = breath.read();
  Serial.println(breathValue);
  delay(100);
}
```

## API
### Constructor

<b> Breath(byte output_pin, byte clock_pin): </b> Inicializa la clase Breath con el pin de salida de datos del sensor y el pin de reloj.

### Métodos

* <b> int16_t read():</b> Lee el valor del sensor, aplica la calibración y devuelve un valor ajustado que varía entre 0 y el valor máximo configurado.
* <b> void setResistance(uint8_t level):</b> Ajusta la sensibilidad del sensor, donde level puede ser un valor de 1 (mínima resistencia) a 5 (máxima resistencia).
* <b> void setMaxOut(uint8_t maxOut):</b> Define el valor máximo de salida que se obtendrá al leer el sensor.
* <b> void setMaxRead(uint16_t mRead):</b> Establece el límite superior de la lectura antes de aplicar el ajuste de salida.

### Notas

* El sensor de presión MPS20N0040D necesita una alimentación estable y debe ser conectado adecuadamente al ESP32.
* La librería incluye una función para ajustar la resistencia de soplo, permitiendo adaptarla a diferentes niveles de sensibilidad según la necesidad del proyecto.
* Los valores que establescas por medio de las funciones setMaxOut y setMaxRead afectan la sensibilidad y resistencia
* El valor recomendado para setMaxOut es 127 ya que es el maximo que se envia como parametro de velocidad segun el estandar MIDI
* El valor recomendaddo para setMaxRead es 255 pero puede ajustarse en un rango de 200 a 500, puedes probar con cual funciona mejor.

## Ejemplos

En la carpeta de examples del repositorio, encontrarás ejemplos adicionales que muestran cómo utilizar la librería Breath con el ESP32.

## Contribuciones

Las contribuciones son bienvenidas. Si encuentras un problema o tienes una sugerencia, por favor abre un issue o envía un pull request.


#### **[[SPANISH]](#english)** 

# TouchButton

TouchButton is a library designed to simplify the use of capacitive touch inputs with the ESP32, allowing you to easily detect touch interactions like clicks, holds, and releases.

<p align="center">
<img width="25%" src='https://static.wixstatic.com/media/99ba69_f4d46c2102c24d46a3c3661d1a71ab0c~mv2.jpg/v1/fill/w_668,h_581,al_c,q_85/99ba69_f4d46c2102c24d46a3c3661d1a71ab0c~mv2.jpg' title=''/>
</p>

## Features

- **Optimized for ESP32**: Uses the built-in touch_pad functionality.
- **Customizable Sensitivity**: Set the touch sensitivity threshold to adapt to different needs.
- **Touch Interactions**: Detects various touch events including single clicks, multiple clicks, holds, and releases.
- **Threshold Adjustment**: Automatically sets the sensitivity based on an initial reading.

## Requirements

- **Board** : Tested on Esp32 board.
- **Arduino IDE** : Recommended 1.8.10 or higher

## Instalation

1. Download the library ZIP file from GitHub .
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library... .
3. Select the downloaded ZIP file to install the library.

Or you can extract the ZIP file from step 1 into your Arduino libraries directory.

## Sample code

```
#include <TouchButton.h>
#define TOUCH_PIN T0  // Define the touch pin (T0 is an example)
tb touchButton(TOUCH_PIN, 70); // Create a touchButton instance with a 70% sensitivity threshold.

void setup() {
  Serial.begin(115200);
}
void loop() {
  if (touchButton.isClick())     { Serial.println("Single click detected!"); }
  if (touchButton.isHold(500))   { Serial.println("Hold detected for 500ms!"); }
  if (touchButton.isHolded(1000)){ Serial.println("Hold detected once at 1000ms!"); }
  if (touchButton.isRelease(300)){ Serial.println("Button released after being held for 300ms."); }
  delay(100);
}
```

## API

### Builder

tb(uint8_t pin, uint8_t threshold = 70): Initializes the TouchButton instance with the specified touch pin and sensitivity threshold.

## Methods

* <b> bool isTouched():</b> Returns true if the touch pad is currently being touched.
* <b> bool isHold(short HoldTIME = 400):</b> Returns true if the touch has been held for the specified time in milliseconds.
* <b> bool isHolded(short HoldedTIME = 400):</b> Returns true once if the touch has been held for the specified time, then resets when released.
* <b> bool isRelease(short ReleaseTIME = 400):</b> Returns true when the touch is released after being held for the specified time.
* <b> bool isClick():</b> Returns true if a single click is detected.
* <b> bool isClicks(uint8_t count):</b> Returns true if the specified number of clicks is detected.

### NOTES

The library uses the ESP32's internal touch_pad functionality, ensuring precise touch detection.
The threshold parameter allows you to adjust the sensitivity of the touch detection.
The time values (ClickTIME, HoldTIME, ResetTIME) can be adjusted based on the desired responsiveness.

## Examples

In the examples folder of the repository, you will find additional examples demonstrating how to use the TouchButton library with the ESP32.

## Contributions

Contributions are welcome. If you find a problem or have a suggestion, please open an issue or send a pull request.
