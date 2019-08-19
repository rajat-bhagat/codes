//stack implementation using linked list

#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
	int index;
};// each node contains index, data, and address of next node


struct node* top = NULL;//node pointing the lastest node

void insert()
{
	static int pos=1;
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));// dynamic memory allocation
	printf("Enter Data:\n");
	scanf("%d",&temp->data);
	temp->next = top;//linking the current node to the previous node
	top = temp;//assigning the current node as top
	temp->index=pos;
	pos++;
}

void display()
{
	struct node* temp;
	if(top == NULL)//shows stack is empty
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
		temp->next = NULL;// breaking the link
		free(temp);// freeing the memory that is not needed
	}
}

void search()
{
 	struct node* temp;
 	int find;
   		
	printf("Enter element to find : ");
	scanf("%d",&find);

	temp=top;

	while(temp!=NULL)
		{
			if(temp->data==find)
				{
					printf("Index= %d",temp->index);// printing the position of the element
				}
			temp=temp->next;	
		}						
}

void main()
{
	while(1)
	{
		int n;
		printf("\n1.Insert\n2.Display\n3.Delete\n4.Search\n5.Exit\n");
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
			case 4: search();
				break;
			case 5: exit(0);
		}
	}

}
