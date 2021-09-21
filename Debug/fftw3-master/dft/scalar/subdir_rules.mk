################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
n.obj: ../fftw3-master/dft/scalar/n.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/dft/scalar/n.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

t.obj: ../fftw3-master/dft/scalar/t.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml --float_support=fpu32 --opt_for_speed=0 --include_path="F:/ccs1/28335_AD7656/INCLUDE" --include_path="F:/ccs1/28335_AD7656/fftw3-master" --include_path="F:/ccs1/28335_AD7656/fftw3-master/api" --include_path="F:/ccs1/28335_AD7656/fftw3-master/dft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/kernel" --include_path="F:/ccs1/28335_AD7656/fftw3-master/rdft" --include_path="F:/ccs1/28335_AD7656/fftw3-master/reodft" --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.5/include" -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="fftw3-master/dft/scalar/t.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


