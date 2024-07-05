################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../2nd_main.c \
../EEPROM.c \
../I2C.c \
../USART.c \
../motor.c \
../timer_0.c 

OBJS += \
./2nd_main.o \
./EEPROM.o \
./I2C.o \
./USART.o \
./motor.o \
./timer_0.o 

C_DEPS += \
./2nd_main.d \
./EEPROM.d \
./I2C.d \
./USART.d \
./motor.d \
./timer_0.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


