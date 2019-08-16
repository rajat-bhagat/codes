#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
};

struct node* top = NULL;

void insert()
{
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	printf("Enter Data:\n");
	scanf("%d",&temp->data);
	temp->next = top;
	top = temp;

}

void display()
{
	struct node* temp;
	if(top == NULL)
	{
		printf("Stack is empty\n");
	}
	temp = top;
	while(temp != NULL)
	{
		printf("Data is %d\n",temp->data);
		temp = temp->next;
	}	
}

void delete()
{
	struct node* temp;
	if(top == NULL)
	{
		printf("No data\n");
	}
	else
	{
		temp = top;
		printf("Deleted data is %d",temp->data);
		top = temp->next;
		temp->next = NULL;
		free(temp);
	}
}

void main()
{
	while(1)
	{
		int n;
		printf("\n1.Insert\n2.Display\n3.Delete\n4.Exit\n");
		printf("Enter your choice:\n");
		scanf("%d",&n);
		switch(n)
		{	
			case 1:
				insert();
				break;
			case 2:
				display();
				break;
			case 3:
				delete();
				break;
			case 4: exit(1);
		}
	}

}
