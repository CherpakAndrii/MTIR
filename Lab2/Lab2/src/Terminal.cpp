#include "Terminal.h"

void Terminal::setup(uint8_t hclk){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1-> BRR = hclk*1000000 / 9600;
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);

    NVIC_EnableIRQ(USART1_IRQn);
}

void Terminal::sendMsg(std::string msg){
    for (char c : msg){
        while ((USART1->SR & USART_SR_TC) == 0) { }

        USART1->DR = c;
    }
}

void Terminal::receiveChar(char s) {
    if (s == '\r') {
        m_cmd = m_tempCmd;
        m_receiveCmd = true;
        m_tempCmd = "";
    }
    else{
        m_tempCmd.push_back(s);
    }
}

bool Terminal::hasNewCommand(){
    return m_receiveCmd;
}
std::string Terminal::getCommand(){
    return m_cmd;
}

void Terminal::clearCommand(){
    m_cmd = "";
    m_receiveCmd = false;
}