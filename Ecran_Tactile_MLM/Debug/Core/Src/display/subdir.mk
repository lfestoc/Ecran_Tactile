################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/display/lcd.c \
../Core/Src/display/lcd_touch.c \
../Core/Src/display/lcd_touch_draw.c 

OBJS += \
./Core/Src/display/lcd.o \
./Core/Src/display/lcd_touch.o \
./Core/Src/display/lcd_touch_draw.o 

C_DEPS += \
./Core/Src/display/lcd.d \
./Core/Src/display/lcd_touch.d \
./Core/Src/display/lcd_touch_draw.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/display/%.o Core/Src/display/%.su: ../Core/Src/display/%.c Core/Src/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-display

clean-Core-2f-Src-2f-display:
	-$(RM) ./Core/Src/display/lcd.d ./Core/Src/display/lcd.o ./Core/Src/display/lcd.su ./Core/Src/display/lcd_touch.d ./Core/Src/display/lcd_touch.o ./Core/Src/display/lcd_touch.su ./Core/Src/display/lcd_touch_draw.d ./Core/Src/display/lcd_touch_draw.o ./Core/Src/display/lcd_touch_draw.su

.PHONY: clean-Core-2f-Src-2f-display

