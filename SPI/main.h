#include "stm32f446xx.h"

#define MASTER 		1
#define BIDI 			1
#define NON_INV		0
#define RISING		1
#define BIT_8			0
#define LSB				1
#define PRES_2		2
#define DISABLE		0

#define SEND_DATA	((uint8_t *)0xAA)
#define DATA_LEN	0x08

#define OUTPUT		(GPIOA->MODER 	|= 	(0x01 << 0))
#define	PUSH_PULL	(GPIOA->OTYPER 	|=	(0x00 << 0))
#define LOW				(GPIOA->OSPEEDR	|= 	(0x00 << 0))
#define PULL_UP		(GPIOA->PUPDR		|= 	(0x01 << 0))

#define PIN_OFF		(GPIOA->BSRR		|=	(0x01 << 16))
#define PIN_ON		(GPIOA->BSRR 		|=  (0x01 << 0))	
