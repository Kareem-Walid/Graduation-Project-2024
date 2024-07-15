################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/src/misc.c \
../Src/MCAL/src/stm32f10x_adc.c \
../Src/MCAL/src/stm32f10x_bkp.c \
../Src/MCAL/src/stm32f10x_can.c \
../Src/MCAL/src/stm32f10x_cec.c \
../Src/MCAL/src/stm32f10x_crc.c \
../Src/MCAL/src/stm32f10x_dac.c \
../Src/MCAL/src/stm32f10x_dbgmcu.c \
../Src/MCAL/src/stm32f10x_dma.c \
../Src/MCAL/src/stm32f10x_exti.c \
../Src/MCAL/src/stm32f10x_flash.c \
../Src/MCAL/src/stm32f10x_fsmc.c \
../Src/MCAL/src/stm32f10x_gpio.c \
../Src/MCAL/src/stm32f10x_i2c.c \
../Src/MCAL/src/stm32f10x_iwdg.c \
../Src/MCAL/src/stm32f10x_pwr.c \
../Src/MCAL/src/stm32f10x_rcc.c \
../Src/MCAL/src/stm32f10x_rtc.c \
../Src/MCAL/src/stm32f10x_sdio.c \
../Src/MCAL/src/stm32f10x_spi.c \
../Src/MCAL/src/stm32f10x_tim.c \
../Src/MCAL/src/stm32f10x_usart.c \
../Src/MCAL/src/stm32f10x_wwdg.c 

OBJS += \
./Src/MCAL/src/misc.o \
./Src/MCAL/src/stm32f10x_adc.o \
./Src/MCAL/src/stm32f10x_bkp.o \
./Src/MCAL/src/stm32f10x_can.o \
./Src/MCAL/src/stm32f10x_cec.o \
./Src/MCAL/src/stm32f10x_crc.o \
./Src/MCAL/src/stm32f10x_dac.o \
./Src/MCAL/src/stm32f10x_dbgmcu.o \
./Src/MCAL/src/stm32f10x_dma.o \
./Src/MCAL/src/stm32f10x_exti.o \
./Src/MCAL/src/stm32f10x_flash.o \
./Src/MCAL/src/stm32f10x_fsmc.o \
./Src/MCAL/src/stm32f10x_gpio.o \
./Src/MCAL/src/stm32f10x_i2c.o \
./Src/MCAL/src/stm32f10x_iwdg.o \
./Src/MCAL/src/stm32f10x_pwr.o \
./Src/MCAL/src/stm32f10x_rcc.o \
./Src/MCAL/src/stm32f10x_rtc.o \
./Src/MCAL/src/stm32f10x_sdio.o \
./Src/MCAL/src/stm32f10x_spi.o \
./Src/MCAL/src/stm32f10x_tim.o \
./Src/MCAL/src/stm32f10x_usart.o \
./Src/MCAL/src/stm32f10x_wwdg.o 

C_DEPS += \
./Src/MCAL/src/misc.d \
./Src/MCAL/src/stm32f10x_adc.d \
./Src/MCAL/src/stm32f10x_bkp.d \
./Src/MCAL/src/stm32f10x_can.d \
./Src/MCAL/src/stm32f10x_cec.d \
./Src/MCAL/src/stm32f10x_crc.d \
./Src/MCAL/src/stm32f10x_dac.d \
./Src/MCAL/src/stm32f10x_dbgmcu.d \
./Src/MCAL/src/stm32f10x_dma.d \
./Src/MCAL/src/stm32f10x_exti.d \
./Src/MCAL/src/stm32f10x_flash.d \
./Src/MCAL/src/stm32f10x_fsmc.d \
./Src/MCAL/src/stm32f10x_gpio.d \
./Src/MCAL/src/stm32f10x_i2c.d \
./Src/MCAL/src/stm32f10x_iwdg.d \
./Src/MCAL/src/stm32f10x_pwr.d \
./Src/MCAL/src/stm32f10x_rcc.d \
./Src/MCAL/src/stm32f10x_rtc.d \
./Src/MCAL/src/stm32f10x_sdio.d \
./Src/MCAL/src/stm32f10x_spi.d \
./Src/MCAL/src/stm32f10x_tim.d \
./Src/MCAL/src/stm32f10x_usart.d \
./Src/MCAL/src/stm32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/src/%.o Src/MCAL/src/%.su Src/MCAL/src/%.cyclo: ../Src/MCAL/src/%.c Src/MCAL/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/LIB/STD_TYPES" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/APP/Inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/include" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/Free_RTOS/portable/GCC/ARM_CM3" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/HAL/inc" -I"E:/WorkSpaces/STM_CUBE_IDE/GP_M3/Src/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-src

clean-Src-2f-MCAL-2f-src:
	-$(RM) ./Src/MCAL/src/misc.cyclo ./Src/MCAL/src/misc.d ./Src/MCAL/src/misc.o ./Src/MCAL/src/misc.su ./Src/MCAL/src/stm32f10x_adc.cyclo ./Src/MCAL/src/stm32f10x_adc.d ./Src/MCAL/src/stm32f10x_adc.o ./Src/MCAL/src/stm32f10x_adc.su ./Src/MCAL/src/stm32f10x_bkp.cyclo ./Src/MCAL/src/stm32f10x_bkp.d ./Src/MCAL/src/stm32f10x_bkp.o ./Src/MCAL/src/stm32f10x_bkp.su ./Src/MCAL/src/stm32f10x_can.cyclo ./Src/MCAL/src/stm32f10x_can.d ./Src/MCAL/src/stm32f10x_can.o ./Src/MCAL/src/stm32f10x_can.su ./Src/MCAL/src/stm32f10x_cec.cyclo ./Src/MCAL/src/stm32f10x_cec.d ./Src/MCAL/src/stm32f10x_cec.o ./Src/MCAL/src/stm32f10x_cec.su ./Src/MCAL/src/stm32f10x_crc.cyclo ./Src/MCAL/src/stm32f10x_crc.d ./Src/MCAL/src/stm32f10x_crc.o ./Src/MCAL/src/stm32f10x_crc.su ./Src/MCAL/src/stm32f10x_dac.cyclo ./Src/MCAL/src/stm32f10x_dac.d ./Src/MCAL/src/stm32f10x_dac.o ./Src/MCAL/src/stm32f10x_dac.su ./Src/MCAL/src/stm32f10x_dbgmcu.cyclo ./Src/MCAL/src/stm32f10x_dbgmcu.d ./Src/MCAL/src/stm32f10x_dbgmcu.o ./Src/MCAL/src/stm32f10x_dbgmcu.su ./Src/MCAL/src/stm32f10x_dma.cyclo ./Src/MCAL/src/stm32f10x_dma.d ./Src/MCAL/src/stm32f10x_dma.o ./Src/MCAL/src/stm32f10x_dma.su ./Src/MCAL/src/stm32f10x_exti.cyclo ./Src/MCAL/src/stm32f10x_exti.d ./Src/MCAL/src/stm32f10x_exti.o ./Src/MCAL/src/stm32f10x_exti.su ./Src/MCAL/src/stm32f10x_flash.cyclo ./Src/MCAL/src/stm32f10x_flash.d ./Src/MCAL/src/stm32f10x_flash.o ./Src/MCAL/src/stm32f10x_flash.su ./Src/MCAL/src/stm32f10x_fsmc.cyclo ./Src/MCAL/src/stm32f10x_fsmc.d ./Src/MCAL/src/stm32f10x_fsmc.o ./Src/MCAL/src/stm32f10x_fsmc.su ./Src/MCAL/src/stm32f10x_gpio.cyclo ./Src/MCAL/src/stm32f10x_gpio.d ./Src/MCAL/src/stm32f10x_gpio.o ./Src/MCAL/src/stm32f10x_gpio.su ./Src/MCAL/src/stm32f10x_i2c.cyclo ./Src/MCAL/src/stm32f10x_i2c.d ./Src/MCAL/src/stm32f10x_i2c.o ./Src/MCAL/src/stm32f10x_i2c.su ./Src/MCAL/src/stm32f10x_iwdg.cyclo ./Src/MCAL/src/stm32f10x_iwdg.d ./Src/MCAL/src/stm32f10x_iwdg.o ./Src/MCAL/src/stm32f10x_iwdg.su ./Src/MCAL/src/stm32f10x_pwr.cyclo ./Src/MCAL/src/stm32f10x_pwr.d ./Src/MCAL/src/stm32f10x_pwr.o ./Src/MCAL/src/stm32f10x_pwr.su ./Src/MCAL/src/stm32f10x_rcc.cyclo ./Src/MCAL/src/stm32f10x_rcc.d ./Src/MCAL/src/stm32f10x_rcc.o ./Src/MCAL/src/stm32f10x_rcc.su ./Src/MCAL/src/stm32f10x_rtc.cyclo ./Src/MCAL/src/stm32f10x_rtc.d ./Src/MCAL/src/stm32f10x_rtc.o ./Src/MCAL/src/stm32f10x_rtc.su ./Src/MCAL/src/stm32f10x_sdio.cyclo ./Src/MCAL/src/stm32f10x_sdio.d ./Src/MCAL/src/stm32f10x_sdio.o ./Src/MCAL/src/stm32f10x_sdio.su ./Src/MCAL/src/stm32f10x_spi.cyclo ./Src/MCAL/src/stm32f10x_spi.d ./Src/MCAL/src/stm32f10x_spi.o ./Src/MCAL/src/stm32f10x_spi.su ./Src/MCAL/src/stm32f10x_tim.cyclo ./Src/MCAL/src/stm32f10x_tim.d ./Src/MCAL/src/stm32f10x_tim.o ./Src/MCAL/src/stm32f10x_tim.su ./Src/MCAL/src/stm32f10x_usart.cyclo ./Src/MCAL/src/stm32f10x_usart.d ./Src/MCAL/src/stm32f10x_usart.o ./Src/MCAL/src/stm32f10x_usart.su ./Src/MCAL/src/stm32f10x_wwdg.cyclo ./Src/MCAL/src/stm32f10x_wwdg.d ./Src/MCAL/src/stm32f10x_wwdg.o ./Src/MCAL/src/stm32f10x_wwdg.su

.PHONY: clean-Src-2f-MCAL-2f-src

