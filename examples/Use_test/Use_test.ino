#include <tb.h>

#define pin1 4 
#define pin2 2 
tb button1(pin1);
tb button2(pin2, 60); //second value is threshold

void setup() {
   Serial.begin(115200);
}

void loop() {

  //Single tap
  if(button1.isClick()) Serial.println("Single tap");
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

}
