#include "SPI.h"
#include "main.h"

spi_handle SPI_1;
gpio_handle GPIO_A;

int main(void){
	SPI1_CLK_ENABLE;
	GPIOA_CLK_ENABLE;
	
	SPI_1.BaseAdress 										= 	SPI1;
	SPI_1.Init.Mode 										=  	MASTER;
	SPI_1.Init.BIDI_UNI 								= 	BIDI;
	SPI_1.Init.ClkPolarity 							=		NON_INV;
	SPI_1.Init.ClkPhase 								=		RISING;
	SPI_1.Init.DataFormat 							=		BIT_8;
	SPI_1.Init.FrameFormat 							= 	LSB;
	SPI_1.Init.BaudRate 								= 	PRES_2;
	SPI_1.Init.SoftwareSlaveManagement 	= 	DISABLE;
	
	GPIO_A.GPIO_Adress 									= GPIOA;
	GPIO_A.GPIO_init.Mode 							= OUTPUT;
	GPIO_A.GPIO_init.Output_Type 				= PUSH_PULL;
	GPIO_A.GPIO_init.Output_Speed 			= LOW;
	GPIO_A.GPIO_init.Pull_Up_Down 			= PULL_UP;
	GPIO_A.PinState 										= PIN_ON;	
	
	spi_initialize(&SPI_1);
	spi_master_TX(&SPI_1, SEND_DATA, DATA_LEN);
	return 0;	
}
