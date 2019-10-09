/**
 * @file stdio.h
 * @brief this header file contains the standard input output functions
 * @file stdlib.h
 * @brief this header file contains the standard funtions for process control, memory allocation etc
 *
 * @author Rajat Bhagat
 *
 * @date 10/07/2019
 */

#include<stdio.h>
#include<stdlib.h>

/**
 * @struct node 
 * @brief this structure represents the node of the binary tree
 *
 * @var data
 * it contains the value of the node
 *
 * @var left 
 * it is the pointer to the left child node to the parent node
 *
 * @var right
 * it is the pointer to the right child node to the parent node 
 */

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

/**
 * this function is used to create the new nodes while data insertion
 * @param value it contains the data to be stored in that node
 * @return returning the new node that is created
 */
struct node* createNode(int value){
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/**
 * this function finds the node with the minimun value
 * @param root it is the current node that ils being worked upon
 * @return returns the node with the minimum value
 */
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) // node with minimum value will have no left child
        return find_minimum(root->left); // left most element will be minimum
    return root;
}

/**
 * this function is used to insert the node in the binary tree
 * @param root it is the root node 
 * @param data it has the value to be stored in the node
 * @return it returns the root node
 */
struct node* insert(struct node* root, int data)
{
	if (root == NULL) return createNode(data);
	if (data < root->data)
		root->left  = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);   

	return root;
}

/**
 * this function searches for a particular value is present or not
 * @param root it is the current node to be worked upon
 * @param number the data value of the node to be searched
 * @return it returns the node whose data matches the data to be searched
 */
struct node* search(struct node* root,int number)
{
	if(root == NULL)
		return NULL;
	if(number == root->data)
		return root;
	if(number < root->data)
		return search(root->left,number);
	if(number > root->data)
		return search(root->right,number);
}

/**
 * this function deletes the node from the binary tree 
 * @param root it is the current node being worked upon
 * @param number it is the data value of the node to be deleted
 * @return returns the child nodes so as to link them to the parent of the deleted node
 */
struct node* delete(struct node *root, int number)
{
	if(root==NULL)
		return NULL;
	if (number>root->data)
		root->right = delete(root->right, number);
	else if(number<root->data)
		root->left = delete(root->left, number);
	else
	{
		//No Children
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			return NULL;
		}

		//One Child
		else if(root->left==NULL || root->right==NULL)
		{
			struct node *temp;
			if(root->left==NULL)
				temp = root->right;
			else
				temp = root->left;
			free(root);
			return temp;
		}

		//Two Children
		else
		{
			struct node *temp = find_minimum(root->right);
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
		}
	}
	return root;
}


/**
 * this function is used to display the tree in "inorder" format
 * @param root it is the root node of the tree
 */
void inorder(struct node* root){
	if(root == NULL) return;
	inorder(root->left);
	printf("%d ->", root->data);
	inorder(root->right);
}

/**
 * it is the main driver program for the Binary search tree
 */
int main(){
	struct node *root = NULL;
	struct node *result;
	int choice,data,find,remove;

	while(1)
	{
		printf("\n1.Create Root Node \n2.Insert Node \n3.Search \n4.Display \n5.Delete \n6.Exit \n");
		printf("Enter choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1: printf("Enter data: ");
				scanf("%d",&data);
				root=insert(root,data);
				break;
			case 2: printf("Enter data: ");
				scanf("%d",&data);
				insert(root,data);
				break;
			case 3: printf("Enter data to search: ");
				scanf("%d",&find);
				result=search(root,find);
				if(result->data!= '\0')
					printf("data found");
				else
					printf("invalid data");
				break;
			case 4: printf("the elements are: \n");
				inorder(root);
				break;
			case 5: printf("Enter data to delete: ");
				scanf("%d",&remove);
				result=delete(root,remove);
				break;
			case 6: exit(0);
		}
	}
	return 0;
}
