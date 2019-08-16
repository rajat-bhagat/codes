#include<stdio.h>
#include<stdlib.h>

void push();
int pop();
void display();

int top=-1;
int a[10]={0};

int main()
{
	int c=0;
	int n;
	while(1)
	{
		
		printf("\n1.PUSH\n2.Display\n3.POP\n4.Exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&n);
		switch(n)
		{	
			case 1:
				push();
				break;
			case 2:
				display();
				break;
			case 3:
				pop();
				//printf("value poped is %d",c);
				break;
			case 4: exit(1);
		}
	}
}

void push()
{	int x=0;
	if(top==10)
	{
		printf("\n Stack overflow");
	}
	else
	{
		printf("Enter value to push : ");
		scanf("%d",&x);

		top++;
		a[top]=x;
	}
}

int pop()
{
	//return a[top];
	printf("value poped is %d\n",a[top]);
	top--;
}

void display()
{
	if(top==-1)
		printf("\n stack empty");
	else
	{
		for(int i=0;i<=top;i++)
		{
			printf("%d ",a[i]);
		}
	}
}
