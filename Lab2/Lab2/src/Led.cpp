#include "Led.h"

Led::Led(uint8_t pin){
    m_pin = pin;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                         // Вмикаємо ТЧ для порту А
    GPIOA->CRL |= /*GPIO_CRL_MODE0_0*/ (0x1UL << (m_pin*4));    // Налаштовуємо пін m_pin на порту A як вихідний зі швидкістю 10 МГц
}

void Led::on(){
    GPIOA->BSRR = /*GPIO_BSRR_BS0*/ (0x1UL << (m_pin));         // Встановлюємо пін m_pin у високий логічний рівень, тобто вмикаємо світлодіод
}

void Led::off(){
    GPIOA->BSRR = /*GPIO_BSRR_BR0*/ (0x1UL << (m_pin+16));      // Встановлюємо пін m_pin у низький логічний рівень, тобто вимикаємо світлодіод
}

void Led::toggle(){
    if (isOn()){
        off();
    }
    else {
        on();
    }
}

bool Led::isOn(){
    return GPIOA->ODR & /*GPIO_ODR_ODR0*/ (0x1UL << (m_pin));       // Перевіряємо логічний рівень піна m_pin
}