#include "Terminal.h"

void Terminal::setup(uint8_t hclk, bool is_rw){
    if (is_rw){
        m_USART = USART2;
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

        m_USART->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
        NVIC_EnableIRQ(USART2_IRQn);
    }
    else{
        m_USART = USART1;
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }
    m_USART->BRR = hclk*1000000 / 9600;
    m_USART->CR1 |= USART_CR1_UE;
}

void Terminal::sendMsg(std::string msg){
    for (char c : msg){
        while ((m_USART->SR & USART_SR_TC) == 0) { }

        m_USART->DR = c;
    }
}

void Terminal::receiveChar(char s) {
    if (s == '\r') {
        m_cmd = m_tempCmd;
        m_receiveCmd = true;
        m_tempCmd = "";
    }
    else if (!(m_tempCmd == "" && s == ' ')) {
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