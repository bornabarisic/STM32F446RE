#include "stm32f446xx.h"
#include <stdint.h>

/************************************************************
							SPI Configuration Register Bits				
*************************************************************/

/*						Configuration Bits SPI_CR1 Register						*/
#define 	SPI_CR1_CLK_PHASE_POS						(0U)
#define 	SPI_CR1_CLK_PHASE_RISE					(0x00UL << SPI_CR1_CLK_PHASE_POS)
#define		SPI_CR1_CLK_PHASE_FALL					(0x01UL << SPI_CR1_CLK_PHASE_POS)

#define 	SPI_CR1_CLK_POL_0								((uint32_t)0 << 1)
#define 	SPI_CR1_CLK_POL_1								((uint32_t)1 << 1)

#define 	SPI_CR1_SLAVE_MODE							((uint32_t)0 << 2)
#define 	SPI_CR1_MASTER_MODE							((uint32_t)1 << 2)

#define 	SPI_CR1_BAUD_RATE_2							((uint32_t)0 << 3)
#define 	SPI_CR1_BAUD_RATE_4							((uint32_t)1 << 3)
#define 	SPI_CR1_BAUD_RATE_8							((uint32_t)2 << 3)
#define 	SPI_CR1_BAUD_RATE_16						((uint32_t)3 << 3)
#define 	SPI_CR1_BAUD_RATE_32						((uint32_t)4 << 3)
#define 	SPI_CR1_BAUD_RATE_64						((uint32_t)5 << 3)
#define 	SPI_CR1_BAUD_RATE_128						((uint32_t)6 << 3)
#define 	SPI_CR1_BAUD_RATE_256						((uint32_t)7 << 3)

#define 	SPI_CR1_SPI_DISABLE							((uint32_t)0 << 6)
#define 	SPI_CR1_SPI_ENABLE							((uint32_t)1 << 6)

#define 	SPI_CR1_MSB_FRAME_FORMAT				((uint32_t)0 << 7)
#define 	SPI_CR1_LSB_FRAME_FORMAT				((uint32_t)1 << 7)

#define 	SPI_CR1_SOFT_SLAVE_MANAG_DIS		((uint32_t)0 << 9)
#define 	SPI_CR1_SOFT_SLAVE_MANAG_ENA		((uint32_t)1 << 9)

#define 	SPI_CR1_RX_ONLY_MODE_DISABLE		((uint32_t)0 << 10)
#define 	SPI_CR1_RX_ONLY_MODE_ENABLE			((uint32_t)1 << 10)

#define 	SPI_CR1_DATA_FRAME_FORMAT_8			((uint32_t)0 << 11)
#define		SPI_CR1_DATA_FRAME_FORMAT_16		((uint32_t)1 << 11)

#define		SPI_CR1_OUTPUT_DISABLE_BIDI			((uint32_t)0 << 14)
#define		SPI_CR1_OUTPUT_ENABLE_BIDI			((uint32_t)1 << 14)

#define 	SPI_CR1_UNI_MODE								((uint32_t)0 << 15)
#define 	SPI_CR1_BIDI_MODE								((uint32_t)1 << 15)


/*						Configuration Bits SPI_CR2 Register						*/
#define 	SPI_CR2_RX_BUFFER_DMA_DIS				((uint32_t)0 << 0)
#define 	SPI_CR2_RX_BUFFER_DMA_ENA				((uint32_t)1 << 0)

#define 	SPI_CR2_TX_BUFFER_DMA_DIS				((uint32_t)0 << 1)
#define 	SPI_CR2_TX_BUFFER_DMA_ENA				((uint32_t)1 << 1)

#define 	SPI_CR2_SS_OUTPUT_DIS						((uint32_t)0 << 2)
#define 	SPI_CR2_SS_OUTPUT_ENA						((uint32_t)1 << 2)

#define 	SPI_CR2_MOTOROLA_MODE						((uint32_t)0 << 4)
#define 	SPI_CR2_TI_MODE									((uint32_t)1 << 4)

#define 	SPI_CR2_ERROR_INT_DISABLE				((uint32_t)0 << 5)
#define 	SPI_CR2_ERROR_INT_ENABLE				((uint32_t)1 << 5)

#define 	SPI_CR2_RXNE_INT_DISABLE				((uint32_t)0 << 6)
#define 	SPI_CR2_RXNE_INT_ENABLE					((uint32_t)1 << 6)

#define 	SPI_CR2_TXNE_INT_DISABLE				((uint32_t)0 << 7)
#define 	SPI_CR2_TXNE_INT_ENABLE					((uint32_t)1 << 7)


/*						Configuration Bits SPI Clock Enable						*/
#define 	SPI1_CLK_ENABLE									(RCC->APB2ENR |= (1 << 12))
#define		SPI2_CLK_ENABLE									(RCC->APB1ENR |= (1 << 14))
#define 	SPI3_CLK_ENABLE									(RCC->APB1ENR |= (1 << 15))
#define 	SPI4_CLK_ENABLE									(RCC->APB2ENR |= (1 << 13))

/*						Configuration Bits GPIO Clock Enable					*/
#define 	GPIOA_CLK_ENABLE								(RCC->AHB1ENR |= (1 << 0))
#define 	GPIOB_CLK_ENABLE								(RCC->AHB1ENR |= (1 << 1))
#define 	GPIOC_CLK_ENABLE								(RCC->AHB1ENR |= (1 << 2))
#define 	GPIOD_CLK_ENABLE								(RCC->AHB1ENR |= (1 << 3))

/************************************************************
							SPI Data Structures				
*************************************************************/

typedef enum
{
		SPI_STATE_RX_BUSY				= 0x01,
		SPI_STATE_TX_BUSY				= 0x02,
		SPI_STATE_UNDERRUN_FLAG		= 0x03,
		SPI_STATE_MODE_FAULT_FLAG	= 0x05,
		SPI_STATE_OVERRUN_FLAG		= 0x06,
		SPI_STATE_FRAME_ERROR			= 0x07
}spi_state;


typedef struct
{
	uint32_t 	Mode;
	uint32_t 	BIDI_UNI;
	uint32_t 	ClkPolarity;
	uint32_t	ClkPhase;
	uint32_t	DataFormat;
	uint32_t	FrameFormat;
	uint32_t	BaudRate;
	uint32_t	SoftwareSlaveManagement;
}spi_init;

typedef struct 
{
	SPI_TypeDef *BaseAdress;
	spi_init 		Init;
	uint8_t 		*pTxBuffer;
	uint8_t			*pRxBuffer;
	uint32_t		TxBufferLen;
	uint32_t		RxBufferLen;
	uint32_t		TxBufferCount;
	uint32_t 		RxBufferCount;
	spi_state		State;
}spi_handle;

typedef struct
{
	uint32_t		Mode;
	uint32_t 		Output_Type;
	uint32_t		Output_Speed;
	uint32_t		Pull_Up_Down;
}gpio_init;

typedef struct
{
	GPIO_TypeDef *GPIO_Adress;
	gpio_init			GPIO_init;
	uint32_t 			PinState;
}gpio_handle;

/************************************************************
							SPI Exposed Driver APIs 				
*************************************************************/

void spi_initialize(spi_handle *spix);

void spi_master_TX(spi_handle *spix, uint8_t *txBuffer, uint32_t txMsgLen);

void spi_master_RX(spi_handle *spix, uint8_t *rxBuffer, uint32_t rxMsgLen);

void spi_slave_TX(spi_handle *spix, uint8_t *txBuffer, uint32_t txMsgLen);

void spi_slave_RX(spi_handle *spix, uint8_t *rxBuffer, uint32_t rxMsgLen);

void spi_handle_interrupt(spi_handle *spix);


























