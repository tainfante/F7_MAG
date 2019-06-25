/*
 * dma.h
 *
 *  Created on: 13.05.2019
 *      Author: Agata
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdint.h>
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"
#include "uart.h"
#include "adc.h"

uint8_t dma_transfer_complete;
DMA_HandleTypeDef uart_dma;

void Dma_Config(void);
void sendADCdata(void);
void DMA2_Stream0_IRQHandler(void);


#endif /* DMA_H_ */
