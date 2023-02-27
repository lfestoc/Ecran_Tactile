################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/display/lcd.c \
../Core/display/lcd_touch.c \
../Core/display/lcd_touch_draw.c 

OBJS += \
./Core/display/lcd.o \
./Core/display/lcd_touch.o \
./Core/display/lcd_touch_draw.o 

C_DEPS += \
./Core/display/lcd.d \
./Core/display/lcd_touch.d \
./Core/display/lcd_touch_draw.d 


# Each subdirectory must supply rules for building sources it contributes
Core/display/%.o Core/display/%.su: ../Core/display/%.c Core/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-display

clean-Core-2f-display:
	-$(RM) ./Core/display/lcd.d ./Core/display/lcd.o ./Core/display/lcd.su ./Core/display/lcd_touch.d ./Core/display/lcd_touch.o ./Core/display/lcd_touch.su ./Core/display/lcd_touch_draw.d ./Core/display/lcd_touch_draw.o ./Core/display/lcd_touch_draw.su

.PHONY: clean-Core-2f-display

