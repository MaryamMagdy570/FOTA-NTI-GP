################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/Services/COMM/COMM_program.c 

OBJS += \
./Inc/Services/COMM/COMM_program.o 

C_DEPS += \
./Inc/Services/COMM/COMM_program.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/Services/COMM/%.o Inc/Services/COMM/%.su Inc/Services/COMM/%.cyclo: ../Inc/Services/COMM/%.c Inc/Services/COMM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F3 -DSTM32F303RETx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc-2f-Services-2f-COMM

clean-Inc-2f-Services-2f-COMM:
	-$(RM) ./Inc/Services/COMM/COMM_program.cyclo ./Inc/Services/COMM/COMM_program.d ./Inc/Services/COMM/COMM_program.o ./Inc/Services/COMM/COMM_program.su

.PHONY: clean-Inc-2f-Services-2f-COMM

