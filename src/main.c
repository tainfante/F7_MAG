/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f7xx.h"
#include "init.h"
#include "dma.h"
#include "adc.h"
#include "tim.h"
#include "uart.h"
#include "i2c.h"


//#include "string.h"

/*void send_string(char* s)
{
 HAL_UART_Transmit(&uart, (uint8_t*)s, strlen(s), 1000);
}*/

int main(void) {

	HAL_Init();

	Initialize();
	Tim_Config();
	Adc_Config();
	Dma_Config();
	Uart_Config();
	I2C_Config();

	//send_string("AT+UART=115200,1,0\r\n");

	Acc_Gyr_Config(0x58, 0x58); //setting acc to 208 Hz and +/-4g and gyr to 208 Hz and 1000dps and enalbling interrupts

	while (1) {

		if(acc_ready==1 && gyr_ready==1){
		Read_Sensors_Data();
		acc_ready=0;
		gyr_ready=0;
		}
		if(dma_transfer_complete){
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
		sendADCdata();
		dma_transfer_complete=0;
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
		}
	}
}
