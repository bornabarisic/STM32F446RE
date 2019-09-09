#include "gpio.h"

/************ Helper Functions *******************/

/* GPIO_PIN_MODE function explanation
	Mode:   0 - input
			1 - output
			2 - alternate
			3 - analog                               
*/ 

static void GPIO_PIN_MODE(GPIO_TypeDef *pGPIO, uint32_t PIN_NUM, uint32_t MODE){
	if (MODE == MODER_INPUT_MODE){
		pGPIO->MODER |=	(0x00 << (2*PIN_NUM));
	}else if (MODE == MODER_OUTPUT_MODE){
		pGPIO->MODER |= (0x01 << (2*PIN_NUM));
	}else if (MODE == MODER_ALTERN_MODE){
		pGPIO->MODER |= (0x02 << (2*PIN_NUM));
	}else if (MODE == MODER_ANALOG_MODE){
		pGPIO->MODER |= (0x03 << (2*PIN_NUM));	
	}	
}

/* GPIO_OUTPUT_TYPE function explanation
	Type:   0 - output push pull
			1 - output open drain                               
*/ 

static void GPIO_OUTPUT_TYPE(GPIO_TypeDef *pGPIO, uint32_t PIN_NUM, uint32_t MODE, uint32_t TYPE){
	if ((MODE == MODER_OUTPUT_MODE)&&(TYPE == OTYPER_PUSH_PULL)){
		pGPIO->OTYPER |= (0 << PIN_NUM);
	}else if ((MODE == MODER_OUTPUT_MODE)&&(TYPE == OTYPER_OPEN_DRAIN)){
		pGPIO->OTYPER |= (1 << PIN_NUM);
	}		
}

/* GPIO_OUTPUT_SPEED function explanation
	Speed:  0 - low
			1 - medium
			2 - fast
			3 - high                               
*/ 

static void GPIO_OUTPUT_SPEED(GPIO_TypeDef *pGPIO, uint32_t PIN_NUM, uint32_t MODE, uint32_t SPEED){
	if ((MODE == MODER_OUTPUT_MODE)&&(SPEED == OSPEED_LOW_SPEED)){
		pGPIO->OSPEEDR |= (0x00 << (2*PIN_NUM));
	}else if ((MODE == MODER_OUTPUT_MODE)&&(SPEED == OSPEED_MED_SPEED)){
		pGPIO->OSPEEDR |= (0x01 << (2*PIN_NUM));
	}else if ((MODE == MODER_OUTPUT_MODE)&&(SPEED == OSPEED_FAS_SPEED)){
		pGPIO->OSPEEDR |= (0x02 << (2*PIN_NUM));
	}else if ((MODE == MODER_OUTPUT_MODE)&&(SPEED == OSPEED_HIG_SPEED)){
		pGPIO->OSPEEDR |= (0x03 << (2*PIN_NUM));
	}
}

/* GPIO_PIN_PUPDR function explanation
	Speed:  0 - no pull up or pull down
			1 - pull up
			2 - pull down
			3 - reserved                               
*/ 

static void GPIO_PIN_PUPDR(GPIO_TypeDef *pGPIO, uint32_t PIN_NUM, uint32_t PUPD){
	if (PUPD == PUPDR_NO_PUSH_PULL){
		pGPIO->PUPDR |= (0x00 << (2*PIN_NUM));
	}else if (PUPD == PUPDR_PULL_UP){
		pGPIO->PUPDR |= (0x01 << (2*PIN_NUM));
	}else if (PUPD == PUPDR_PULL_DOWN){
		pGPIO->PUPDR |= (0x02 << (2*PIN_NUM));
	}
}

/* GPIO_PIN_SET_RESET function explanation
	State:  0 - pin OFF
			1 - pin ON                              
*/

static void GPIO_PIN_SET_RESET(GPIO_TypeDef *pGPIO, uint32_t MODE, uint32_t PIN_NUM, uint32_t state){
	if ((state == 1)&&(MODE == MODER_OUTPUT_MODE)){
		pGPIO->BSRR |= (1 << PIN_NUM);
	}else if ((state == 0)&&(MODE == MODER_OUTPUT_MODE)){
		pGPIO->BSRR |= (1 << (PIN_NUM+16));
	}
}

/************ API Functions *******************/

void GPIO_INIT(gpio_handle_t *gpio_handle){	
	GPIO_PIN_MODE(gpio_handle->Instance, gpio_handle->Init.Pin_num, gpio_handle->Init.Mode);
	GPIO_OUTPUT_TYPE(gpio_handle->Instance, gpio_handle->Init.Pin_num, gpio_handle->Init.Mode, gpio_handle->Init.Type);
	GPIO_OUTPUT_SPEED(gpio_handle->Instance, gpio_handle->Init.Pin_num, gpio_handle->Init.Mode, gpio_handle->Init.Speed);
	GPIO_PIN_PUPDR(gpio_handle->Instance, gpio_handle->Init.Pin_num, gpio_handle->Init.PP);
}

void GPIO_PIN_ON_OFF(gpio_handle_t *gpio_handle, uint32_t state){
	GPIO_PIN_SET_RESET(gpio_handle->Instance, gpio_handle->Init.Mode, gpio_handle->Init.Pin_num, state);
}
