#include "Button.h"
#include "App.h"

extern "C" void EXTI1_IRQHandler(){
    App::instance()->onButton1Changed();
    EXTI->PR = EXTI_PR_PR1;
}

extern "C" void EXTI3_IRQHandler(){
    App::instance()->onButton1Changed();
    EXTI->PR = EXTI_PR_PR3;
}

Button::Button(int8_t pin){
    m_pin = pin;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                             // Вмикаємо тактову частоту для порту A

    GPIOA->CRL &= ~/*GPIO_CRL_CNF1;*/(0x3UL << (2 + 4*m_pin));      // Налаштовуємо пін m_pin на порту A як вхідний без підтяжки (навіщо??)
    GPIOA->CRL |= /*GPIO_CRL_CNF1_1*/(0x2UL << (2+4*m_pin));        // Налаштовуємо пін m_pin на порту A як вхідний з підтяжкою до Vcc
    GPIOA->BSRR = /*GPIO_BSRR_BS1*/((0x1UL << m_pin));

    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                             // Вмикаємо тактову частоту для альтернативних функцій вводу/виводу
    AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA;                       // налаштовуємо порт А для зовнішніх переривань, значення для усіх пінів на порту спільне
    EXTI->RTSR |= /*EXTI_RTSR_TR1*/(0x1UL << (m_pin));              // Встановлюємо зростаюче та спадне переривання для піну
    EXTI->FTSR |= /*EXTI_FTSR_TR1*/(0x1UL << (m_pin));
    
    NVIC_EnableIRQ(/*EXTI1_IRQn*/(IRQn_Type)(6+m_pin));             // Дозволяємо переривання від EXTI{m_pin}

    EXTI->PR = /*EXTI_PR_PR1*/(0x1UL << (m_pin));                   // Скидаємо прапорець переривання для піну
    EXTI->IMR |= /*EXTI_IMR_MR1*/(0x1UL << (m_pin));                // Дозволяємо переривання від піну
}

bool Button::clicked(){
    return !(GPIOA->IDR & /*GPIO_IDR_IDR1*/(0x1UL << (m_pin)));     // Перевіряємо логічний рівень піну
}