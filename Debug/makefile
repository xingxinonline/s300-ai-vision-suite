################################################################################
# Automatically-generated file. Do not edit!
################################################################################


ifeq ($(OS), Windows_NT)
    SHELL:=cmd
endif


VPATH += C:\CEVA-ToolBox\V22\SensPro\cevatools\lib\clang\14.0.6\cevasp-unknown-unknown-elf\rtlv1.2.0-fp2-dpfp2\lib

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: testbench_dsp.elf

# Tool invocations
testbench_dsp.elf: $(OBJS) D:/Toolbox/workspace_dsp_next_fd/testbench_dsp/Debug/testbench_dsp.ld $(LIBS)
	@echo 'Building target: $@'
	@echo 'Invoking: CEVA-ELF Linker'
	C:\CEVA-ToolBox\V22\SensPro\toolbox\../cevatools/bin/ceva-elf-ld -defsym __internal_code_size=128k -defsym __internal_data_size=256k -L"C:/CEVA-ToolBox/V22/SensPro/cevatools/lib/clang/14.0.6/cevasp-unknown-unknown-elf/rtlv1.2.0-fp2-dpfp2/lib"  -T D:\Toolbox\workspace_dsp_next_fd\testbench_dsp\Debug\testbench_dsp.ld --no-relax --no-gc-sections --no-rstr-check -Map=testbench_dsp.map $(OBJS) $(USER_OBJS) --start-group $(LIBS) --end-group -o  "testbench_dsp.elf"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) testbench_dsp.elf
	-@echo ' '

post-build:
	-ceva-elf-objdump.exe -D testbench_dsp.elf > testbench_dsp.dis & ceva-elf-objdump.exe -D -S testbench_dsp.elf > testbench_dsp.all.dis & ceva-elf-readelf.exe -h testbench_dsp.elf > temp_output.txt & for /f "tokens=4" %%i in ('findstr "Entry point address" temp_output.txt') do echo %%i > testbench_dsp.entrypoint & ceva-elf-objcopy -O binary -j .inttbl -j .text.internal testbench_dsp.elf dsp_ptcm_boot.bin & ceva-elf-objcopy -O binary -j .data.internal -j .cst.call -j .cst.mov -j .bss  -j __MALLOC_SECT testbench_dsp.elf dsp_dtcm_boot.bin & ceva-elf-objcopy -O binary -j .vi_data.external -j .text.external -j .data.external -j .bss1 -j __STACK_SECT -j __ARG_SECT -j .interrupt.external -j .network.data.external testbench_dsp.elf dsp_sram0_boot.bin & ceva-elf-objcopy -O binary -j .sram1.data testbench_dsp.elf dsp_sram1_boot.bin
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
