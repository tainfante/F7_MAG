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
		__HAL_RCC_GPIOG_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOI_CLK_ENABLE();

		GPIO_InitTypeDef gpio;
		GPIO_InitTypeDef gpio_adc;

		//External interrupts from I2C - INT1
		gpio.Mode=GPIO_MODE_IT_RISING;
		gpio.Pin=GPIO_PIN_7;
		gpio.Pull=GPIO_NOPULL;
		HAL_GPIO_Init(GPIOG, &gpio);

		//External interrupts from I2C - INT2
		gpio.Mode=GPIO_MODE_IT_RISING;
		gpio.Pin=GPIO_PIN_3;
		gpio.Pull=GPIO_NOPULL;
		HAL_GPIO_Init(GPIOI, &gpio);

		//Usart TX pin
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Pin = GPIO_PIN_6;
		gpio.Pull = GPIO_NOPULL;
		gpio.Speed = GPIO_SPEED_LOW;
		gpio.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &gpio);

		//Usart Rx pin
		gpio.Mode = GPIO_MODE_AF_PP;
		gpio.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &gpio);

		//I2C SDA and SCL
		gpio.Mode = GPIO_MODE_AF_OD;
		gpio.Pin = GPIO_PIN_8 | GPIO_PIN_9; // SCL, SDA
		gpio.Pull = GPIO_PULLUP;
		gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;
		gpio.Alternate=GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &gpio);

		//Data sending frequency check
		gpio.Mode=GPIO_MODE_OUTPUT_PP;
		gpio.Pin=GPIO_PIN_6;
		HAL_GPIO_Init(GPIOG, &gpio);

		//ADC Channel 1
		gpio_adc.Mode = GPIO_MODE_ANALOG;
		gpio_adc.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOF, &gpio_adc);

		//ADC Channel 2
		gpio_adc.Mode = GPIO_MODE_ANALOG;
		gpio_adc.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOF, &gpio_adc);

		UartHandle.Instance = USART6;
		UartHandle.hdmatx= &uart_dma;
		UartHandle.Init.BaudRate = 115200;
		UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
		UartHandle.Init.StopBits = UART_STOPBITS_1;
		UartHandle.Init.Parity = UART_PARITY_NONE;
		UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		UartHandle.Init.Mode = UART_MODE_TX_RX;
		HAL_UART_Init(&UartHandle);

		HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);

		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

UART_HandleTypeDef UartInstance(void){
	return UartHandle;
}

void EXTI3_IRQHandler(void){
	gyr_ready=1;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXTI9_5_IRQHandler(void){
	acc_ready=1;
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}



