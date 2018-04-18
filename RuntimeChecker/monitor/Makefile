
run:
	./test

all: CHECKER SIGNAL

CHECKER: CheckerAPIs checker_initializer
	arm-none-eabi-ar rc libChecker.a CheckerAPIs.o checker_initializer.o
	
SIGNAL: SignalAPIs
	arm-none-eabi-ar rc libSignal.a SignalAPIs.o

SignalAPIs:
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c SignalAPIs.c

CheckerAPIs:
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -c CheckerAPIs.cpp

checker_initializer:
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -c checker_initializer.cpp

obj:
	arm-none-eabi-objdump -d libSignal.a > obj_sig
	arm-none-eabi-objdump -d libChecker.a > obj_checker

clean:
	rm -f *.o test *.a obj_sig
