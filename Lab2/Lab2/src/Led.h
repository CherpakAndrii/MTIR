#pragma once

#include "stm32f103x6.h"

class Led{
public:
    Led(uint8_t pin);
    void on();
    void off();
    bool isOn();
    void toggle();
private:
    uint8_t m_pin;
};