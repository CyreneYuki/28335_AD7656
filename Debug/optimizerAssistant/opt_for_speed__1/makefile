################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
"./project.obj" \
"./FFT.obj" \
"./DSP2833x_usDelay.obj" \
"./DSP2833x_Xintf.obj" \
"./DSP2833x_SysCtrl.obj" \
"./DSP2833x_PieVect.obj" \
"./DSP2833x_PieCtrl.obj" \
"./DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_DefaultIsr.obj" \
"./DSP2833x_DMA.obj" \
"./DSP2833x_CpuTimers.obj" \
"./DSP2833x_CodeStartBranch.obj" \
"./DSP2833x_ADC_cal.obj" \
"../CMD/28335_RAM_lnk.cmd" \
-l"rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include SRC/subdir_vars.mk
-include CMD/subdir_vars.mk
-include SRC/subdir_rules.mk
-include CMD/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
28335_AD7656.out \

EXE_OUTPUTS__QUOTED += \
"28335_AD7656.out" \

BIN_OUTPUTS += \
28335_AD7656.hex \

BIN_OUTPUTS__QUOTED += \
"28335_AD7656.hex" \


# All Target
all: 28335_AD7656.out

# Tool invocations
28335_AD7656.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=1 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off -z -m"28335_AD7656.map" --heap_size=1000 --stack_size=1000 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -i"F:/ccs1/28335_AD7656" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="28335_AD7656_linkInfo.xml" --entry_point=code_start --rom_model -o "28335_AD7656.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

28335_AD7656.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "28335_AD7656.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "SRC\DSP2833x_CpuTimers.pp" "SRC\DSP2833x_DMA.pp" "SRC\DSP2833x_DefaultIsr.pp" "SRC\DSP2833x_GlobalVariableDefs.pp" "SRC\DSP2833x_PieCtrl.pp" "SRC\DSP2833x_PieVect.pp" "SRC\DSP2833x_SysCtrl.pp" "SRC\DSP2833x_Xintf.pp" "SRC\project.pp" 
	-$(RM) "SRC\FFT.pp" 
	-$(RM) "DSP2833x_ADC_cal.obj" "DSP2833x_CodeStartBranch.obj" "DSP2833x_CpuTimers.obj" "DSP2833x_DMA.obj" "DSP2833x_DefaultIsr.obj" "DSP2833x_GlobalVariableDefs.obj" "DSP2833x_PieCtrl.obj" "DSP2833x_PieVect.obj" "DSP2833x_SysCtrl.obj" "DSP2833x_Xintf.obj" "DSP2833x_usDelay.obj" "FFT.obj" "project.obj" 
	-$(RM) "SRC\DSP2833x_ADC_cal.pp" "SRC\DSP2833x_CodeStartBranch.pp" "SRC\DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

