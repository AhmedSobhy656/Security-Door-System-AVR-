################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Final_Project_MC2.c \
../Timer0_Normal_mode.c \
../dc_motor.c \
../external_eeprom.c \
../i2c.c \
../uart_mc_2.c 

OBJS += \
./Final_Project_MC2.o \
./Timer0_Normal_mode.o \
./dc_motor.o \
./external_eeprom.o \
./i2c.o \
./uart_mc_2.o 

C_DEPS += \
./Final_Project_MC2.d \
./Timer0_Normal_mode.d \
./dc_motor.d \
./external_eeprom.d \
./i2c.d \
./uart_mc_2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


