################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/system_stm32f4xx.c 

CPP_SRCS += \
../Core/Src/Bitmaps.cpp \
../Core/Src/Drawable_Content.cpp \
../Core/Src/ILI9225.cpp \
../Core/Src/IM_IO.cpp \
../Core/Src/Level_Manager.cpp \
../Core/Src/Renderer.cpp \
../Core/Src/Soldier.cpp \
../Core/Src/Soldier_Handler.cpp \
../Core/Src/main.cpp 

C_DEPS += \
./Core/Src/system_stm32f4xx.d 

OBJS += \
./Core/Src/Bitmaps.o \
./Core/Src/Drawable_Content.o \
./Core/Src/ILI9225.o \
./Core/Src/IM_IO.o \
./Core/Src/Level_Manager.o \
./Core/Src/Renderer.o \
./Core/Src/Soldier.o \
./Core/Src/Soldier_Handler.o \
./Core/Src/main.o \
./Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./Core/Src/Bitmaps.d \
./Core/Src/Drawable_Content.d \
./Core/Src/ILI9225.d \
./Core/Src/IM_IO.d \
./Core/Src/Level_Manager.d \
./Core/Src/Renderer.d \
./Core/Src/Soldier.d \
./Core/Src/Soldier_Handler.d \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Bitmaps.d ./Core/Src/Bitmaps.o ./Core/Src/Bitmaps.su ./Core/Src/Drawable_Content.d ./Core/Src/Drawable_Content.o ./Core/Src/Drawable_Content.su ./Core/Src/ILI9225.d ./Core/Src/ILI9225.o ./Core/Src/ILI9225.su ./Core/Src/IM_IO.d ./Core/Src/IM_IO.o ./Core/Src/IM_IO.su ./Core/Src/Level_Manager.d ./Core/Src/Level_Manager.o ./Core/Src/Level_Manager.su ./Core/Src/Renderer.d ./Core/Src/Renderer.o ./Core/Src/Renderer.su ./Core/Src/Soldier.d ./Core/Src/Soldier.o ./Core/Src/Soldier.su ./Core/Src/Soldier_Handler.d ./Core/Src/Soldier_Handler.o ./Core/Src/Soldier_Handler.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

