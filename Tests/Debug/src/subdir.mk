################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Tests.c \
../src/estructurasUMC.c \
../src/funciones.c \
../src/hexdump.c 

OBJS += \
./src/Tests.o \
./src/estructurasUMC.o \
./src/funciones.o \
./src/hexdump.o 

C_DEPS += \
./src/Tests.d \
./src/estructurasUMC.d \
./src/funciones.d \
./src/hexdump.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/tp-2016-1c-SO-2016-1C/Librerias" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


