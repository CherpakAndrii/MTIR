#pragma once

#include "Timer.h"
#include "Button.h"
#include "Led.h"
#include <memory>
#include <functional>

#define HCLK 8
#define TICKS_PER_SECOND 1

class App{
public:
    static std::shared_ptr<App> instance();
    void onButton1Changed();
    void onButton2Changed();
    void onTimerElapsed();
    App();
private:
    void initRcc(uint8_t mhz);
    static std::shared_ptr<App> s_instance;
    Timer m_timer;
    Button m_button = Button(1);
    Led m_led_1_5 = Led(0);
    Led m_led_6_10 = Led(2);
    Button m_button2 = Button(3);
};