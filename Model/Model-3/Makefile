
run:
	./test

all: SignalAPIs main CheckerAPIs checker_initializer
	gcc -o test main.o SignalAPIs.o CheckerAPIs.o checker_initializer.o -lstdc++

SignalAPIs:
	gcc -O0 -c SignalAPIs.c

main:
	gcc -O0 -c main.c

CheckerAPIs:
	g++ -O0 -c CheckerAPIs.cpp

checker_initializer:
	g++ -O0 -c checker_initializer.cpp

clean:
	rm -f *.o test
