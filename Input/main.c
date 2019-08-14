#include "stm32f446xx.h"

int main(void){
	// Namjestanje clock-a ---------------------
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	pRCC->CR |= (0x01 << 0); // HSI ON
	
	while (! pRCC->CR & (1 << 1));
	
	pRCC->CFGR |= (0x00 << 0);
	
	pRCC->AHB1ENR |= (0x01 << 0);
	// -----------------------------------------
	// Namjestanje GPIOA porta kao input
	GPIO_TypeDef *pA;
	pA = GPIOA;
	
	pA->MODER |= (0x04 << 18); // PA9 i PA10 su namješteni
	
	pA->OTYPER |= (0 << 10); // push pull na 10 pinu
	
	pA->OSPEEDR |= (0x01 << 20); // medium speed na 10 pinu
	
	pA->PUPDR |= (0x02 << 18); // pull down na pin 9
	// -----------------------------------------
	// Upravljamo izlazom s ulazom
		
	while(1){
		if (pA->IDR & (1 << 9)){
			pA->BSRR |= (1 << 10);
		}
		else{
			pA->BSRR |= (1 << 26);
		}
	}
	
	return 0;
}
