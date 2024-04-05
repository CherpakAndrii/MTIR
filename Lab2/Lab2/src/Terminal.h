#pragma once

#include "stm32f103x6.h"
#include <memory>

class Terminal{
public:
    Terminal() = default;
    void setup(uint8_t hclk, bool is_rw);
    void sendMsg(std::string msg);
    void receiveChar(char s);
    bool hasNewCommand();
    std::string getCommand();
    void clearCommand();
private:
    USART_TypeDef * m_USART;
    std::string m_cmd;
    std::string m_tempCmd;
    bool m_receiveCmd = false;
};