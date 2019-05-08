################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/init.c \
../src/main.c \
../src/stm32f7xx_it.c \
../src/syscalls.c \
../src/system_stm32f7xx.c 

OBJS += \
./src/init.o \
./src/main.o \
./src/stm32f7xx_it.o \
./src/syscalls.o \
./src/system_stm32f7xx.o 

C_DEPS += \
./src/init.d \
./src/main.d \
./src/stm32f7xx_it.d \
./src/syscalls.d \
./src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ampire480272" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/n25q512a" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/s5k5cag" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/mfxstm32l152" -I"C:/Users/Agata/workspace/F7_ADC/CMSIS/device" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/n25q128a" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ts3510" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/st7735" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/rk043fn48h" -I"C:/Users/Agata/workspace/F7_ADC/HAL_Driver/Inc/Legacy" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ov9655" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/otm8009a" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/STM32746G-Discovery" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/Common" -I"C:/Users/Agata/workspace/F7_ADC/HAL_Driver/Inc" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/stmpe811" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/wm8994" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Fonts" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ft5336" -I"C:/Users/Agata/workspace/F7_ADC/inc" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ft6x06" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/exc7200" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/st7789h2" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Log" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/adv7533" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/ampire640480" -I"C:/Users/Agata/workspace/F7_ADC/CMSIS/core" -I"C:/Users/Agata/workspace/F7_ADC/Utilities/Components/mx25l512" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


