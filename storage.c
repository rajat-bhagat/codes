#include<stdio.h>


void autostorage()
{
	printf("\nauto class\n");
	auto int a=32;
	printf("value of a = %d\n",a);
}

void registerstorage()
{
	printf("register class\n");
	register int b=12;
	printf("value of b = %d\n",b);
}

void externstorage()
{
	printf("extern class\n");
	extern int x;
	printf("value of c as defined = %d\n",x);
	x=20;
	printf("updated value of c = %d\n",x);
}

void staticstorage()
{
	int count=0;
	printf("static class");
	for(count=0;count<5;count++)
	{
		static int d=10;
		int e=10;
		d++;e++;
		printf("value of d = %d\n",d);
		printf("value of e = %d\n",e);
	}
}


int main()
{
	autostorage();
	registerstorage();
	externstorage();
	staticstorage();
	return 0;
}

