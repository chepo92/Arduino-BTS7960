#include "BTS7960Bridge.h"

BTS7960Bridge::BTS7960Bridge(
    uint8_t enablePin,
    uint8_t forwardPin,
    uint8_t reversePin,
    uint8_t currentSensePin,
    uint16_t adcResolution)
    :
    enablePin_(enablePin),
    forwardPin_(forwardPin),
    reversePin_(reversePin),
    currentSensePin_(currentSensePin),
    adcResolution_(adcResolution)
{
    pinMode(enablePin_, OUTPUT);

    pinMode(forwardPin_, OUTPUT);
    pinMode(reversePin_, OUTPUT);

    if (currentSensePin_ != NO_PIN)
        pinMode(currentSensePin_, INPUT);

    stop();
}

void BTS7960Bridge::enable()
{
    digitalWrite(enablePin_, HIGH);
}

void BTS7960Bridge::disable()
{
    digitalWrite(enablePin_, LOW);
}

void BTS7960Bridge::forward(uint8_t pwm)
{
    analogWrite(reversePin_, 0);
    analogWrite(forwardPin_, pwm);
}

void BTS7960Bridge::reverse(uint8_t pwm)
{
    analogWrite(forwardPin_, 0);
    analogWrite(reversePin_, pwm);
}

void BTS7960Bridge::stop()
{
    analogWrite(forwardPin_, 0);
    analogWrite(reversePin_, 0);
}

uint16_t BTS7960Bridge::currentRaw() const
{
    if (currentSensePin_ == NO_PIN)
        return 0;

    return analogRead(currentSensePin_);
}

float BTS7960Bridge::current() const
{
    if (currentSensePin_ == NO_PIN)
        return NAN;

    return static_cast<float>(currentRaw());
}
