#include "Adc.h"

volatile uint32_t Adc::s_adcValue = 0;

extern "C" void ADC1_2_IRQHandler(){
    if (ADC1->SR & ADC_SR_EOS) {
        Adc::s_adcValue = ADC1->DR;
        ADC1->SR &= ~ADC_SR_EOS;
    }
}

void Adc::setup(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~GPIO_CRL_CNF0;

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    NVIC_EnableIRQ(ADC1_2_IRQn);

    ADC1->SMPR2 = ADC_SMPR2_SMP0;
    ADC1->CR1 |= ADC_CR1_EOSIE;
    ADC1->SR &= ~ADC_SR_EOS;
    ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t Adc::getValue(){
    return s_adcValue;
}