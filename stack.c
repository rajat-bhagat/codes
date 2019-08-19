//stack data structure implemntation using array

#include<stdio.h>
#include<stdlib.h>

void push();//add value to stack
void pop();//fetch value from stack
void display();
void search();

int top=-1;
int a[10]={0};//size of stack

int main()
{
	int n;
	while(1)
	{
		
		printf("\n1.PUSH\n2.Display\n3.POP\n4.Search\n5.Exit\n");
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
			case 4: search();
				break;
			case 5: exit(0);
		}
	}
}

void push()
{	int x=0;
	if(top>=9)//stack size full
	{
		printf("\n Stack overflow");
	}
	else
	{
		printf("Enter value to push : ");
		scanf("%d",&x);

		++top;
		a[top]=x;
	}
}

void pop()
{
	printf("value poped is %d\n",a[top]);//last value entered value is poped
	top--;//count decreased
}

void display()
{
	if(top==-1)// empty stack
		printf("\n stack empty");
	else
	{
		for(int i=0;i<=top;i++)
		{
			printf("%d ",a[i]);
		}
	}
}

void search()
{
	int find=0;
	int count=top;
	printf("Enter element to search");
	scanf("%d",&find);
	if(top==-1)
		printf("\n stack is empty\n");
	else
	{
		while(count>=0)
		{
			if(a[count]==find)
			{
				printf("index= %d",count+1);
			}
			count--;
		}
	}

}
