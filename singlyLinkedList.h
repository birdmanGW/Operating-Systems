#ifndef singlyLinkedList_H_
#define singlyLinkedList_H_

typedef struct Node
{
	int data;
	char *arg;
	struct Node *next;
}Node;

Node makeNewNode(int value, char *arg);

void insertFront(int value, char *arg);

void deleteNode(int);

int countNodes();

void display(Node *head);

#endif

