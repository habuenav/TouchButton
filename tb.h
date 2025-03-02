#ifndef TouchButton_h
#define TouchButton_h

#include <Arduino.h>
#include "driver/touch_pad.h"

// Habilita los mensajes de depuración si está definido.
#define MESSAGES
#if defined MESSAGES
   #define printLine(x) Serial.println(x)
#else
   #define printLine(x)
#endif

// Definiciones de tiempo por defecto
#ifndef ClickTIME
#define ClickTIME 50
#endif

#ifndef ResetTIME
#define ResetTIME 700
#endif

#define THRESHOLD_MULTIPLIER 0.66666f
#define THRESHOLD_PERCENTAGE_FACTOR 0.01f

class tb {
public:
    tb(uint8_t pin, uint8_t threshold = 70);
    inline IRAM_ATTR bool isTouched();
    bool isHold(short holdTime = 400);
    bool isReleased(short releaseTime = 400);
    bool isHolded(short holdedTime = 400);
    bool isClick();
    bool isClicks(uint8_t count);
    uint16_t valor;

private:
    inline long _touchTime(unsigned long now = millis());
    uint8_t _pin;
    uint8_t _threshold;
    unsigned long _touchStart = 0;
    unsigned long _lastTouchStart = 0;
    uint8_t _clickCount = 0;
    bool _isTouched = false;
    bool _isHolding = false;
    float _initialThreshold;

    void initializeTouchPad();
};

// Constructor
tb::tb(uint8_t pin, uint8_t threshold) : _pin(pin), _threshold(threshold) {
    initializeTouchPad();
}

void tb::initializeTouchPad() {
    touch_pad_init();
    touch_pad_io_init(static_cast<touch_pad_t>(_pin));
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    delay(10);
    touch_pad_set_cnt_mode(static_cast<touch_pad_t>(_pin), TOUCH_PAD_SLOPE_7, TOUCH_PAD_TIE_OPT_HIGH);
    touch_pad_config(static_cast<touch_pad_t>(_pin), 0);
    delay(40);
    touch_pad_read(static_cast<touch_pad_t>(_pin), &valor);
    _initialThreshold = valor * _threshold * THRESHOLD_PERCENTAGE_FACTOR;
    touch_pad_set_thresh(static_cast<touch_pad_t>(_pin), valor * THRESHOLD_MULTIPLIER);
}

inline IRAM_ATTR bool tb::isTouched() {
    touch_pad_read(static_cast<touch_pad_t>(_pin), &valor);
    return (valor < _initialThreshold);
}

inline long tb::_touchTime(unsigned long now) {
    long duration = 0;
    bool touching = isTouched();

    if (_touchStart) { duration = now - _touchStart; }
    if (touching && !_touchStart) { _touchStart = now; }
    if (!touching) { _touchStart = 0; }
    return touching ? duration : -duration;
}

bool tb::isClick() {
    long touchDuration = _touchTime(millis()); // Captura el tiempo una sola vez
    long timeSinceLastTouch = _touchStart - _lastTouchStart;
    if (timeSinceLastTouch > ResetTIME) {_clickCount = 0;}
    if (touchDuration > ClickTIME) {
        if (!_isTouched) {
            _lastTouchStart = _touchStart;
            _clickCount++;
            _isTouched = true;
            return true;
        }
    } 
  else { _isTouched = false; }
    return false;
}

bool tb::isClicks(uint8_t count) {
    if (isClick() && _clickCount == count) {
        _clickCount = 0;
        return true;
    }
    return false;
}

bool tb::isHold(short holdTime) {
    return _touchTime(millis()) > holdTime;
}

bool tb::isHolded(short holdedTime) {
    bool triggered = false;
    if (isHold(holdedTime) && !_isHolding) {
        _isHolding = true;
        triggered = true;
    }
    if (!isHold(holdedTime)) {
        _isHolding = false;
    }
    return triggered;
}

bool tb::isReleased(short releaseTime) {
      bool released = false;
    if (isHold(releaseTime)) { _isHolding = true; }
    if (_isHolding && !isHold(releaseTime)) {
        _isHolding = false;
        released = true;
    }
    return released;
}
#endif
