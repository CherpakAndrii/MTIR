#include "App.h"

extern "C" void USART1_IRQHandler(){
    App::instance()->receiveChar(USART1->DR);
    USART1->SR &= ~USART_SR_RXNE;
}

// extern "C" void USART2_IRQHandler(){
//     App::instance()->receiveChar(USART1->DR);
//     USART1->SR &= ~USART_SR_RXNE;
// }

std::shared_ptr<App> App::s_instance = nullptr;

std::shared_ptr<App> App::instance(){
    if (!s_instance){
        s_instance = std::make_shared<App>();
    }
    return s_instance;
}

App::App(){
    m_rcc.setup(HCLK);
    m_rcc.initClock(HCLK);
    initUsart1();
    m_timer.run();
}

void App::run(){
    while (true)
    {
        m_led.toggle();
        if (m_receiveCmd){
            sendMsg("You sent " + m_cmd + "\r\n");
            m_receiveCmd = false;
        }
        
        m_rcc.delay(1000);
    }
}

void App::sendMsg(std::string msg){
    for (char c : msg){
        while ((USART1->SR & USART_SR_TC) == 0) { }

        USART1->DR = c;
    }
}

void App::receiveChar(char s) {
    if (s == '\r') {
        m_cmd = m_tempCmd;
        m_receiveCmd = true;
        m_tempCmd = "";
    }
    else{
        m_tempCmd.push_back(s);
    }
}

void App::onTimerElapsed(){
    m_led.toggle();
}

void App::initUsart1(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1-> BRR = HCLK*1000000 / 9600;
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);

    NVIC_EnableIRQ(USART1_IRQn);
}

// void App::initUsart2(){
//     RCC->APB2ENR |= RCC_APB1ENR_USART2EN;
//     USART2-> BRR = HCLK*1000000 / 9600;
//     USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);

//     NVIC_EnableIRQ(USART2_IRQn);
// }