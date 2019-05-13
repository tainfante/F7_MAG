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
#include "uart.h"



int main(void) {

	HAL_Init();

	Initialize();
	Dma_Config();
	Uart_Config();
	StartADC_DMA();


	while (1) {

		sendADCdata();
		HAL_Delay(1000);

	}
}
