
#include "diag/Trace.h"

int signalvalue = 5;

char message[10]="hello!";

/*
void sig_initialzer()
{
	signalvalue = 1;
	return;
}
*/

void sig_checker()
{
	trace_puts(message);
	signalvalue = 1;
	return;
}
