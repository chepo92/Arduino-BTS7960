#pragma once

#include <Arduino.h>
#include "BTS7960Bridge.h"

class BTS7960Driver
{
public:
    BTS7960Bridge left;
    BTS7960Bridge right;

    BTS7960Driver(
        uint8_t leftEnable,
        uint8_t rightEnable,
        uint8_t leftForward,
        uint8_t leftReverse,
        uint8_t rightForward,
        uint8_t rightReverse,
        uint8_t leftCurrent = BTS7960Bridge::NO_PIN,
        uint8_t rightCurrent = BTS7960Bridge::NO_PIN,
        uint16_t leftAdcResolution = 1023,
        uint16_t rightAdcResolution = 1023);

    void enable();
    void disable();

    void forward(uint8_t pwm);
    void reverse(uint8_t pwm);

    void stop();
};
