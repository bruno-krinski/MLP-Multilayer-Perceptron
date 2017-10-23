################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dataset.cpp \
../src/Layer.cpp \
../src/MLP.cpp \
../src/main.cpp 

OBJS += \
./src/Dataset.o \
./src/Layer.o \
./src/MLP.o \
./src/main.o 

CPP_DEPS += \
./src/Dataset.d \
./src/Layer.d \
./src/MLP.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


