#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int data;
	struct Node* next;
}Node;

Node *head, *temp, *newNode, *tempNext;
int i;

void createQueue(int value)
{
	
	head->next = NULL;
	temp = head;
	
	temp->next =  (Node*) malloc(sizeof(Node));
	temp = temp->next;
	
	temp->data = value;
	
	temp->next = head;
	
	i++;
}

void insertFront(int value)
{
	
	temp = head->next;
	tempNext = head;
	
	newNode = (Node*) malloc(sizeof(Node));
	newNode->data = value;
	
	tempNext->next = newNode;
	newNode->next = temp;
	i++;
} 

void insertBack(int value)
{
	temp = head;
	
	//iterate until end of list
	while(temp->next != head)
	{
		temp = head->next;
	}

	//Node *newNode = makeNewNode(value);
	temp->next = newNode;
	newNode->next = head;
	
}

bool search(int key)
{
	
	for (temp = head; temp->next != head; temp = temp->next)
		if (temp->data == key)
			return true;
	
	return false;
}

void deleteNode(int key)
{
	temp = head;


	for (temp = head; temp->next != head; temp = temp->next)
	{
		if (temp->next->data == key)		//found match, delete node
		{
			tempNext = temp->next;
			temp->next = tempNext->next;
			free (tempNext);
		}
	}

}

int countNodes()
{

	
	int count = 0;
	
	for (temp = head; temp->next != head; temp = temp->next)
	{
		count++;
	}

	return count;
}

void display(Node *head)
{
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
	
	createQueue(1);
	
	printf("inerstFront 3... ");
	insertFront(3);
	display(head);
	
	/*
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
	
	*/
}

