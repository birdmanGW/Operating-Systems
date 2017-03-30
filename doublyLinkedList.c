#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
	struct Node* prev;
}Node;

struct Node *head, *temp;

Node *makeNewNode(int value)
{
	newNode = (Node*) malloc(sizeof(struct Node)); 				// Creates space for node in heap

	newNode->data = value;										//set data
	newNode->next = NULL;										//set next NULL
	newNODE->PREV = NULL;										//set prev NULL
	return newNode;
}

void insertFront(int value)
{
	Node *newNode = makeNewNode(value);							//make newNode

	if (head == NULL)											//If empty list
	{
		head = newNode;
		return;
	}

	head->prev = newNode;										//else set prev node
	newNode->next = head;										//set next node
	head = newNode;												//assigne newnode to head
}

void insertBack(int value)
{
	Node *temp = head;
	Node *newNode = makeNewNode(value);

	if (head == NULL)											//if empty list
	{
		head = newNode;
		return;
	}

	//transverse list
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newNode;										//set next
	newNode->prev = temp;										//set prev
}

bool search(int key)
{
	//transverse list
	for (temp = head; temp != NULL; temp = temp->next)
		if (temp->data == key)
			return true;
	
	return false;
}

void deleteNode(int key)
{
	if (head == NULL | key == NULL)
		return;

	Node *temp;
	
	//Visit each node
	for (temp = head; temp != NULL; temp = temp->next)
	{	
		//Node found
		if (temp->data == key)
		{
			//If node is head
			if (temp->prev == NULL)
			{
				head = temp->next;
			}
			//If node is last
			else if (temp->next == NULL)
			{
				temp->prev->next == NULL;
			}
			//If node is in middle
			else
			{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			free(temp);
		}
	}
}

int countNodes()
{
	int count = 0;

	//transverse list
	for (temp = head; temp != NULL; temp = temp->next)
	{
		count++;														//append count
	}

	return count;
}

void display(Node *head)
{
	//transverse list
	while (head != NULL)
	{
		printf("\t %d", head->data);
		head = head->next;
	}
	printf("\n");
}

int main()
{

	head = NULL;

	printf("inerstFront 3... ");
	insertFront(3);
	display(head);
	
	printf("insertBack 6... ");
	insertBack(6);
	display(head);
	
	printf("inerstFront 10... ");
	insertFront(10);
	display(head);
	
	printf("insertBack 20... ");
	insertBack(20);
	display(head);

	printf("Before deletion... \n");
	display(head);
	deleteNode(10);
	
	printf("After deletion.... \n");
	display(head);
	
	printf("Searching for 3... %d \n", search(3));
	
	printf("Searching for 10... %d \n", search(10));
	
	printf("Total Node count... %d \n", countNodes());
	
} 
