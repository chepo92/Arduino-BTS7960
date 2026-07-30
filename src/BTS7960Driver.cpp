#include "BTS7960Driver.h"

BTS7960Driver::BTS7960Driver(
    uint8_t leftEnable,
    uint8_t rightEnable,
    uint8_t leftForward,
    uint8_t leftReverse,
    uint8_t rightForward,
    uint8_t rightReverse,
    uint8_t leftCurrent,
    uint8_t rightCurrent,
    uint16_t leftAdcResolution,
    uint16_t rightAdcResolution)
    :
    left(
        leftEnable,
        leftForward,
        leftReverse,
        leftCurrent,
        leftAdcResolution),
    right(
        rightEnable,
        rightForward,
        rightReverse,
        rightCurrent,
        rightAdcResolution)
{
}

void BTS7960Driver::enable()
{
    left.enable();
    right.enable();
}

void BTS7960Driver::disable()
{
    left.disable();
    right.disable();
}

void BTS7960Driver::forward(uint8_t pwm)
{
    left.forward(pwm);
    right.forward(pwm);
}

void BTS7960Driver::reverse(uint8_t pwm)
{
    left.reverse(pwm);
    right.reverse(pwm);
}

void BTS7960Driver::stop()
{
    left.stop();
    right.stop();
}
