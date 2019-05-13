/*
 * dma.c
 *
 *  Created on: 13.05.2019
 *      Author: Agata
 */

#include "dma.h"

#define ADC_DATA_BYTE 13
#define BUFFER_SIZE 3

DMA_HandleTypeDef dma;
UART_HandleTypeDef uart;
ADC_HandleTypeDef adc;
uint32_t adcValue;
uint8_t ADC1buffer[BUFFER_SIZE];

void Dma_Config(void) {

	__HAL_RCC_DMA1_CLK_ENABLE()
	;
	__HAL_RCC_ADC3_CLK_ENABLE()
	;

	dma.Instance = DMA1_Stream1;
	dma.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dma.Init.PeriphInc = DMA_PINC_DISABLE;
	dma.Init.MemInc = DMA_MINC_ENABLE;
	dma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	dma.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	dma.Init.Mode = DMA_CIRCULAR;
	dma.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&dma);

	adc.Instance = ADC3;
	adc.Init.ContinuousConvMode = ENABLE;
	adc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	adc.Init.NbrOfConversion = 1;
	adc.Init.DiscontinuousConvMode = DISABLE;
	adc.Init.NbrOfDiscConversion = 1;
	HAL_ADC_Init(&adc);

	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel = ADC_CHANNEL_8;
	adc_ch.Rank = ADC_REGULAR_RANK_1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&adc, &adc_ch);

	__HAL_LINKDMA(&adc, DMA_Handle, dma);
}

void StartADC_DMA(void) {

	HAL_ADC_Start_DMA(&adc, (uint32_t*) adcValue, 1);

}

void sendADCdata(void) {

	ADC1buffer[0] = (uint8_t) (ADC_DATA_BYTE);
	ADC1buffer[1] = (uint8_t) (adcValue >> 8);
	ADC1buffer[2] = (uint8_t) (adcValue);

	uart=UartInstance();

	HAL_UART_Transmit(&uart, ADC1buffer, BUFFER_SIZE, 1000);
}

