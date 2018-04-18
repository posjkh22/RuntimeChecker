
bc: 
	clang++ -S -emit-llvm -o main.bc main.cpp \
		-I./system/include \
		-I./include \
		-I./system/include/cmsis \
		-I./system/include/stm32f4-hal \
		-I./GNU_Tools_ARM_Embedded/arm-none-eabi/include/ \
		-I./GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1 \
		-I./GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/arm-none-eabi/thumb/v7e-m \
		-I./GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/backward \
		-I./GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include \
		-I./GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include-fixed \
		-std=c++11 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics \
		-DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000

#-fabi-version=0 \

assemble:
	llc -march=arm -mcpu=cortex-m4 -arm-implicit-it=thumb main.bc

obj:
	arm-none-eabi-g++ -c main.s
	cp main.o ./Debug/src

readelf:
	arm-none-eabi-readelf -a main.o > readelf

objdump:
	arm-none-eabi-objdump -d main.o > main_obj

clean:
	rm -f *.bc *.s *.o
