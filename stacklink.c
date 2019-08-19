#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
	int index;
};


struct node* top = NULL;

void insert()
{
	static int i=1;
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	printf("Enter Data:\n");
	scanf("%d",&temp->data);
	temp->next = top;
	top = temp;
	temp->index=i;
	i++;
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

void search()
{
 	struct node* temp;
 	int t;
   		
	printf("Enter element to find : ");
	scanf("%d",&t);

	temp=top;

	while(temp!=NULL)
		{
			if(temp->data==t)
				{
					printf("Index= %d",temp->index);
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
