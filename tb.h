#ifndef TouchButton_h
#define TouchButton_h
#include <Arduino.h>

#ifndef STICKING
#define STICKING 50
#endif
#ifndef TouchInterval
#define TouchInterval 125
#endif
#ifndef HoldTIME
#define HoldTIME 250
#endif
#ifndef RESETTIME
#define RESETTIME 300
#endif

class tb {
  public:
    tb(uint8_t pin, uint8_t threshold=50);

    void update();
    uint8_t getTaps();
    bool isClicks(uint8_t count);
    bool isHold();
    bool isHolded();
    bool isRelease();

  private:
    uint8_t _pin = 0;
    uint8_t _threshold = 50;


    uint32_t _previousTouchTime = 0;
    uint32_t _startTouchTime = 0;
    uint32_t _endTouchTime = 0;

    bool _pressedNow = false;
    bool _wasReleased = true;
    bool _isHolded = false;
    bool _isHoldedYet = false;
    bool _wasisHolded = false;
    bool _wasCleaned = true;
    uint8_t _numberOfTouches = 0;
    uint8_t _numberOfTouchesInTheEnd = 0;

    bool isTouched();
};

#endif