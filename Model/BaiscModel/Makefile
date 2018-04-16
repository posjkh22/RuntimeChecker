
run:
	./test

all: sig main checker 
	gcc -o test main.o sig.o checker.o -lstdc++

sig:
	gcc -c sig.c

main:
	gcc -c main.c

checker:
	g++ -c checker.cpp


clean:
	rm -f *.o test
