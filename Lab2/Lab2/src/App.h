#pragma once

#include "PWMTimer.h"
#include "Led.h"
#include "Rcc.h"
#include <memory>
#include <functional>

#define HCLK 8
#define TICKS_PER_SECOND 1

class App{
public:
    static std::shared_ptr<App> instance();
    void onTimerElapsed();
    void run();
    void sendMsg(std::string msg);
    void receiveChar(char s);
    App();
private:
    void initUsart1();
    // void initUsart2();
    static std::shared_ptr<App> s_instance;
    PWMTimer m_timer;
    Led m_led = Led(0);
    Rcc m_rcc;
    std::string m_cmd;
    std::string m_tempCmd;
    bool m_receiveCmd = false;
};

extern "C" void USART1_IRQHandler();
// extern "C" void USART2_IRQHandler();