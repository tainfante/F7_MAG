/*
 * dma.c
 *
 *  Created on: 13.05.2019
 *      Author: Agata
 */

#include "dma.h"

#define ADC_DATA_BYTE 13
#define BUFFER_SIZE 5

DMA_HandleTypeDef dma;



ADC_HandleTypeDef adc_handle;

uint16_t adcValue[2];
uint8_t ADC1buffer[BUFFER_SIZE];
UART_HandleTypeDef uart;


void Dma_Config(void) {

	__HAL_RCC_DMA2_CLK_ENABLE();

	dma.Instance = DMA2_Stream0;
	dma.Init.Channel = DMA_CHANNEL_2;
	dma.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dma.Init.PeriphInc = DMA_PINC_DISABLE;
	dma.Init.MemInc = DMA_MINC_ENABLE;
	dma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	dma.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	dma.Init.Mode = DMA_CIRCULAR;
	dma.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&dma);

	adc_handle = ADC_getInstance();

	__HAL_LINKDMA(&adc_handle, DMA_Handle, dma);
	__HAL_DMA_ENABLE_IT(&dma, DMA_IT_TC);

	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	HAL_ADC_Start_DMA(&adc_handle, (uint32_t*) &adcValue, 2);

	uart_dma.Instance=DMA2_Stream6;
	uart_dma.Init.Channel=DMA_CHANNEL_5;
	uart_dma.Init.Direction=DMA_MEMORY_TO_PERIPH;
	uart_dma.Init.PeriphInc=DMA_PINC_DISABLE;
	uart_dma.Init.MemInc=DMA_MINC_ENABLE;
	uart_dma.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
	uart_dma.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
	uart_dma.Init.Mode=DMA_CIRCULAR;
	uart_dma.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&uart_dma);

	__HAL_DMA_ENABLE(&uart_dma);

}

void sendADCdata(void) {

	uart=UartInstance();

	ADC1buffer[0] = (uint8_t) (ADC_DATA_BYTE);
	ADC1buffer[1] = (uint8_t) (adcValue[0] >> 8);
	ADC1buffer[2] = (uint8_t) (adcValue[0]);
	ADC1buffer[3] = (uint8_t) (adcValue[1] >> 8);
	ADC1buffer[4] = (uint8_t) (adcValue[1]);

	HAL_UART_Transmit_DMA(&uart, ADC1buffer, BUFFER_SIZE);
}

void DMA2_Stream0_IRQHandler(void){
	HAL_DMA_IRQHandler(&dma);
	dma_transfer_complete=1;
}

