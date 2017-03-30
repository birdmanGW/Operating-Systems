#include <stdlib.h>
#include <stdio.h>


/*
 *  Creates a PriorityQueue as a linked list of nodes with ->next pointing to next priorty node in Descending order
 */

typedef struct Node
{
    int id;
    int priority;
    struct Node *next;
}Node;

Node *head, *temp, *temp2, *newNode;
int saveId, savePriority;

void Insert(int id, int priority)
{
    newNode = (Node*) malloc(sizeof(Node));
    newNode->id = id;
    newNode->priority = priority;
    
    //If empty queue or, node to be inserted has higher priority than head
    if (head == NULL || priority > head->priority)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        temp = head;                                                                                    //save head
        
        //transverse queue until finds node with lower priority than the one being inserted
        while (temp->next != NULL && temp->next->priority >= priority)
            temp = temp->next;
            
        newNode->next = temp->next;                                                                     //set newNode next to next node after closest priority level
        temp->next = newNode;                                                                           //set newNode
    }
    
}

void display()
{
    temp = head;
    
    if (head == NULL)
        printf("QUEUE IS EMPTY. \n");
    else
    {
        printf("QUEUE IS: \n");
        
        while (temp->next != NULL)
        {
            printf("\t [id: %d, priority: %d] \n", temp->id, temp->priority);
            temp = temp->next;
        }
    }
    
}

void extractMax()
{
    //head is always saved as the highest priority node, so return head:)
    printf("Highest Priority Node: [%d, %d] \n",head->id, head->priority);
}

void deleteNode(int priority)
{
	if (head == NULL | priority == NULL)
		return;

	//transverse list
	for (temp = head; temp != NULL; temp = temp->next)
	{
		//Found node to delete
		if (temp->priority == priority)
		{
			//If at tail of list
			if (temp->next == NULL)
			{
				free (temp);
				return;
			}
	        
			//swap priority values with temp
			temp->priority = temp->next->priority;
			temp->id = temp->next->id;
			//set temp2 to next's next node in list
			temp2 = temp->next->next;
			//free temp next
			free(temp->next);
			//set next node to node in front of temp2
			temp->next = temp2;
		}
	}

}

//Increments node with priority by a
void Increase(int priority, int a)
{
    //save head
    temp = head;
    
    //Iterate through queue until we find the node to append
    while (temp->priority != priority)
        temp = temp->next;
    
    //change temp priority by affected a
    temp->priority = priority + a;

    //save temp info
    saveId = temp->id;
    savePriority = temp->priority;
    
    //delete old priority pre addition
    deleteNode(priority + a);
    
    //insert new node post addition
    Insert(saveId, savePriority);
}

//Decrements node with priority by b
void Decrease(int priority, int b)
{
    //save head
    temp = head;
    
    //Iterate through queue until we find the node to append
    while (temp->priority != priority)
        temp = temp->next;
    
    //change priority by affected value
    temp->priority = priority - b;
    
    //save temp values
    saveId = temp->id;
    savePriority = temp->priority;

    //delete old priorty node before subtraction
    deleteNode(priority - b);
    
    //insert newly subtracted priority node back into queue
    Insert(saveId, savePriority);
}


int main()
{
    Insert(3, 20);
    Insert(5, 18);
    Insert(2, 20);
    Insert(7, 16);
    Insert(6, 18);
    Insert(10, 8);
    Insert(9, 10);
    Insert(4, 16);
    Insert(12, 4);
    Insert(8, 10);
    Insert(11, 6);
    Insert(13, 2);
    Insert(1, 100);
    display();
    
    extractMax();
    
    printf("Adding 100 to priority 4... \n");
    Increase(4, 100);
    display();
    
    extractMax();
    
    printf("Subtracting 5 from priority 104... \n");
    Decrease(104, 5);
    display();
    
    extractMax();
    
}

