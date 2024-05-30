#include "App.h"
#include "command_methods.h"

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
    m_adc.setup();
    m_terminalW.setup(HCLK, false);
    m_terminalRW.setup(HCLK, true);
}

void App::run(){
    m_timer.run();

    while (true)
    {
        if (m_led_is_active) m_led.toggle();
        if (m_terminalRW.hasNewCommand()){
            std::string command = m_terminalRW.getCommand();
            if (command == "ON") {
                m_led_is_active = true;
                m_terminalRW.sendMsg("Led swithed on!\r\n");
            } else if (command == "OFF") {
                m_led_is_active = false;
                m_led.off();
                m_terminalRW.sendMsg("Led swithed off!\r\n");
            } else if (n_commands.is_SETTIM(command)) {
                double secs = n_commands.get_SETTIM_param(command);
                m_timer.changeTimerInterval(secs);
                std::string ssecs = n_commands.double_to_str(secs, 3);
                m_terminalRW.sendMsg("Timer interval changed to " + ssecs + " seconds \r\n");
            } else if (n_commands.is_SETPWM(command)) {
                // m_terminalRW.sendMsg("OK \r\n");
                double secs = n_commands.get_SETPWM_param(command);
                // m_terminalRW.sendMsg("PARSED \r\n");
                m_timer.changePWM_CCR(secs);
                std::string ssecs = n_commands.double_to_str(secs, 3);
                // m_terminalRW.sendMsg("CONVERTED \r\n");
                m_terminalRW.sendMsg("PWM offset changed to " + ssecs + " seconds \r\n");
            } else{
                m_terminalRW.sendMsg("Command \"" + command + "\" doesn't exist!\r\n");
            }
            m_terminalRW.clearCommand();
        }
        m_terminalW.sendMsg("adc = " + std::to_string(m_adc.getValue()) + "\r\n");
        m_rcc.delay(1000);
    }
}

extern "C" void USART2_IRQHandler(){
    App::instance()->receiveChar(USART2->DR);
    USART2->SR &= ~USART_SR_RXNE;
}

void App::onTimerElapsed(){
    if (m_led_is_active){
        m_led.toggle();
    }
}


void App::receiveChar(char s) {
    m_terminalRW.receiveChar(s);
}
