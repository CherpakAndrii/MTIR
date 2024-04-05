#pragma once

#include "stm32f103x6.h"

extern "C" void SysTick_Handler();

class Rcc {
    public:
        Rcc() = default;
        void setup(uint8_t mhz);
        void initClock(uint8_t hclk);
        void delay(int ms);
};