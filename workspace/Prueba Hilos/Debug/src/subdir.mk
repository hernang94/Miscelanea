################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Prueba\ Hilos.c 

OBJS += \
./src/Prueba\ Hilos.o 

C_DEPS += \
./src/Prueba\ Hilos.d 


# Each subdirectory must supply rules for building sources it contributes
src/Prueba\ Hilos.o: ../src/Prueba\ Hilos.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Prueba Hilos.d" -MT"src/Prueba\ Hilos.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


