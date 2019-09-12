#include "SPI.h"
#include "main.h"

spi_handle SPI_1;

int main(void){
	SPI_1.BaseAdress 										= 	SPI1;
	SPI_1.Init.Mode 										=  	MASTER;
	SPI_1.Init.BIDI_UNI 								= 	BIDI;
	SPI_1.Init.ClkPolarity 							=		NON_INV;
	SPI_1.Init.ClkPhase 								=		RISING;
	SPI_1.Init.DataFormat 							=		BIT_8;
	SPI_1.Init.FrameFormat 							= 	LSB;
	SPI_1.Init.BaudRate 								= 	PRES_2;
	SPI_1.Init.SoftwareSlaveManagement 	= 	DISABLE;
	
	spi_initialize(&SPI_1);
	return 0;	
}
