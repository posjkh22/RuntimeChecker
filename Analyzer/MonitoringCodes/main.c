
#include <stdio.h>
#include <unistd.h>

unsigned int count = 0;

////////////////////////////

/* checker */

void checker_initializer(unsigned int);
void checker();


////////////////////////////

/* signal_checker */

void sig_initializer();
void sig_checker(int);
void sig_debug();

////////////////////////////


void task1()
{


	int branch2 = count %3;
	sig_checker(0x00010001);
	
	if(branch2 == 0)
	{
		sig_checker(0x00010002);
	}
	else
	{
		sig_checker(0x00010003);
	}
	checker();

	sig_checker(0x00010004);
	checker();

	return;
}



int main()
{

	while(1){	
	count++;
		
	int branch1 = count %2;

	//sig_init
	sig_initializer();

	//checker_init
	checker_initializer(0);


	sig_checker(0x00020001);
	
	if(count %2 == 0)
	{
		checker();
	}

	if(branch1 == 0)
	{
		sig_checker(0x00020002);
		checker();
		task1();
	}
	

	sig_checker(0x00020003);
//	sig_debug();
	sleep(1);

	if(count %2 != 0)
	{
		checker();
	}
	
	}

	return 0;
}
