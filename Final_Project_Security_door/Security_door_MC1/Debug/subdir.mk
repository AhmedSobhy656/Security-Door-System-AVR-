################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Final_Project_MC1.c \
../Internal_eeprom_avr.c \
../Password.c \
../Timer0_Normal_mode.c \
../external_eeprom.c \
../i2c.c \
../keypad.c \
../lcd.c \
../uart_mc_1.c 

OBJS += \
./Final_Project_MC1.o \
./Internal_eeprom_avr.o \
./Password.o \
./Timer0_Normal_mode.o \
./external_eeprom.o \
./i2c.o \
./keypad.o \
./lcd.o \
./uart_mc_1.o 

C_DEPS += \
./Final_Project_MC1.d \
./Internal_eeprom_avr.d \
./Password.d \
./Timer0_Normal_mode.d \
./external_eeprom.d \
./i2c.d \
./keypad.d \
./lcd.d \
./uart_mc_1.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


