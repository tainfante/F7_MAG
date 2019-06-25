/*
 * adc.h
 *
 *  Created on: 01.06.2019
 *      Author: Agata
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f746xx.h"
#include "stm32f7xx_hal.h"

void Adc_Config(void);
ADC_HandleTypeDef ADC_getInstance(void);

#endif /* ADC_H_ */
