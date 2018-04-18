
all2: 
	arm-none-eabi-g++ -c Signal.cpp \
		-I../system/include \
		-I../include \
		-I../system/include/cmsis \
		-I../system/include/stm32f4-hal \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/ \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1 \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/arm-none-eabi/thumb/v7e-m \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/backward \
		-I../GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include \
		-I../GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include-fixed \
		-std=c++11 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics \
		-DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000
	cp Signal.o ../Debug/src
	
all:
	arm-none-eabi-g++ -c Signal.cpp \
		-I../system/include \
		-I../include \
		-I../system/include/cmsis \
		-I../system/include/stm32f4-hal \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/ \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1 \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/arm-none-eabi/thumb/v7e-m \
		-I../GNU_Tools_ARM_Embedded/arm-none-eabi/include/c++/6.3.1/backward \
		-I../GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include \
		-I../GNU_Tools_ARM_Embedded/lib/gcc/arm-none-eabi/6.3.1/include-fixed \
		-std=c++11 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics \
		-DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx
	cp Signal.o ../Debug/src
	
	

obj:
	arm-none-eabi-objdump -d Signal.o > obj

clean:
	rm -f *.o obj *.s
