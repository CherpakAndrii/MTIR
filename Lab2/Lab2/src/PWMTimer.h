#pragma once

#include "stm32f103x6.h"

// extern "C" void TIM3_UP_IRQHandler();
// extern "C" void TIM1_UP_IRQHandler();

class PWMTimer{
public:
    PWMTimer(uint8_t mhz, uint8_t ticks_per_second);
    PWMTimer();
    void run();
    void stop();
    void changeTimerInterval(double sec);
    void changePWM_CCR(double sec);
};