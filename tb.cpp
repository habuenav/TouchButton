#include "tb.h"
#include <Arduino.h>


//Contructor
tb::tb(uint8_t pin, uint8_t threshold) {
  _pin = pin;
  _threshold=threshold;
}

//detect touchs 
bool tb::isTouched() {
byte value1,value2,value;
  value1=touchRead(_pin);
  value2=touchRead(_pin);
  value = ( value1 > value2 ) ? value1 : value2;
if(value<=_threshold){ return true;}  
else if(value>_threshold && value<=_threshold+10){ return (touchRead(_pin)<=_threshold) ? true: false;  }
else if(value>_threshold){ return (touchRead(_pin)>_threshold) ? false: true; }

}

void tb::update() {
  uint32_t t = millis();
  _pressedNow = isTouched();

  //Recording start time
  if (_wasReleased == _pressedNow && _pressedNow && t - _endTouchTime >= STICKING) {
    _wasReleased = !_wasReleased;
    _startTouchTime = t;
  }

  //Recording the end time of pressing
  if (_wasReleased == _pressedNow && !_pressedNow  && t - _previousTouchTime >= STICKING) {
    _wasReleased = !_wasReleased;
    _endTouchTime = t;
    //Click increment if less than hold time has elapsed
    if (_endTouchTime - _startTouchTime < HoldTIME) {
      _numberOfTouches++;
      _wasCleaned = false;
    }
  }

  //Write an assertion
  if (!_wasReleased && t - _startTouchTime >= HoldTIME) {
    _isHolded = true;
    _wasCleaned = false;
  }

  //Record how many clicks were made and reset the counter
  if (!_wasCleaned && _wasReleased && t - _endTouchTime >= TouchInterval) {
    _numberOfTouchesInTheEnd = _numberOfTouches;
    _numberOfTouches = 0;
    _wasCleaned = true;
  }

  //When the button is released
  if (_wasReleased && t + TouchInterval - _endTouchTime >= RESETTIME) {
    _isHolded = false;
    _isHoldedYet = false;
    _numberOfTouchesInTheEnd = 0;
  }

  // Anti-bounce
  if (_pressedNow) _previousTouchTime = t;
}

//Get the number of clicks
uint8_t tb::getTaps() {
  uint8_t num = _numberOfTouchesInTheEnd;
  _numberOfTouchesInTheEnd = 0;
  return num;
}

//return number clicks
bool tb::isClicks(uint8_t count) {
  if (_numberOfTouchesInTheEnd == count) {
    _numberOfTouchesInTheEnd = 0;
    return true;
  }
  else return false;

}

//hold
bool tb::isHold() {
  if (_isHolded) return true;
  else return false;
}

//holded
bool tb::isHolded() {
  if (_isHolded && !_isHoldedYet) {
    _isHoldedYet = true;
    return true;
  }
  else return false;
}

//release
bool tb::isRelease() {
  if (_isHolded) {   _wasisHolded =true;   }
 if(_wasisHolded && !_isHolded) {_wasisHolded =false; return true; }
 else { return false;  }

}