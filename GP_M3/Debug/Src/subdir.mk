################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/core_cm3.c \
../Src/main.c \
../Src/stm32f10x_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f10x.c 

OBJS += \
./Src/core_cm3.o \
./Src/main.o \
./Src/stm32f10x_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f10x.o 

C_DEPS += \
./Src/core_cm3.d \
./Src/main.d \
./Src/stm32f10x_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/core_cm3.cyclo ./Src/core_cm3.d ./Src/core_cm3.o ./Src/core_cm3.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f10x_it.cyclo ./Src/stm32f10x_it.d ./Src/stm32f10x_it.o ./Src/stm32f10x_it.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f10x.cyclo ./Src/system_stm32f10x.d ./Src/system_stm32f10x.o ./Src/system_stm32f10x.su

.PHONY: clean-Src

