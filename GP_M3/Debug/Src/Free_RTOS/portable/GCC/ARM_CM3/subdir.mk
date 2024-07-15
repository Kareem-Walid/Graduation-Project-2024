################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Free_RTOS/portable/GCC/ARM_CM3/port.c 

OBJS += \
./Src/Free_RTOS/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./Src/Free_RTOS/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Free_RTOS/portable/GCC/ARM_CM3/%.o Src/Free_RTOS/portable/GCC/ARM_CM3/%.su Src/Free_RTOS/portable/GCC/ARM_CM3/%.cyclo: ../Src/Free_RTOS/portable/GCC/ARM_CM3/%.c Src/Free_RTOS/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Free_RTOS-2f-portable-2f-GCC-2f-ARM_CM3

clean-Src-2f-Free_RTOS-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./Src/Free_RTOS/portable/GCC/ARM_CM3/port.cyclo ./Src/Free_RTOS/portable/GCC/ARM_CM3/port.d ./Src/Free_RTOS/portable/GCC/ARM_CM3/port.o ./Src/Free_RTOS/portable/GCC/ARM_CM3/port.su

.PHONY: clean-Src-2f-Free_RTOS-2f-portable-2f-GCC-2f-ARM_CM3

