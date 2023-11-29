################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.c 

OBJS += \
./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.o 

C_DEPS += \
./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/STM32F3xx_HAL_Driver/Target/%.o Inc/STM32F3xx_HAL_Driver/Target/%.su Inc/STM32F3xx_HAL_Driver/Target/%.cyclo: ../Inc/STM32F3xx_HAL_Driver/Target/%.c Inc/STM32F3xx_HAL_Driver/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Target

clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Target:
	-$(RM) ./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.cyclo ./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.d ./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.o ./Inc/STM32F3xx_HAL_Driver/Target/system_stm32f3xx.su

.PHONY: clean-Inc-2f-STM32F3xx_HAL_Driver-2f-Target

