################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/display/Fonts/font12.c \
../Drivers/display/Fonts/font16.c \
../Drivers/display/Fonts/font20.c \
../Drivers/display/Fonts/font24.c \
../Drivers/display/Fonts/font8.c 

OBJS += \
./Drivers/display/Fonts/font12.o \
./Drivers/display/Fonts/font16.o \
./Drivers/display/Fonts/font20.o \
./Drivers/display/Fonts/font24.o \
./Drivers/display/Fonts/font8.o 

C_DEPS += \
./Drivers/display/Fonts/font12.d \
./Drivers/display/Fonts/font16.d \
./Drivers/display/Fonts/font20.d \
./Drivers/display/Fonts/font24.d \
./Drivers/display/Fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/display/Fonts/%.o Drivers/display/Fonts/%.su: ../Drivers/display/Fonts/%.c Drivers/display/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-display-2f-Fonts

clean-Drivers-2f-display-2f-Fonts:
	-$(RM) ./Drivers/display/Fonts/font12.d ./Drivers/display/Fonts/font12.o ./Drivers/display/Fonts/font12.su ./Drivers/display/Fonts/font16.d ./Drivers/display/Fonts/font16.o ./Drivers/display/Fonts/font16.su ./Drivers/display/Fonts/font20.d ./Drivers/display/Fonts/font20.o ./Drivers/display/Fonts/font20.su ./Drivers/display/Fonts/font24.d ./Drivers/display/Fonts/font24.o ./Drivers/display/Fonts/font24.su ./Drivers/display/Fonts/font8.d ./Drivers/display/Fonts/font8.o ./Drivers/display/Fonts/font8.su

.PHONY: clean-Drivers-2f-display-2f-Fonts

