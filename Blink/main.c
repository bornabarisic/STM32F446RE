#include "stm32f446xx.h"

int main(void){
	// Prvo cu ospobiti sat do GPIOA portova
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	pRCC->CR |= (1 << 0); 							// Osbosobljavam HSI clock
	while (! pRCC->CR & (1 << 1)); 			// Delay dok clock nije stabilan
	pRCC->CFGR |= (0x00 << 0); 					// postavaljam HSI kao system clock
	pRCC->AHB1ENR |= (1 << 0);					// osposobljen clock do GPIO A 
	pRCC->AHB1ENR |= (1 << 1);					// za GPIO B
	pRCC->AHB1ENR |= (1 << 2);					// za GPIO C
	
	// Sada radim na podešavanju GPIO porta
	GPIO_TypeDef *pGPIOA, *pGPIOB, *pGPIOC;
	pGPIOA = GPIOA;
	pGPIOB = GPIOB;
	pGPIOC = GPIOC;
	
	pGPIOA->MODER |= (1 << 20); 				// namjestanje nacina rada pina gpio A 10 kao izlazni
	pGPIOB->MODER |= (1 << 10);
	pGPIOC->MODER |= (1 << 0);
	
	pGPIOA->OTYPER |= (0 << 10); 				// namjestam output kao push-pull 
	pGPIOB->OTYPER |= (0 << 5);
	pGPIOC->OTYPER |= (0 << 0);
	
	pGPIOA->OSPEEDR |= (1 << 20); 		// namjestanje brzine
	pGPIOB->OSPEEDR |= (1 << 10);
	pGPIOC->OSPEEDR |= (1 << 0);
	
	// Pali gasi LED diodu (ako bog da)
	int i,j=0;
	while(j<10){
		pGPIOA->BSRR |= (1 << 10); 				// ON
		for(i=0;i<500000;i++);
		pGPIOA->BSRR |= (1 << 26);				// OFF
		for(i=0;i<500000;i++);
		
		pGPIOB->BSRR |= (1 << 5);
		for(i=0;i<500000;i++);
		pGPIOB->BSRR |= (1 << 21);
		for(i=0;i<500000;i++);
		
		pGPIOC->BSRR |= (1 << 0);
		for(i=0;i<500000;i++);
		pGPIOC->BSRR |= (1 << 16);
		for(i=0;i<500000;i++);
		j++;
	}
	return 0;
}
