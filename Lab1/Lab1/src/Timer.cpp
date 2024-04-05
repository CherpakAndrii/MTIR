// #include "Timer.h"
// #include "App.h"


// extern "C" void TIM1_UP_IRQHandler(){
//     App::instance()->onTimerElapsed();
// }

// Timer::Timer() : Timer::Timer(HCLK, TICKS_PER_SECOND) {  }

// Timer::Timer(uint8_t mhz, uint8_t ticks_per_second){

//     RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;             // Вмикаємо ТЧ для таймера 1
//     TIM1->PSC = mhz*1000 - 1;                       // налаштували на mhz МГц
//     TIM1->ARR = (uint32_t)(1000/ticks_per_second) - 1;                   // тригериться кожну секунду
//     TIM1->DIER |= TIM_DIER_UIE;             // Дозволяємо переривання за подією оновлення

//     NVIC_EnableIRQ(TIM1_UP_IRQn);           // Дозволяємо переривання від таймера 1
// }

// void Timer::run(){
//     TIM1->CR1 |= TIM_CR1_CEN;               // Встановлюємо біт Counter ENable у реєстрі CR1 у високий логічний рівень
// }

// void Timer::stop(){
//     TIM1->CR1 &= ~TIM_CR1_CEN;              // Встановлюємо біт Counter ENable у реєстрі CR1 у низький логічний рівень
// }
