#pragma once

#include "stm32f103x6.h"
#include <memory>

class Terminal{
public:
    Terminal() = default;
    void setup(uint8_t hclk);
    void sendMsg(std::string msg);
    void receiveChar(char s);
    bool hasNewCommand();
    std::string getCommand();
    void clearCommand();
private:
    std::string m_cmd;
    std::string m_tempCmd;
    bool m_receiveCmd = false;
};

extern "C" void USART1_IRQHandler();
// extern "C" void USART2_IRQHandler();