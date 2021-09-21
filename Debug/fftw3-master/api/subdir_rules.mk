################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
apiplan.obj: ../fftw3-master/api/apiplan.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/apiplan.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configure.obj: ../fftw3-master/api/configure.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/configure.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-dft-c2r.obj: ../fftw3-master/api/execute-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-dft-r2c.obj: ../fftw3-master/api/execute-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-dft.obj: ../fftw3-master/api/execute-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-r2r.obj: ../fftw3-master/api/execute-r2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-r2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-split-dft-c2r.obj: ../fftw3-master/api/execute-split-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-split-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-split-dft-r2c.obj: ../fftw3-master/api/execute-split-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-split-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute-split-dft.obj: ../fftw3-master/api/execute-split-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute-split-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

execute.obj: ../fftw3-master/api/execute.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/execute.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

export-wisdom-to-file.obj: ../fftw3-master/api/export-wisdom-to-file.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/export-wisdom-to-file.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

export-wisdom-to-string.obj: ../fftw3-master/api/export-wisdom-to-string.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/export-wisdom-to-string.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

export-wisdom.obj: ../fftw3-master/api/export-wisdom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/export-wisdom.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

f77api.obj: ../fftw3-master/api/f77api.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/f77api.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

flops.obj: ../fftw3-master/api/flops.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/flops.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

forget-wisdom.obj: ../fftw3-master/api/forget-wisdom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/forget-wisdom.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

import-system-wisdom.obj: ../fftw3-master/api/import-system-wisdom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/import-system-wisdom.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

import-wisdom-from-file.obj: ../fftw3-master/api/import-wisdom-from-file.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/import-wisdom-from-file.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

import-wisdom-from-string.obj: ../fftw3-master/api/import-wisdom-from-string.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/import-wisdom-from-string.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

import-wisdom.obj: ../fftw3-master/api/import-wisdom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/import-wisdom.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

malloc.obj: ../fftw3-master/api/malloc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/malloc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

map-r2r-kind.obj: ../fftw3-master/api/map-r2r-kind.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/map-r2r-kind.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mapflags.obj: ../fftw3-master/api/mapflags.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mapflags.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mkprinter-file.obj: ../fftw3-master/api/mkprinter-file.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mkprinter-file.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mkprinter-str.obj: ../fftw3-master/api/mkprinter-str.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mkprinter-str.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mktensor-iodims.obj: ../fftw3-master/api/mktensor-iodims.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mktensor-iodims.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mktensor-iodims64.obj: ../fftw3-master/api/mktensor-iodims64.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mktensor-iodims64.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mktensor-rowmajor.obj: ../fftw3-master/api/mktensor-rowmajor.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/mktensor-rowmajor.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-1d.obj: ../fftw3-master/api/plan-dft-1d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-1d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-2d.obj: ../fftw3-master/api/plan-dft-2d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-2d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-3d.obj: ../fftw3-master/api/plan-dft-3d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-3d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-c2r-1d.obj: ../fftw3-master/api/plan-dft-c2r-1d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-c2r-1d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-c2r-2d.obj: ../fftw3-master/api/plan-dft-c2r-2d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-c2r-2d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-c2r-3d.obj: ../fftw3-master/api/plan-dft-c2r-3d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-c2r-3d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-c2r.obj: ../fftw3-master/api/plan-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-r2c-1d.obj: ../fftw3-master/api/plan-dft-r2c-1d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-r2c-1d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-r2c-2d.obj: ../fftw3-master/api/plan-dft-r2c-2d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-r2c-2d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-r2c-3d.obj: ../fftw3-master/api/plan-dft-r2c-3d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-r2c-3d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft-r2c.obj: ../fftw3-master/api/plan-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-dft.obj: ../fftw3-master/api/plan-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-dft-c2r.obj: ../fftw3-master/api/plan-guru-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-dft-r2c.obj: ../fftw3-master/api/plan-guru-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-dft.obj: ../fftw3-master/api/plan-guru-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-r2r.obj: ../fftw3-master/api/plan-guru-r2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-r2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-split-dft-c2r.obj: ../fftw3-master/api/plan-guru-split-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-split-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-split-dft-r2c.obj: ../fftw3-master/api/plan-guru-split-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-split-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru-split-dft.obj: ../fftw3-master/api/plan-guru-split-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru-split-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-dft-c2r.obj: ../fftw3-master/api/plan-guru64-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-dft-r2c.obj: ../fftw3-master/api/plan-guru64-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-dft.obj: ../fftw3-master/api/plan-guru64-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-r2r.obj: ../fftw3-master/api/plan-guru64-r2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-r2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-split-dft-c2r.obj: ../fftw3-master/api/plan-guru64-split-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-split-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-split-dft-r2c.obj: ../fftw3-master/api/plan-guru64-split-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-split-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-guru64-split-dft.obj: ../fftw3-master/api/plan-guru64-split-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-guru64-split-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-many-dft-c2r.obj: ../fftw3-master/api/plan-many-dft-c2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-many-dft-c2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-many-dft-r2c.obj: ../fftw3-master/api/plan-many-dft-r2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-many-dft-r2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-many-dft.obj: ../fftw3-master/api/plan-many-dft.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-many-dft.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-many-r2r.obj: ../fftw3-master/api/plan-many-r2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-many-r2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-r2r-1d.obj: ../fftw3-master/api/plan-r2r-1d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-r2r-1d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-r2r-2d.obj: ../fftw3-master/api/plan-r2r-2d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-r2r-2d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-r2r-3d.obj: ../fftw3-master/api/plan-r2r-3d.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-r2r-3d.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

plan-r2r.obj: ../fftw3-master/api/plan-r2r.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/plan-r2r.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

print-plan.obj: ../fftw3-master/api/print-plan.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/print-plan.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rdft2-pad.obj: ../fftw3-master/api/rdft2-pad.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/rdft2-pad.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

the-planner.obj: ../fftw3-master/api/the-planner.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/the-planner.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

version.obj: ../fftw3-master/api/version.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/api/version.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


