#pragma once

#include <Arduino.h>

class BTS7960Bridge
{
public:
    static constexpr uint8_t NO_PIN = 0;

    BTS7960Bridge(
        uint8_t enablePin,
        uint8_t forwardPin,
        uint8_t reversePin,
        uint8_t currentSensePin = NO_PIN,
        uint16_t adcResolution = 1023);

    void enable();
    void disable();

    void forward(uint8_t pwm);
    void reverse(uint8_t pwm);
    void stop();

    uint16_t currentRaw() const;
    float current() const;

private:
    uint8_t enablePin_;
    uint8_t forwardPin_;
    uint8_t reversePin_;
    uint8_t currentSensePin_;

    uint16_t adcResolution_;
};
