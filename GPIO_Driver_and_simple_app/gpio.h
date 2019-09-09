#include "stm32f446xx.h"
#include <stdint.h>

/***********************************************************************
				General Purpose Input Output
				Register Bit Definitions
************************************************************************/

/************** Register Bit Definitions for GPIO_MODER register *******/
#define MODER_INPUT_MODE	(0x00UL) 
#define MODER_OUTPUT_MODE	(0x01UL)
#define MODER_ALTERN_MODE	(0x02UL)
#define MODER_ANALOG_MODE	(0x03UL)

/************** Register Bit Definitions for GPIO_OTYPER register ******/
#define OTYPER_PUSH_PULL	0
#define OTYPER_OPEN_DRAIN	1

/************** Register Bit Definitions for GPIO_OSPEEDR register *****/
#define OSPEED_LOW_SPEED	(0x00UL)
#define OSPEED_MED_SPEED	(0x01UL)
#define OSPEED_FAS_SPEED	(0x02UL)
#define OSPEED_HIG_SPEED	(0x03UL)

/************** Register Bit Definitions for GPIO_PUPDR register *******/
#define PUPDR_NO_PUSH_PULL	(0x00UL)
#define PUPDR_PULL_UP		(0x01UL)
#define PUPDR_PULL_DOWN		(0x02UL)

/************** Register Bit Definitions for GPIO_BSRR register *******/
#define BSRR_SET_PIN		1
#define BSRR_RESET_PIN		1

/***********************************************************************
				General Purpose Input Output
				Data structures
************************************************************************/

typedef struct{
	uint32_t Mode;
	uint32_t PP;
	uint32_t Speed;
	uint32_t Pin_num;
	uint32_t Type;
}gpio_init_t;

typedef struct HANDLE{
	GPIO_TypeDef *Instance;
	gpio_init_t Init;	
}gpio_handle_t;

/***********************************************************************
				General Purpose Input Output
				Driver Exposed APIs
************************************************************************/
void GPIO_INIT(gpio_handle_t *gpio_handle);

void GPIO_PIN_ON_OFF(gpio_handle_t *gpio_handle, uint32_t on_off);

