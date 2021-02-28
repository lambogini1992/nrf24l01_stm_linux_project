################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/nrf24_hal/nrf24_hal.c 

OBJS += \
./Core/nrf24_hal/nrf24_hal.o 

C_DEPS += \
./Core/nrf24_hal/nrf24_hal.d 


# Each subdirectory must supply rules for building sources it contributes
Core/nrf24_hal/nrf24_hal.o: ../Core/nrf24_hal/nrf24_hal.c Core/nrf24_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I"D:/stm32_proj/nrf24_receive/Core/nrf24_service" -I"D:/stm32_proj/nrf24_receive/Core/nrf24_hal" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/nrf24_hal/nrf24_hal.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

