################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/2021HW5starter.cpp \
../src/Board.cpp \
../src/GamePiece.cpp \
../src/LinkedList.cpp \
../src/Production.cpp \
../src/Tests.cpp 

OBJS += \
./src/2021HW5starter.o \
./src/Board.o \
./src/GamePiece.o \
./src/LinkedList.o \
./src/Production.o \
./src/Tests.o 

CPP_DEPS += \
./src/2021HW5starter.d \
./src/Board.d \
./src/GamePiece.d \
./src/LinkedList.d \
./src/Production.d \
./src/Tests.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


