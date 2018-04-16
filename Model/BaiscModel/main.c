
#include <stdio.h>
#include <unistd.h>

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
	int branch2 = 0;


	sig_checker(0x00020001);
	sleep(1);
	
	if(branch2 == 0)
	{
		sig_checker(0x00020002);
		sleep(1);
	}
	else
	{
		sig_checker(0x00020003);
		sleep(1);
	}
	checker();
	sig_debug();

	sig_checker(0x00020004);
	sleep(1);

	return;
}



int main()
{

	int branch1 = 0;

	while(1)
	{

	checker();

	//sig_init
	sig_initializer();

	//checker_init
	checker_initializer(0);


	sig_checker(0x00010001);
	sleep(1);

	sig_checker(0x00010002);
	sleep(1);

	if(branch1 == 0)
	{
		sig_checker(0x00010003);
		sleep(1);
		checker();
		sig_debug();
		task1();
	}
	

	else
	{
		sig_checker(0x00010004);
		sleep(1);
	}
	
	checker();

	sig_checker(0x00010005);
	sleep(1);
	sig_debug();
	checker();
	
	}
	

	return 0;
}
