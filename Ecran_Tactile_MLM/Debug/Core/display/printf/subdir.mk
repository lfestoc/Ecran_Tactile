################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/display/printf/printf.c 

OBJS += \
./Core/display/printf/printf.o 

C_DEPS += \
./Core/display/printf/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/display/printf/%.o Core/display/printf/%.su: ../Core/display/printf/%.c Core/display/printf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-display-2f-printf

clean-Core-2f-display-2f-printf:
	-$(RM) ./Core/display/printf/printf.d ./Core/display/printf/printf.o ./Core/display/printf/printf.su

.PHONY: clean-Core-2f-display-2f-printf

