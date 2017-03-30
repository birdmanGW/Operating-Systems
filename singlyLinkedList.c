#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "singlyLinkedList.h"

#define MAX_SIZE 10

typedef struct Node
{
	int data;
	char *arg;
	struct Node *next;
}Node;

Node *head, *temp, *newNode;

Node *makeNewNode(int value, char *arg)
{
	newNode = (Node*) malloc(sizeof(struct Node)); 				// Creates space for node in heap

	newNode->data = value;	
	newNode->arg = arg;      //set data
	newNode->next = NULL;										//set next NULL
	return newNode;
}

void insertFront(int value, char *arg)
{
	
	if ( count() >= 10 )
		deleteNode();
	
	
	newNode = makeNewNode(value, arg);							//make new node

	if (head == NULL)										//if empty list
	{
		head = newNode;										//insert head
		head->next = NULL;
		return;
	}
	
		newNode->next = head;								//else set newNode before head
		head = newNode;

}

void insertBack(int value)
{
	Node *temp1, *temp2;

	temp1 = makeNewNode(value);

	//Save Head
	temp2 = head;

	if (head == NULL)
	{
		//Empty List, new node
		head = temp1;
		head->next = NULL;
		return;
	}
	
	//Transverse end of list
	while (temp2->next != NULL)
		temp2 = temp2->next;

	//Append to end of list
	temp1->next = NULL;
	temp2->next = temp1;

}

bool search(int key)
{
	//transverse list
	for (temp = head; temp != NULL; temp = temp->next)
		if (temp->data == key)																//found key
			return true;
	
	return false;
}

void deleteNode()
{
	temp = head;
	
	while (temp->next != NULL)
		temp = temp-> next
		
	free(temp);

}

int countNodes()
{

	int count = 0;
	
	//transverse list
	for (temp = head; temp != NULL; temp = temp->next)
	{
		count++;			//append count
	}

	return count;
}

void display(Node *head)
{
	//transverse list
	while (head != NULL)
	{
		printf("\t %d", head->data);		//this part is obvious
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
