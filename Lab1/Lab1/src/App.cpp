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
    m_timer.run();
}

void App::onTimerElapsed(){
    if (m_button.clicked()){
        m_led_1_5.toggle();
    } else{
        m_led_6_10.toggle();
    }
}

void App::onButton1Changed(){
    if (m_button.clicked()){
        m_led_6_10.off();
    }
    else{
        m_led_1_5.off();
    }
}



void App::onButton2Changed(){
    
}