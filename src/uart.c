/*
 * uart.c
 *
 *  Created on: 13.05.2019
 *      Author: Agata
 */

#include "uart.h"

UART_HandleTypeDef UartHandle;

void Uart_Config(void){

	__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_USART6_CLK_ENABLE();
		__HAL_RCC_GPIOF_CLK_ENABLE();


		GPIO_InitTypeDef gpio;
		GPIO_InitTypeDef gpio_adc;

		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Pin = GPIO_PIN_6;
		gpio.Pull = GPIO_NOPULL;
		gpio.Speed = GPIO_SPEED_LOW;
		gpio.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &gpio);

		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &gpio);

		gpio_adc.Mode = GPIO_MODE_ANALOG;
		gpio_adc.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOF, &gpio_adc);

		UartHandle.Instance = USART6;
		UartHandle.Init.BaudRate = 9600;
		UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
		UartHandle.Init.StopBits = UART_STOPBITS_1;
		UartHandle.Init.Parity = UART_PARITY_NONE;
		UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		UartHandle.Init.Mode = UART_MODE_TX_RX;
		HAL_UART_Init(&UartHandle);

}

UART_HandleTypeDef UartInstance(void){
	return UartHandle;
}

