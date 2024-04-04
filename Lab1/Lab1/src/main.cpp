// #include "stm32f103x6.h"
#include "App.h"

// void sleep(){
//     for (volatile int i = 0; i < 400000; i++){

//     }
// }


int main(){
    // RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // GPIOA->CRL |= GPIO_CRL_MODE0_0;
    // GPIOA->CRL |= GPIO_CRL_MODE1_0;
    // GPIOA->CRL |= GPIO_CRL_MODE2_0;
    // GPIOA->CRL |= GPIO_CRL_MODE3_0;

    App::instance();

    while (true)
    {
        // GPIOA->ODR |= GPIO_ODR_ODR0;
        // GPIOA->ODR |= GPIO_ODR_ODR2;
        // GPIOA->ODR &= ~GPIO_ODR_ODR3;
        // GPIOA->ODR &= ~GPIO_ODR_ODR1;
        // sleep();
        // GPIOA->ODR |= GPIO_ODR_ODR1;
        // GPIOA->ODR |= GPIO_ODR_ODR3;
        // GPIOA->ODR &= ~GPIO_ODR_ODR0;
        // GPIOA->ODR &= ~GPIO_ODR_ODR2;
        // sleep();
    }
    

    return 0;
}