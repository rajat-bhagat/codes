/**
 * @file stdio.h
 * @brief this header file contains all the standard input and output functions.
 *
 * @author   Rajat Bhagat
 *
 * @date 08/26/2019
 */

#include<stdio.h>
#include<stdlib.h>

void push();
int pop();
void display();

///initialised as empty stack
int top=-1;
///max size of the stack is 10
int a[10]={0};

/**
 * The program will for infiite times untill it is exited
 */
int main()
{
	int p=0;
	int n;
	while(1)
	{
		
		printf("\n1.Insert\n2.Display\n3.Delete\n4.Exit\n");
		printf("Enter your choice:\n");
		//The choice which will decide the  function to be performed
		scanf("%d",&n);
		switch(n)
		{	
			case 1:
				p=push();
				break;
			case 2:
				display();
				break;
			case 3:
				pop();
				break;
			case 4: exit(1);
		}
	}
}

/**
 * This method will be used to push the data to the stack.
 * @return c jst a random value.
 * @author  Rajat Bhagat
 * @date 08/26/2019
 */
int push()
{	int x=0,c=2;
	//Stack size is taken as 10.
	if(top==10)
	{
		printf("\n Stack overflow");
	}
	else
	{
		printf("Enter value to push : ");
		scanf("%d",&x);
		//The index will increment 
		top++;
		a[top]=x;

	}
return c;
}
/**
 * This method will be used to fetch the most recent data entered in the stack.
 * @date 08/26/2019
 */
int pop()
{
	//return a[top];
	printf("value poped is %d\n",a[top]);
	//The count will be decremented as the value is poped
	top--;
}
/**
 * This method will be used to print the complete stack from the last entered first.
 * @date 08/26/2019
 */ 
void display()
{	
	//Default value for the empty stack is -1
	if(top==-1)
		printf("\n stack empty");
	else
	{
		/// Prints all the values in the stack
		for(int i=0;i<=top;i++)
		{
			printf("%d ",a[i]);
		}
	}
}
