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


#define BUFFER_SIZE 3
#define DATA_AMOUNT 1500
#define ADC_DATA_BYTE 13
UART_HandleTypeDef UartHandle;
ADC_HandleTypeDef adc;
uint32_t ADC1data[DATA_AMOUNT];
uint8_t ADC1buffer[BUFFER_SIZE];


void sendADCdata(uint32_t data){

	ADC1buffer[0] = (uint8_t)(ADC_DATA_BYTE);
	ADC1buffer[1] = (uint8_t)(data >> 8);
	ADC1buffer[2] = (uint8_t)(data);


	 HAL_UART_Transmit(&UartHandle, ADC1buffer, BUFFER_SIZE,1000);
}

int main(void){

	HAL_Init();

	Initialize();


	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_USART6_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_ADC3_CLK_ENABLE();

	GPIO_InitTypeDef gpio;
	GPIO_InitTypeDef gpio_adc;



	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_6;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_LOW;
	gpio.Alternate=GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &gpio);

	 gpio.Mode = GPIO_MODE_AF_PP;
	 gpio.Pin = GPIO_PIN_7;
	 HAL_GPIO_Init(GPIOC, &gpio);

	 gpio_adc.Mode = GPIO_MODE_ANALOG;
	 gpio_adc.Pin = GPIO_PIN_10;
	 HAL_GPIO_Init(GPIOF, &gpio_adc);

	UartHandle.Instance        = USART6;
	UartHandle.Init.BaudRate   = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	HAL_UART_Init(&UartHandle);

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

	 HAL_ADC_Start(&adc);
	 uint32_t c;

 while(1){

	 c=HAL_ADC_GetValue(&adc);
	 sendADCdata(c);
	 HAL_Delay(1000);




	}
}
