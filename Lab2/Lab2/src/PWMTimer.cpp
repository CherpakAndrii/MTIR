#include "PWMTimer.h"
#include "App.h"

PWMTimer::PWMTimer() : PWMTimer::PWMTimer(HCLK, TICKS_PER_SECOND) {  }

PWMTimer::PWMTimer(uint8_t mhz, uint8_t ticks_per_second){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;             // Вмикаємо тактову частоту для порту A, щоб можна було використовувати GPIO

    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);// Скидаємо налаштування для піну 8 порту A
    GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1); // Налаштовуємо пін 8 порту A як альтернативну функцію вихідного сигналу

    GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);// Скидаємо налаштування для піну 8 порту A
    GPIOA->CRL |= (GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1); // Налаштовуємо пін 8 порту A як альтернативну функцію вихідного сигналу

    AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_PARTIALREMAP;
    
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;             // Вмикаємо ТЧ для таймера 1
    TIM1->PSC = mhz*1000 - 1;                       // налаштували на mhz МГц
    TIM1->ARR = (uint32_t)(1000/ticks_per_second) - 1;                   // тригериться кожну секунду
    TIM1->CCR1 = 250 - 1;                           // налаштовуємо зсув відносно основного виходу;
    TIM1->BDTR |= TIM_BDTR_MOE;                         // Вмикаємо основний вихід таймера
    TIM1->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC1NE | TIM_CCER_CC1P);  // Вмикаємо вихідний канал 1
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);   // Налаштовуємо режим виводу каналу 1 як неінвертований порівняльний режим
}

void PWMTimer::run(){
    TIM1->CR1 |= TIM_CR1_CEN;               // Встановлюємо біт Counter ENable у реєстрі CR1 у високий логічний рівень
}

void PWMTimer::stop(){
    TIM1->CR1 &= ~TIM_CR1_CEN;              // Встановлюємо біт Counter ENable у реєстрі CR1 у низький логічний рівень
}
void PWMTimer::changeTimerInterval(double sec){
    TIM1->ARR = (uint32_t)(sec*1000) - 1;
}
void PWMTimer::changePWM_CCR(double sec){
    TIM1->CCR1 = (uint32_t)(sec*1000) - 1;
}