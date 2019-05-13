/*
 * uart.h
 *
 *  Created on: 13.05.2019
 *      Author: Agata
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"

void Uart_Config(void);
UART_HandleTypeDef UartInstance(void);

#endif /* UART_H_ */
