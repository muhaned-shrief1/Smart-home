################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/BUZZER.c \
../HAL/EEPROM.c \
../HAL/Keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/BUZZER.o \
./HAL/EEPROM.o \
./HAL/Keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/BUZZER.d \
./HAL/EEPROM.d \
./HAL/Keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


