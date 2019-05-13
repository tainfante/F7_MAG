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

void Dma_Config(void);
void StartADC_DMA(void);
void sendADCdata();

#endif /* DMA_H_ */
