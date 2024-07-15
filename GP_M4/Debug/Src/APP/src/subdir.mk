################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/src/Initialize_file_M4.c \
../Src/APP/src/app.c 

OBJS += \
./Src/APP/src/Initialize_file_M4.o \
./Src/APP/src/app.o 

C_DEPS += \
./Src/APP/src/Initialize_file_M4.d \
./Src/APP/src/app.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/src/%.o Src/APP/src/%.su Src/APP/src/%.cyclo: ../Src/APP/src/%.c Src/APP/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/APP/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/portable/GCC/ARM_CM4F" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/freeRTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M4/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-src

clean-Src-2f-APP-2f-src:
	-$(RM) ./Src/APP/src/Initialize_file_M4.cyclo ./Src/APP/src/Initialize_file_M4.d ./Src/APP/src/Initialize_file_M4.o ./Src/APP/src/Initialize_file_M4.su ./Src/APP/src/app.cyclo ./Src/APP/src/app.d ./Src/APP/src/app.o ./Src/APP/src/app.su

.PHONY: clean-Src-2f-APP-2f-src

