#pragma once

#include "PWMTimer.h"
#include "Led.h"
#include "Rcc.h"
#include "Adc.h"
#include "Terminal.h"
#include <memory>

#define HCLK 8
#define TICKS_PER_SECOND 1

extern "C" void USART2_IRQHandler();

class App{
    friend void USART2_IRQHandler();
public:
    static std::shared_ptr<App> instance();
    void onTimerElapsed();
    void run();
    App();
private:
    static std::shared_ptr<App> s_instance;
private:
    volatile bool m_led_is_active = true;
private:
    PWMTimer m_timer;
    Led m_led = Led(1);
    Rcc m_rcc;
    Terminal m_terminalW;
    Terminal m_terminalRW;
    Adc m_adc;
private:
    void receiveChar(char s);
};
