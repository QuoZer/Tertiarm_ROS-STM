################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f103c8tx.s 

S_DEPS += \
./Core/Startup/startup_stm32f103c8tx.d 

OBJS += \
./Core/Startup/startup_stm32f103c8tx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f103c8tx.o: ../Core/Startup/startup_stm32f103c8tx.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g -c -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/util -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/SERVO -I/home/roser/Documents/stm32/deb_stm_files/C8_try/ros_lib -I/home/roser/Documents/stm32/deb_stm_files/C8_try/mylibs/JOYSTICK -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f103c8tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

