################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/custom_printf.c \
../src/debug.c \
../src/dsp_mailbox.c \
../src/dsp_mm.c \
../src/face_detect.c \
../src/testbench_dsp.c \
../src/tests_aux.c 

OBJS += \
./src/custom_printf.o \
./src/debug.o \
./src/dsp_mailbox.o \
./src/dsp_mm.o \
./src/face_detect.o \
./src/testbench_dsp.o \
./src/tests_aux.o 

C_DEPS += \
./src/custom_printf.d \
./src/debug.d \
./src/dsp_mailbox.d \
./src/dsp_mm.d \
./src/face_detect.d \
./src/testbench_dsp.d \
./src/tests_aux.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: CEVA-ELF C Compiler'
	C:\CEVA-ToolBox\V22\SensPro\toolbox\../cevatools/bin/clang --target=senspro250-unknown-unknown-elf -mcpu=sensprov1.2.0 -mvmpyv5 -mvmpyext -mnonlinear=1 -mno-vbnn -mno-vhist -mlvu=1 -mfp=2 -mdpfp=2 -mhpfp -mvfpsimd -mvfp=2  -c -fmessage-length=0 -O0 -g -Wall -pedantic -Wa,--no-rstr-check -I"D:\Toolbox\workspace_dsp_next_fd\testbench_dsp\dsp_csl\include" -I"D:\Toolbox\workspace_dsp_next_fd\testbench_dsp\dsp_lib\includes" -D_LIBCPP_INLINE_VISIBILITY="" -D_LIBCPP_EXTERN_TEMPLATE_INLINE_VISIBILITY="" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


