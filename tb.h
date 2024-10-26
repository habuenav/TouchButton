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

class tb {
public:
    tb(uint8_t pin, uint8_t threshold = 70);
    inline bool IRAM_ATTR isTouched();
    bool isHold(short HoldTIME = 400);
    bool isRelease(short ReleaseTIME = 400);
    bool isHolded(short HoldedTIME = 400);
    bool isClick();
    bool isClicks(uint8_t count);
    uint16_t valor;

private:
    inline long IRAM_ATTR _touchTime();
    uint8_t _pin;
    uint8_t _threshold;
    unsigned long _touchStart = 0;
    unsigned long _oldT = 0;
    uint8_t _cont = 0;
    bool _pushed = false;
    bool result=false;
    bool _Hold = false;
    float initialThreshold;

    void initializeTouchPad();
};

// Constructor
tb::tb(uint8_t pin, uint8_t threshold) {
    _pin = pin;
    _threshold = threshold;
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
    initialThreshold = valor * _threshold * 0.01;
    touch_pad_set_thresh(static_cast<touch_pad_t>(_pin), valor * 0.66666f);
}

inline bool IRAM_ATTR tb::isTouched() {
    touch_pad_read(static_cast<touch_pad_t>(_pin), &valor);
    return (valor < initialThreshold);
}

inline long IRAM_ATTR tb::_touchTime() {
    unsigned long now = millis();
    long result = 0;
    bool touching = isTouched();
    if (_touchStart) {
        result = now - _touchStart;
    }
    if (touching && !_touchStart) {
        _touchStart = now;
    }
    if (!touching) {
        _touchStart = 0;
        _pushed = false;
    }
    return touching ? result : -result;
}

bool tb::isClick() {
    long touchTime = _touchTime();
    long t = _touchStart - _oldT;
    if (t > ResetTIME) {
        _cont = 0;
    }
    if (touchTime > ClickTIME) {
        if (!_pushed) {
            _oldT = _touchStart;
            _cont++;
            _pushed = true;
        }
    } else {
        _pushed = false;
    }
    return _pushed;  // Devuelve el estado de `_pushed`
}

bool tb::isClicks(uint8_t count) {
    result = false;
    if (isClick()) {
        if (_cont == count) {
            _cont = 0;
            result = true;
        }
    }
    return result;
}

bool tb::isHold(short HoldTIME) {
    return _touchTime() > HoldTIME;
}

bool tb::isHolded(short HoldedTIME) {
   result = false;
    if (isHold(HoldedTIME) && !_Hold) {
        _Hold = true;
        result = true;
    } 
    if (_Hold && !isHold(HoldedTIME)) {
        _Hold = false;
    }
    return result;
}

bool tb::isRelease(short ReleaseTIME) {
  result = false;
    if (isHold(ReleaseTIME)) {
        _Hold = true;
    }
    if (_Hold && !isHold(ReleaseTIME)) {
        _Hold = false;
        result = true;
    }
    return result;
}
#endif
