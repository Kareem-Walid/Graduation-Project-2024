################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/Src/ACC.c \
../Src/APP/Src/AEB.c \
../Src/APP/Src/BlindSpot.c \
../Src/APP/Src/Initialize_file_M3.c \
../Src/APP/Src/LKAS.c \
../Src/APP/Src/SysInit.c 

OBJS += \
./Src/APP/Src/ACC.o \
./Src/APP/Src/AEB.o \
./Src/APP/Src/BlindSpot.o \
./Src/APP/Src/Initialize_file_M3.o \
./Src/APP/Src/LKAS.o \
./Src/APP/Src/SysInit.o 

C_DEPS += \
./Src/APP/Src/ACC.d \
./Src/APP/Src/AEB.d \
./Src/APP/Src/BlindSpot.d \
./Src/APP/Src/Initialize_file_M3.d \
./Src/APP/Src/LKAS.d \
./Src/APP/Src/SysInit.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/Src/%.o Src/APP/Src/%.su Src/APP/Src/%.cyclo: ../Src/APP/Src/%.c Src/APP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-Src

clean-Src-2f-APP-2f-Src:
	-$(RM) ./Src/APP/Src/ACC.cyclo ./Src/APP/Src/ACC.d ./Src/APP/Src/ACC.o ./Src/APP/Src/ACC.su ./Src/APP/Src/AEB.cyclo ./Src/APP/Src/AEB.d ./Src/APP/Src/AEB.o ./Src/APP/Src/AEB.su ./Src/APP/Src/BlindSpot.cyclo ./Src/APP/Src/BlindSpot.d ./Src/APP/Src/BlindSpot.o ./Src/APP/Src/BlindSpot.su ./Src/APP/Src/Initialize_file_M3.cyclo ./Src/APP/Src/Initialize_file_M3.d ./Src/APP/Src/Initialize_file_M3.o ./Src/APP/Src/Initialize_file_M3.su ./Src/APP/Src/LKAS.cyclo ./Src/APP/Src/LKAS.d ./Src/APP/Src/LKAS.o ./Src/APP/Src/LKAS.su ./Src/APP/Src/SysInit.cyclo ./Src/APP/Src/SysInit.d ./Src/APP/Src/SysInit.o ./Src/APP/Src/SysInit.su

.PHONY: clean-Src-2f-APP-2f-Src

