#include "App.h"

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
    m_terminal.setup(HCLK);
}

void App::run(){
    m_timer.run();

    while (true)
    {
        m_led.toggle();
        if (m_terminal.hasNewCommand()){
            m_terminal.sendMsg("You sent " + m_terminal.getCommand() + "\r\n");
            m_terminal.clearCommand();
        }
        
        m_rcc.delay(1000);
    }
}

extern "C" void USART1_IRQHandler(){
    App::instance()->receiveChar(USART1->DR);
    USART1->SR &= ~USART_SR_RXNE;
}

void App::onTimerElapsed(){
    m_led.toggle();
}


void App::receiveChar(char s) {
    m_terminal.receiveChar(s);
}
