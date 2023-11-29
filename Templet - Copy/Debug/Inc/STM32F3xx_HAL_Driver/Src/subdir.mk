################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c \
../Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c 

OBJS += \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.o \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.o 

C_DEPS += \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.d \
./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/STM32F3xx_HAL_Driver/Src/%.o Inc/STM32F3xx_HAL_Driver/Src/%.su Inc/STM32F3xx_HAL_Driver/Src/%.cyclo: ../Inc/STM32F3xx_HAL_Driver/Src/%.c Inc/STM32F3xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Src

clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Src:
	-$(RM) ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi_ex.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.su ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.cyclo ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.d ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.o ./Inc/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.su

.PHONY: clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Src

