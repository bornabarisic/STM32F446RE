#include "stm32f446xx.h"

#define DELAY 			5000000
#define INPUT_PIN 	13
#define OUTPUT_PIN 	7
#define EXTI_13 		0x02

void CLK_SETUP(RCC_TypeDef *pRCC){
	pRCC->CR |= (0x01 << 0);
	while (! pRCC->CR & (1 << 1));
	pRCC->CFGR |= (0x00 << 0);
	pRCC->AHB1ENR |= (1 << 2);
	pRCC->APB2ENR |= (1 << 14);
}

void GPIO_SETUP(GPIO_TypeDef *pGPIO){
	pGPIO->MODER |= (0x00 << (INPUT_PIN*2));
	pGPIO->MODER |= (0x01 << (OUTPUT_PIN*2));
	pGPIO->OTYPER |= (0 << OUTPUT_PIN);
	pGPIO->OSPEEDR |= (0x01 << (OUTPUT_PIN*2));
}

void GPIO_TO_EXTI(SYSCFG_TypeDef *pSYSCFG){
	pSYSCFG->EXTICR[3] |= (EXTI_13 << 4); 
}

void EXTI_TO_NVIC(EXTI_TypeDef *pEXTI){
	pEXTI->IMR |= (1 << 13);	
	pEXTI->FTSR |= (1 << 13);		
}

int main(void){
	CLK_SETUP(RCC);
	GPIO_SETUP(GPIOC);
	GPIO_TO_EXTI(SYSCFG);	
	EXTI_TO_NVIC(EXTI);
	
	while(1){
		if (EXTI->PR & (1 << 13)){
			EXTI->PR |= (1 << 13);
			GPIOC->BSRR |= (1 << 7);
			for (int i=0;i<DELAY;i++);
			GPIOC->BSRR |= (1 << 23);
			for (int i=0;i<DELAY;i++);
		}
	}
	
	return 0;
}
