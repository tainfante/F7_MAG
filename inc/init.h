/*
 * init.h
 *
 *  Created on: 08.05.2019
 *      Author: Agata
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdint.h>
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"

static void SystemClock_Config(void);
void Initialize(void);
void Error_Handler(void);
static void CPU_CACHE_Enable(void);

#endif /* INIT_H_ */
