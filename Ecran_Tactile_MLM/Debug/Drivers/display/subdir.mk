################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/display/lcd.c \
../Drivers/display/lcd_touch.c \
../Drivers/display/lcd_touch_draw.c 

OBJS += \
./Drivers/display/lcd.o \
./Drivers/display/lcd_touch.o \
./Drivers/display/lcd_touch_draw.o 

C_DEPS += \
./Drivers/display/lcd.d \
./Drivers/display/lcd_touch.d \
./Drivers/display/lcd_touch_draw.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/display/%.o Drivers/display/%.su: ../Drivers/display/%.c Drivers/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-display

clean-Drivers-2f-display:
	-$(RM) ./Drivers/display/lcd.d ./Drivers/display/lcd.o ./Drivers/display/lcd.su ./Drivers/display/lcd_touch.d ./Drivers/display/lcd_touch.o ./Drivers/display/lcd_touch.su ./Drivers/display/lcd_touch_draw.d ./Drivers/display/lcd_touch_draw.o ./Drivers/display/lcd_touch_draw.su

.PHONY: clean-Drivers-2f-display

