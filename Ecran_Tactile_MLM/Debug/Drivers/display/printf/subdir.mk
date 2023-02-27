################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/display/printf/printf.c 

OBJS += \
./Drivers/display/printf/printf.o 

C_DEPS += \
./Drivers/display/printf/printf.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/display/printf/%.o Drivers/display/printf/%.su: ../Drivers/display/printf/%.c Drivers/display/printf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-display-2f-printf

clean-Drivers-2f-display-2f-printf:
	-$(RM) ./Drivers/display/printf/printf.d ./Drivers/display/printf/printf.o ./Drivers/display/printf/printf.su

.PHONY: clean-Drivers-2f-display-2f-printf

