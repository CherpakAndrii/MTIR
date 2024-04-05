#include "Rcc.h"

void Rcc::setup(uint8_t mhz){
    uint8_t pll_multiplier/*, ahb_prescaler*/;
    uint32_t ahb_prescaler_value;

    if (mhz < 3){
        pll_multiplier = 2;
        //ahb_prescaler = 8/mhz;
        ahb_prescaler_value = mhz == 2? 0x00000090U : 0x000000A0U;
    } else if (mhz%4 == 0){
        pll_multiplier = mhz/4;
        //ahb_prescaler = 1;
        ahb_prescaler_value = 0x00000000U;
    } else if (mhz%2 == 0){
        pll_multiplier = mhz/2;
        //ahb_prescaler = 2;
        ahb_prescaler_value = 0x00000080U;
    } else {
        pll_multiplier = mhz;
        //ahb_prescaler = 4;
        ahb_prescaler_value = 0x00000090U;
    }

    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);                 // Скидаємо налаштування PLL;
    RCC->CFGR |= /*RCC_CFGR_PLLMULL5*/(pll_multiplier - 2) * 0x40000;   // Встановлюємо необхідний множник PLL (враховуємо, що ще на 4 домножується)

    RCC->CR |= RCC_CR_PLLON;                                            // Вмикаємо PLL

    while ((RCC->CR & RCC_CR_PLLRDY) == 0) {}                           // Очікуємо, доки PLL буде готовий

    RCC->CFGR &= ~RCC_CFGR_SW;                                          // Вибираємо PLL як джерело системного годинника
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0) {}                      // Очікуємо, доки PLL стане джерелом системного годинника

    RCC->CFGR |= /*RCC_CFGR_HPRE_DIV2*/ahb_prescaler_value;             // Ділимо на необхідний прескейлер для HCLK
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                                   // Ділимо ТЧ для таймера (у даному випадку, не ділимо)
}