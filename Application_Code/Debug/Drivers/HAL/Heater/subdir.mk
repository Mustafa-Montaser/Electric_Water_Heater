################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HAL/Heater/Heater.c 

OBJS += \
./Drivers/HAL/Heater/Heater.o 

C_DEPS += \
./Drivers/HAL/Heater/Heater.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HAL/Heater/%.o: ../Drivers/HAL/Heater/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


