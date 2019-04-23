################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../build/CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./build/CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./build/CMakeFiles/3.10.2/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
build/CMakeFiles/3.10.2/CompilerIdCXX/%.o: ../build/CMakeFiles/3.10.2/CompilerIdCXX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/steve/Downloads/OgreSDK/ogre-1.11.2//OgreMain/include" -I"/home/steve/Downloads/OgreSDK/ogre-1.11.2//build/include" -I"/home/steve/Downloads/OgreSDK/ogre-1.11.2//Components/RTShaderSystem/include" -I"/home/steve/Downloads/OgreSDK/ogre-1.11.2//Components/Bites/include" -I"/home/steve/Downloads/OgreSDK/ogre-1.11.2//Samples/Common/include" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


