################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ahb_dma.c \
../src/ahb_spi.c \
../src/axi_dma.c \
../src/debug.c \
../src/dsp_dmss.c \
../src/dsp_mailbox.c \
../src/dsp_pmss.c \
../src/dsp_rcc.c \
../src/dsp_sctrl.c \
../src/flash.c \
../src/gpio.c \
../src/i2c.c \
../src/i2s.c \
../src/kernel.c \
../src/psram.c \
../src/sdio.c \
../src/sram.c \
../src/testbench_dsp.c \
../src/uart.c 

OBJS += \
./src/ahb_dma.o \
./src/ahb_spi.o \
./src/axi_dma.o \
./src/debug.o \
./src/dsp_dmss.o \
./src/dsp_mailbox.o \
./src/dsp_pmss.o \
./src/dsp_rcc.o \
./src/dsp_sctrl.o \
./src/flash.o \
./src/gpio.o \
./src/i2c.o \
./src/i2s.o \
./src/kernel.o \
./src/psram.o \
./src/sdio.o \
./src/sram.o \
./src/testbench_dsp.o \
./src/uart.o 

C_DEPS += \
./src/ahb_dma.d \
./src/ahb_spi.d \
./src/axi_dma.d \
./src/debug.d \
./src/dsp_dmss.d \
./src/dsp_mailbox.d \
./src/dsp_pmss.d \
./src/dsp_rcc.d \
./src/dsp_sctrl.d \
./src/flash.d \
./src/gpio.d \
./src/i2c.d \
./src/i2s.d \
./src/kernel.d \
./src/psram.d \
./src/sdio.d \
./src/sram.d \
./src/testbench_dsp.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: CEVA-ELF C Compiler'
	C:\CEVA-ToolBox\V22\SensPro\toolbox\../cevatools/bin/clang --target=senspro250-unknown-unknown-elf -mcpu=sensprov1.2.0 -mvmpyv5 -mvmpyext -mnonlinear=1 -mno-vbnn -mno-vhist -mlvu=1 -mfp=2 -mdpfp=2 -mno-hpfp -mno-vfpsimd -mvfp=0  -c -fmessage-length=0 -O0 -g -Wall -pedantic -Wa,--no-rstr-check -I"D:\Toolbox\workspace_dsp_app12345678\testbench_dsp\dsp_csl\include" -I"D:\Toolbox\workspace_dsp_app12345678\testbench_dsp\dsp_lib\includes" -D_LIBCPP_INLINE_VISIBILITY="" -D_LIBCPP_EXTERN_TEMPLATE_INLINE_VISIBILITY="" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


