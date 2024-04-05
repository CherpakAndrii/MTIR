#pragma once

#include "stm32f103x6.h"


class Rcc {
    public:
        Rcc() = default;
        void setup(uint8_t mhz);
};