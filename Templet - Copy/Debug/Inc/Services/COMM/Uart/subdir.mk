################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Services/COMM/Uart/COM_Uart.c 

OBJS += \
./Inc/Services/COMM/Uart/COM_Uart.o 

C_DEPS += \
./Inc/Services/COMM/Uart/COM_Uart.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Services/COMM/Uart/%.o Inc/Services/COMM/Uart/%.su Inc/Services/COMM/Uart/%.cyclo: ../Inc/Services/COMM/Uart/%.c Inc/Services/COMM/Uart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-Services-2f-COMM-2f-Uart

clean-Inc-2f-Services-2f-COMM-2f-Uart:
	-$(RM) ./Inc/Services/COMM/Uart/COM_Uart.cyclo ./Inc/Services/COMM/Uart/COM_Uart.d ./Inc/Services/COMM/Uart/COM_Uart.o ./Inc/Services/COMM/Uart/COM_Uart.su

.PHONY: clean-Inc-2f-Services-2f-COMM-2f-Uart

