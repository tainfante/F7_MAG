/*
 * adc.c
 *
 *  Created on: 01.06.2019
 *      Author: Agata
 */

#include "adc.h"

ADC_HandleTypeDef adc;

void Adc_Config(void) {

	__HAL_RCC_ADC3_CLK_ENABLE();

	adc.Instance = ADC3;
	adc.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
	adc.Init.Resolution = ADC_RESOLUTION12b;
	adc.Init.ContinuousConvMode = DISABLE;
	adc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_TRGO;
	adc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	adc.Init.ScanConvMode = ADC_SCAN_ENABLE;
	adc.Init.NbrOfConversion = 2;
	adc.Init.DiscontinuousConvMode = DISABLE;
	adc.Init.DMAContinuousRequests = ENABLE;

	HAL_ADC_Init(&adc);

	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel = ADC_CHANNEL_8;
	adc_ch.Rank = 1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&adc, &adc_ch);

	adc_ch.Channel = ADC_CHANNEL_7;
	adc_ch.Rank = 2;
	adc_ch.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&adc, &adc_ch);

}

ADC_HandleTypeDef ADC_getInstance(void){
	return adc;
}

