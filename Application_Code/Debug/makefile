################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/MCAL/Timer0/subdir.mk
-include Drivers/MCAL/IIC/subdir.mk
-include Drivers/MCAL/GIE/subdir.mk
-include Drivers/MCAL/ExtInt/subdir.mk
-include Drivers/MCAL/DIO/subdir.mk
-include Drivers/MCAL/ADC/subdir.mk
-include Drivers/HAL/SensorLM35/subdir.mk
-include Drivers/HAL/PushButton/subdir.mk
-include Drivers/HAL/LED/subdir.mk
-include Drivers/HAL/Heater/subdir.mk
-include Drivers/HAL/EEPROM/subdir.mk
-include Drivers/HAL/DSSD/subdir.mk
-include Drivers/HAL/Cooler/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
electric_water_heater.lss \

FLASH_IMAGE += \
electric_water_heater.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: electric_water_heater.elf secondary-outputs

# Tool invocations
electric_water_heater.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,electric_water_heater.map -mmcu=atmega32 -o "electric_water_heater.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

electric_water_heater.lss: electric_water_heater.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S electric_water_heater.elf  >"electric_water_heater.lss"
	@echo 'Finished building: $@'
	@echo ' '

electric_water_heater.hex: electric_water_heater.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex electric_water_heater.elf  "electric_water_heater.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: electric_water_heater.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 electric_water_heater.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) electric_water_heater.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
