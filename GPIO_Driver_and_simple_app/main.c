#include "stm32f446xx.h"
#include "gpio.h"
#include "main.h"

gpio_handle_t PB0,PC1;

int main(void){	
	RCC_TypeDef *CLK;
	CLK = RCC;
	
	CLK->CR |= (1 << 0);
	while (! CLK->CR & (1 << 1));
	CLK->CFGR |= (0x00 << 0);
	CLK->AHB1ENR |= (0x0F << 0);	
	
	PB0.Instance 		= 	GPIOB;
	PB0.Init.Mode 		= 	OUTPUT_MODE;
	PB0.Init.PP 		= 	PUPDR_NO;
	PB0.Init.Speed 		=	MEDIUM_SPEED;
	PB0.Init.Pin_num	= 	0;
	PB0.Init.Type		= 	PIN_TYPE_PUPD;
	
	PC1.Instance		= 	GPIOC;
	PC1.Init.Mode		= 	OUTPUT_MODE;
	PC1.Init.PP			= 	PIN_TYPE_PUPD;
	PC1.Init.Speed		= 	MEDIUM_SPEED;
	PC1.Init.Pin_num	= 	1;
	PC1.Init.Type		= 	PIN_TYPE_PUPD;
	
	GPIO_INIT(&PB0);
	GPIO_INIT(&PC1);
	
	int j=0;
	while(j < 5){
		GPIO_PIN_ON_OFF(&PB0, 1);
		for (int i=0;i<1000000;i++);
		GPIO_PIN_ON_OFF(&PB0, 0);
		for (int i=0;i<1000000;i++);
		GPIO_PIN_ON_OFF(&PC1, 1);
		for (int i=0;i<1000000;i++);
		GPIO_PIN_ON_OFF(&PC1, 0);
		for (int i=0;i<1000000;i++);
		j++;
	}
	
	return 0;
}
