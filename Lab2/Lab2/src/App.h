#pragma once

#include "PWMTimer.h"
#include "Led.h"
#include "Rcc.h"
#include "Terminal.h"
#include <memory>
#include <functional>

#define HCLK 8
#define TICKS_PER_SECOND 1

extern "C" void USART1_IRQHandler();

class App{
    friend void USART1_IRQHandler();
public:
    static std::shared_ptr<App> instance();
    void onTimerElapsed();
    void run();
    App();
private:
    static std::shared_ptr<App> s_instance;
    PWMTimer m_timer;
    Led m_led = Led(0);
    Rcc m_rcc;
    Terminal m_terminal;
    void receiveChar(char s);
};

extern "C" void USART1_IRQHandler();