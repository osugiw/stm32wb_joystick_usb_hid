################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Self-Learning/learn-stm32/HID_Standalone/Drivers/BSP/P-NUCLEO-WB55.Nucleo/stm32wbxx_nucleo.c 

OBJS += \
./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.o 

C_DEPS += \
./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.o: D:/Self-Learning/learn-stm32/HID_Standalone/Drivers/BSP/P-NUCLEO-WB55.Nucleo/stm32wbxx_nucleo.c Drivers/BSP/P-NUCLEO-WB55-Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32WB55xx -c -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/P-NUCLEO-WB55.Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-P-2d-NUCLEO-2d-WB55-2d-Nucleo

clean-Drivers-2f-BSP-2f-P-2d-NUCLEO-2d-WB55-2d-Nucleo:
	-$(RM) ./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.cyclo ./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.d ./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.o ./Drivers/BSP/P-NUCLEO-WB55-Nucleo/stm32wbxx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-P-2d-NUCLEO-2d-WB55-2d-Nucleo

