################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ApplicationCode.c \
../Src/LCD_Driver.c \
../Src/fonts.c \
../Src/ili9341.c \
../Src/main.c \
../Src/stmpe811.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/ApplicationCode.o \
./Src/LCD_Driver.o \
./Src/fonts.o \
./Src/ili9341.o \
./Src/main.o \
./Src/stmpe811.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/ApplicationCode.d \
./Src/LCD_Driver.d \
./Src/fonts.d \
./Src/ili9341.d \
./Src/main.d \
./Src/stmpe811.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F429I_DISC1 -DSTM32 -DSTM32F429ZITx -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ApplicationCode.cyclo ./Src/ApplicationCode.d ./Src/ApplicationCode.o ./Src/ApplicationCode.su ./Src/LCD_Driver.cyclo ./Src/LCD_Driver.d ./Src/LCD_Driver.o ./Src/LCD_Driver.su ./Src/fonts.cyclo ./Src/fonts.d ./Src/fonts.o ./Src/fonts.su ./Src/ili9341.cyclo ./Src/ili9341.d ./Src/ili9341.o ./Src/ili9341.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stmpe811.cyclo ./Src/stmpe811.d ./Src/stmpe811.o ./Src/stmpe811.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

