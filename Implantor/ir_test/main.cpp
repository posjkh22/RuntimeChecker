
void func3(int);

void func(int a, int b)
{
	int c = a+b;
}

void func2(int a)
{
	a++;
}

int main()
{
	func(1, 2);
	func2(2);
	func3(1);

	return 0;
}
