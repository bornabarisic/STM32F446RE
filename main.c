#include "stm32f446xx.h"
#include <stdint.h>

uint16_t ADC_value = 0;
float Voltage = 0;
float a = 3.3/4097;
		
void SET_CLK(RCC_TypeDef *pRCC){
	// CLOCK registers reset
	pRCC->CR &= 0x00000083;
	pRCC->CFGR &= 0x00000000;
	pRCC->AHB1ENR &= 0x00100000;
	
	// CLOCK registers setup 
	pRCC->CR |= (1 << 0);
	while(! pRCC->CR & (1 << 1));
	pRCC->CFGR |= (0x00 << 0) | (0x00 << 4) | (0x00 << 10) | (0x00 << 14);
	pRCC->AHB1ENR |= (0x04 << 0);
	pRCC->APB2ENR |= (1 << 8);
}

void SET_GPIO(GPIO_TypeDef *pGPIO){	
	// GPIO registers reset
	pGPIO->MODER &= 0x00000000;
	pGPIO->PUPDR &= 0x00000000;
	
	// GPIO registers setup 
	pGPIO->MODER |= (0x03 << 0);
	pGPIO->PUPDR |= (0x00 << 0);
}

void SET_ADC(ADC_TypeDef *pADC){
	// Reseting registers
	ADC123_COMMON->CCR &= 0x00000000;
	pADC->CR1 &= 0x00000000;
	pADC->CR2 &= 0x00000000;
	pADC->SMPR2 &= 0x00000000;
	pADC->SQR1 &= 0x00000000;
	
	// Selecting operating mode od ADC as independent
	ADC123_COMMON->CCR |= (0x00 << 0);
	// Disable scan mode
	pADC->CR1 |= (0 << 8);
	// Continuous conversaton mode, right alligned data, disable external trigger x2 
	pADC->CR2 |= (1 << 1) | (0 << 11) | (0x00 << 20) | (0x00 << 28);
	// Nuber of cycles (84)
	pADC->SMPR1 |= (0x04 << 0);
	// Nuber of conversations (1),
	pADC->SQR1 |= (0x00 << 20); 		
	pADC->SQR3 |= (0x0A << 0);
	// ADC ON
	pADC->CR2 |= (1 << 0);
}

int main(void){	
	SET_CLK(RCC);
	SET_GPIO(GPIOC);
	SET_ADC(ADC1);
	
	while(1){		
		// start conversation
		ADC1->CR2 |= (1 << 30);		
		// wait for conversation to stop
		while (! ADC1->SR & (1 << 1));
		
		ADC_value = ADC1->DR;	

		Voltage = a * ADC_value;
	}	
	
	return 0;
}
