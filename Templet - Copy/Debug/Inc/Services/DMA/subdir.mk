################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Services/DMA/DMA.c 

OBJS += \
./Inc/Services/DMA/DMA.o 

C_DEPS += \
./Inc/Services/DMA/DMA.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Services/DMA/%.o Inc/Services/DMA/%.su Inc/Services/DMA/%.cyclo: ../Inc/Services/DMA/%.c Inc/Services/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-Services-2f-DMA

clean-Inc-2f-Services-2f-DMA:
	-$(RM) ./Inc/Services/DMA/DMA.cyclo ./Inc/Services/DMA/DMA.d ./Inc/Services/DMA/DMA.o ./Inc/Services/DMA/DMA.su

.PHONY: clean-Inc-2f-Services-2f-DMA

