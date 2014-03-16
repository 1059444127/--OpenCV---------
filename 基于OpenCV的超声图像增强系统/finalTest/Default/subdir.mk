################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../calcHistogram.cpp \
../contrastEnhancement.cpp \
../multiWin.cpp \
../myCorrfactor.cpp \
../myTophat.cpp \
../opencvImagEnhance.cpp \
../plotImhist.cpp 

OBJS += \
./calcHistogram.o \
./contrastEnhancement.o \
./multiWin.o \
./myCorrfactor.o \
./myTophat.o \
./opencvImagEnhance.o \
./plotImhist.o 

CPP_DEPS += \
./calcHistogram.d \
./contrastEnhancement.d \
./multiWin.d \
./myCorrfactor.d \
./myTophat.d \
./opencvImagEnhance.d \
./plotImhist.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


