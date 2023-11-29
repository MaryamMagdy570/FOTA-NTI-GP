################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/stm32f3xx/stm32f3xx_it.c 

OBJS += \
./Inc/stm32f3xx/stm32f3xx_it.o 

C_DEPS += \
./Inc/stm32f3xx/stm32f3xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/stm32f3xx/%.o Inc/stm32f3xx/%.su Inc/stm32f3xx/%.cyclo: ../Inc/stm32f3xx/%.c Inc/stm32f3xx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-stm32f3xx

clean-Inc-2f-stm32f3xx:
	-$(RM) ./Inc/stm32f3xx/stm32f3xx_it.cyclo ./Inc/stm32f3xx/stm32f3xx_it.d ./Inc/stm32f3xx/stm32f3xx_it.o ./Inc/stm32f3xx/stm32f3xx_it.su

.PHONY: clean-Inc-2f-stm32f3xx

