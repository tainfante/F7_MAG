/*
 * i2c.c
 *
 *  Created on: 23.06.2019
 *      Author: Agata
 */

#include "i2c.h"

I2C_HandleTypeDef i2c;
UART_HandleTypeDef uart;
uint8_t acc_en=1;
uint8_t gyr_en=2;

void I2C_Config(void){

	__HAL_RCC_I2C1_CLK_ENABLE();

	i2c.Instance=I2C1;
	i2c.Init.Timing=0x80201721;
	i2c.Init.DualAddressMode=I2C_DUALADDRESS_DISABLE;
	i2c.Init.OwnAddress1=ACC_GYR_ADDR;
	i2c.Init.AddressingMode=I2C_ADDRESSINGMODE_7BIT;
	i2c.Init.GeneralCallMode=I2C_GENERALCALL_DISABLE;
	i2c.Init.NoStretchMode=I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(&i2c);

}

uint8_t I2C_Read_Reg(uint8_t reg)
{
 uint8_t value = 0;

 HAL_I2C_Mem_Read(&i2c, ACC_GYR_ADDR, reg, 1, &value, sizeof(value), 1000);

 return value;
}

void Acc_Gyr_Config(uint8_t acc_value, uint8_t gyr_value){
	HAL_I2C_Mem_Write(&i2c, ACC_GYR_ADDR, CTRL1_XL, 1, &acc_value, sizeof(acc_value), 1000);
	HAL_I2C_Mem_Write(&i2c, ACC_GYR_ADDR, CTRL2_G, 1, &gyr_value, sizeof(gyr_value), 1000);
	HAL_I2C_Mem_Write(&i2c, ACC_GYR_ADDR, INT1_CTRL, 1, &acc_en, sizeof(acc_en), 1000);
	HAL_I2C_Mem_Write(&i2c, ACC_GYR_ADDR, INT2_CTRL, 1, &gyr_en, sizeof(gyr_en), 1000);
}

void Read_Sensors_Data(void){
	int i=0;
	for(i=0; i<DATA_AMOUNT; i++){
		HAL_I2C_Mem_Read(&i2c, ACC_GYR_ADDR, (0x22+i), 1, &sensors_data[i], sizeof(sensors_data[i]), 1000);
	}
	uart = UartInstance();
	HAL_UART_Transmit_DMA(&uart, sensors_data, DATA_AMOUNT);
}
