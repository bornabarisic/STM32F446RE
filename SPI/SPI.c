#include "SPI.h"
#include <stdint.h>


/************************************************************
							Helper Functions				
*************************************************************/

/************ Helper Functions For spi_initialize function **/
static void spi_mode_configure(SPI_TypeDef *SPIx, uint32_t mode){
	if(mode){
		SPIx->CR1 |= SPI_CR1_MASTER_MODE;
	}
	else{
		SPIx->CR1 |= SPI_CR1_SLAVE_MODE;
	}
}

static void spi_bidi_uni_configuration(SPI_TypeDef *SPIx, uint32_t bidi){
	if(bidi){
		SPIx->CR1 |= SPI_CR1_BIDI_MODE;
	}
	else{
		SPIx->CR1 |= SPI_CR1_UNI_MODE;
	}
}

static void spi_clock_polarity(SPI_TypeDef *SPIx, uint32_t inverted){
	if(inverted){
		SPIx->CR1 |= SPI_CR1_CLK_POL_1;
	}
	else{
		SPIx->CR1 |= SPI_CR1_CLK_POL_0;
	}
}

static void spi_clock_phase(SPI_TypeDef *SPIx, uint32_t rising){
	if (rising){
		SPIx->CR1 |= SPI_CR1_CLK_PHASE_RISE;
	}
	else{
		SPIx->CR1 |= SPI_CR1_CLK_PHASE_FALL;
	}
}

static void spi_data_format(SPI_TypeDef *SPIx, uint32_t format_16){
	if (format_16){
		SPIx->CR1 |= SPI_CR1_DATA_FRAME_FORMAT_16;
	}
	else{
		SPIx->CR1 |= SPI_CR1_DATA_FRAME_FORMAT_8;
	}
}

static void spi_frame_format(SPI_TypeDef *SPIx, uint32_t format_LSB){
	if (format_LSB){
		SPIx->CR1 |= SPI_CR1_LSB_FRAME_FORMAT;
	}
	else{
		SPIx->CR1 |= SPI_CR1_MSB_FRAME_FORMAT;
	}
}

static void spi_baud_rate(SPI_TypeDef *SPIx, uint32_t rate){
	switch (rate){
		case 2:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_2;
			break;
		case 4:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_4;
			break;
		case 8:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_8;
			break;
		case 16:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_16;
			break;
		case 32:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_32;
			break;
		case 64:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_64;
			break;
		case 128:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_128;
			break;
		case 256:
			SPIx->CR1 |= SPI_CR1_BAUD_RATE_256;
			break;
	}
}

static void spi_sofware_slave_management(SPI_TypeDef *SPIx, uint32_t enable){
	if (enable){
		SPIx->CR1 |= SPI_CR1_SOFT_SLAVE_MANAG_ENA;
	}
	else{
		SPIx->CR1 |= SPI_CR1_SOFT_SLAVE_MANAG_DIS;
	}
}
/************************************************************/


/************ Helper Functions For spi_master_TX function **/
static void spi_enable(SPI_TypeDef *SPIx){
	if (SPIx->CR1 & SPI_CR1_SPI_DISABLE){
		SPIx->CR1 |= SPI_CR1_SPI_ENABLE;
	}
}

static void spi_disable(SPI_TypeDef *SPIx){
	SPIx->CR1 |= SPI_CR1_SPI_DISABLE;
}

static void spi_enable_txe_interrupt(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_CR2_TXNE_INT_ENABLE;
}

static void spi_disable_txe_interrupt(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_CR2_TXNE_INT_DISABLE;
}

static void spi_enable_rxne_interrupt(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_CR2_RXNE_INT_ENABLE;
}

static void spi_disable_rxne_interrupt(SPI_TypeDef *SPIx){
	SPIx->CR2 |= SPI_CR2_RXNE_INT_DISABLE;
}

/************************************************************/




/************************************************************
							SPI Exposed Driver APIs 				
*************************************************************/

void spi_initialize(spi_handle *spix){
	spi_mode_configure(spix->BaseAdress, spix->Init.Mode);
	spi_bidi_uni_configuration(spix->BaseAdress, spix->Init.BIDI_UNI);
	spi_clock_polarity(spix->BaseAdress, spix->Init.ClkPolarity);
	spi_clock_phase(spix->BaseAdress, spix->Init.ClkPhase);
	spi_data_format(spix->BaseAdress, spix->Init.DataFormat);
	spi_frame_format(spix->BaseAdress, spix->Init.FrameFormat);
	spi_baud_rate(spix->BaseAdress, spix->Init.BaudRate);
	spi_sofware_slave_management(spix->BaseAdress, spix->Init.SoftwareSlaveManagement);
	
}

void spi_master_TX(spi_handle *spix, uint8_t *txBuffer, uint32_t txMsgLen){
	uint32_t txCount 		= 0;
	
	spix->pTxBuffer 		= txBuffer;
	spix->TxBufferLen 	= txMsgLen;
	spix->TxBufferCount = txCount;	
	
	spix->State = SPI_STATE_TX_BUSY;
	
	spi_enable(spix->BaseAdress);
	
	spi_enable_txe_interrupt(spix->BaseAdress);
}

void spi_master_RX(spi_handle *spix, uint8_t *rxBuffer, uint32_t rxMsgLen){
	uint32_t rxCount = 0, txCount = 0, val;
	
	// dummy transmit data
	spix->pTxBuffer 		= rxBuffer;
	spix->TxBufferLen 	= rxMsgLen;
	spix->TxBufferCount = txCount;

	// received data to rx buffer
	spix->pRxBuffer			= rxBuffer;
	spix->RxBufferLen		= rxMsgLen;
	spix->RxBufferLen		= rxCount;
	
	spix->State = SPI_STATE_RX_BUSY;
	
	spi_enable(spix->BaseAdress);
	
	// read from data register to make sure DR is empty before RXNE interrupt
	val = spix->BaseAdress->DR;
	
	spi_enable_txe_interrupt(spix->BaseAdress);
	spi_enable_rxne_interrupt(spix->BaseAdress);	
}

void spi_slave_TX(spi_handle *spix, uint8_t *txBuffer, uint32_t txMsgLen);

void spi_slave_RX(spi_handle *spix, uint8_t *rxBuffer, uint32_t rxMsgLen);

void spi_handle_interrupt(spi_handle *spix);
