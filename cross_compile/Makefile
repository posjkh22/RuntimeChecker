
CROSS_ARM_GNU_C_COMPILE_OPTION=-DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -std=gnu11

all: cross_compile_assemble


cross_compile_assemble: ir
	llc -march=arm -mcpu=cortex-m4 -arm-implicit-it=thumb test.ll

ir: 
	clang++ -S -emit-llvm test.c

#cross_compile2: ir
#	llc -march=arm -mcpu=cortex-m4 -filetype=obj -o test.o

object-arm:
	arm-none-eabi-g++ -c test.s $(CROSS_ARM_GNU_C_COMPILE_OPTION)

readelf-arm:
	arm-none-eabi-readelf -a test.o > readelf_out

#-I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal"

compared_assemble:
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -S test.c -o compared_test.s

compare:
	arm-none-eabi-g++ -c -mcpu=cortex-m4 -mthumb test2.c
	arm-none-eabi-ar rc libtest2.a test2.o

lib:
	arm-none-eabi-ar rc libtest.a test.o

obj:
	arm-none-eabi-objdump -d libtest.a

clean:
	rm -f *.ll *.o *.s
