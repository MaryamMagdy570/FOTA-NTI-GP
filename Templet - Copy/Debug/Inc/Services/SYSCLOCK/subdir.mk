################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Services/SYSCLOCK/SYSCLOCK.c 

OBJS += \
./Inc/Services/SYSCLOCK/SYSCLOCK.o 

C_DEPS += \
./Inc/Services/SYSCLOCK/SYSCLOCK.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Services/SYSCLOCK/%.o Inc/Services/SYSCLOCK/%.su Inc/Services/SYSCLOCK/%.cyclo: ../Inc/Services/SYSCLOCK/%.c Inc/Services/SYSCLOCK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-Services-2f-SYSCLOCK

clean-Inc-2f-Services-2f-SYSCLOCK:
	-$(RM) ./Inc/Services/SYSCLOCK/SYSCLOCK.cyclo ./Inc/Services/SYSCLOCK/SYSCLOCK.d ./Inc/Services/SYSCLOCK/SYSCLOCK.o ./Inc/Services/SYSCLOCK/SYSCLOCK.su

.PHONY: clean-Inc-2f-Services-2f-SYSCLOCK

