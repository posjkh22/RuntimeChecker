




void task()
{
	int x = 2;
	int y = 3;
	int b = 0;

	if(b == 0)
	{
		x = x-y;
	}
	else
	{
		y = x-y;
	}

	x = x++;
	y = y++;

	return;
}

int main()
{
	
	int x = 0;
 	int a = 0;

	if(a == 0)
	{
		x++;
		task();
	}

	a = 2;
	x = x+a;

	return 0;
}


