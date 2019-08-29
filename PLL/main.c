#include "stm32f446xx.h"

int main(void){
	RCC_TypeDef *pRCC;
	pRCC = RCC;
	
	FLASH_TypeDef *pFL;
	pFL = FLASH;
	
	// Reset CLK registers
	pRCC->CR &= 0x00000083;
	pRCC->PLLCFGR &= 0x24000010;
	
	// Setting up FLASH latency
	pFL->ACR |= (0x05 << 0);
	
	// Enable HSI clock 
	pRCC->CR |= (1 << 0);
	while (! pRCC->CR & (1 << 1));
	
	// Set HSI clock as PLL clock input
	pRCC->PLLCFGR |= (0 << 22);	
	
	// Input frequency scale HSI - 16 MHz, must be in range 1-2 MHz, if using HSI, PLLM must be at 16 
	// Set the multiplication factor of VCO - PLLM, PLLN, PLLP
	pRCC->PLLCFGR |= 
				(0x00 << 0) | (0x01 << 4) 	// PLLM
			| (0x00 << 8)	| (0x05 << 12) 	// PLLN
			| (0x00 << 16);								// PLLP
	
	// Enable PLL clock
	pRCC->CR |= (1 << 24);
	while (! pRCC->CR & (1 << 25));
	
	// Set PLL as system clock
	pRCC->CFGR |= (0x02 << 0);
	
	return 0;
}
