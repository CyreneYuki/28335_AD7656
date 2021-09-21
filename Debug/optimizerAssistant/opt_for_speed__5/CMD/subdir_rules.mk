################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CMD/28335_RAM_lnk.exe: ../CMD/28335_RAM_lnk.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=5 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off -z -m"../CMD/Debug/28335_AD7656.map" --heap_size=1000 --stack_size=1000 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -i"F:/ccs1/28335_AD7656" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="28335_AD7656_linkInfo.xml" --entry_point=code_start --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMD/DSP2833x_Headers_nonBIOS.exe: ../CMD/DSP2833x_Headers_nonBIOS.cmd $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=5 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off -z -m"../CMD/Debug/28335_AD7656.map" --heap_size=1000 --stack_size=1000 --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -i"F:/ccs1/28335_AD7656" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="28335_AD7656_linkInfo.xml" --entry_point=code_start --rom_model -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


