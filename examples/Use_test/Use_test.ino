#include <tb.h>
// Please don't use delay() function in your code 

#define pin1 4 
#define pin2 2 
tb button1(pin1);
tb button2(pin2, 40); //second value is threshold

void setup() {
   Serial.begin(115200);
}

void loop() {
  //Check and update button condition
  //If u use more then one button, you must write check() functions to all of them
  button1.update();
  button2.update();

  //Single tap
  if(button1.isClicks(1)) Serial.println("Single tap");
  //Double tap
  if(button1.isClicks(2)) Serial.println("Double tap");
  //Triple tap
  if(button1.isClicks(3)) Serial.println("Triple tap");

  // Do anything for long time when button is hold
  if(button1.isHold()) Serial.println("Hold");

  // Do anything for long time when button2 is hold
  if(button2.isHolded()) Serial.println("Holded");
  
  // Do anything one time when button was release
    if(button2.isRelease()){ Serial.println("Release");}

  //Take number of taps
    byte num = button2.getTaps();
    if (num > 0) {
      Serial.print(num);
      Serial.println(" tap(s)");
    }
}