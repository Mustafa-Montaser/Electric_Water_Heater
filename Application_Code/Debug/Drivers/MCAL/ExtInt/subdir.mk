################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MCAL/ExtInt/EXT_INT_Program.c 

OBJS += \
./Drivers/MCAL/ExtInt/EXT_INT_Program.o 

C_DEPS += \
./Drivers/MCAL/ExtInt/EXT_INT_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MCAL/ExtInt/%.o: ../Drivers/MCAL/ExtInt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


