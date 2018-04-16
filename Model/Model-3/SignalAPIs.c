
#include <stdio.h>

#define BB_NUM 200

unsigned int sig_queue[BB_NUM*2];
const int size_sig_queue = BB_NUM*2;
unsigned int current_size_sig_queue = 0;

typedef int bool;
#define true 1
#define false 0

bool sig_init_flag = true;

void sig_initializer()
{
	if(sig_init_flag == true)
	{
		sig_init_flag = false;
		// SWI_INITIALIZER;
	}
}

#undef true
#undef false

void sig_checker(unsigned int node_id)
{

	if(current_size_sig_queue + 1 < size_sig_queue)
	{
		sig_queue[current_size_sig_queue] = node_id;
		current_size_sig_queue++;
	}

	else
	{
		// SWI_SIG_ERROR
	}

}

void sig_debug()
{


	if(current_size_sig_queue == 0)
	{
		printf(" [DEBUG: sig_queue]: empty\n");
	}

	else
	{
		for(int i=0; i < current_size_sig_queue; i++)
		{
			printf("signal %x ", sig_queue[i]);
		}
		printf("\n");
	}

}
