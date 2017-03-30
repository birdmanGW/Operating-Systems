#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>

/* these may be any values >= 0 */ 
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* the available amount of each resource */ 
int available[NUMBER_OF_RESOURCES];

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the amount currently allocated to each customer */ 
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* Return 0 if successful | -1 if unsucessful */
void request_resources(int customer_num, int request[]);

/* Return 0 if successful | -1 if unsucessful */
void release_resources(int customer_num, int request[]);

int work[NUMBER_OF_RESOURCES];

int finish[NUMBER_OF_CUSTOMERS];

int complete[NUMBER_OF_CUSTOMERS];

/* Computes BankerAlgorithm for a certain request array */
void bankers_algorithm();

//Loops 20 times per thread, requesting, then release data
void *Thread(void *data);

int release[NUMBER_OF_RESOURCES];

int request[NUMBER_OF_RESOURCES];

int i, j;
bool safe = false;
pthread_mutex_t mutex;


typedef struct{
    int id;
}threadData;


int main(int argc, char *argv[]) 
{
    int z;
    
    //create mutex
    pthread_mutex_init(&mutex, NULL);

    printf("AVAILABLE RESOURCE: \n [");
    //Populate Available Resource Array
    for (i = 1; i <= argc-1; i++)
    {
        available[i-1] = atoi(argv[i]);
        printf("%d ", available[i-1]);
    }
    printf("] \n\n");
    
    printf("MAXIMUM RESOURCES: \n");
    //Populate Maximum Demand for each Resource
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) 
    {
        printf("%d:[",i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            maximum[i][j] = available[j] ? (rand() % available[j]) : 0;
            printf("%d ", maximum[i][j]);
        }
        printf("] \n");
    }
    
    printf("\n");
    
    printf("ALLOCATED RESOURCES: \n");
    //Populate Currently Allocated Reasource for each customer
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) 
    {
        printf("%d:[",i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            allocation[i][j] = 0;
            printf("%d ",allocation[i][j]);
        }
        printf("] \n");
    }
    
    printf("\n");
    
    printf("NEED: \n");
    //Populate Need for each customer
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) 
    {
        printf("%d:[",i);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("] \n");
    }
    
    printf("\n");
    
    
    pthread_t *threadIDs;
     
    threadIDs = malloc(sizeof(pthread_t) * NUMBER_OF_CUSTOMERS);

    
    //Create a thread for each Customer
    for (z = 0; z < NUMBER_OF_CUSTOMERS; z++) 
    {
        threadData *data = malloc(sizeof(threadData));
        data->id = z;
        
        pthread_create(&threadIDs[z], NULL, Thread, data);
        //printf("CUSTOMER %d created \n", z);
    }
    
    for (z = 0; z < NUMBER_OF_CUSTOMERS; z++)
    {
        pthread_join(threadIDs[z], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
     
}

void *Thread(void *data)
{
    
    int y;
    
    //Dereference data pointer
    threadData myData = *((threadData *) data);
    
    //pthread_mutex_lock(&mutex);
    
    //Loop 20 random requests
    for (y = 0; y < 20; y++)
    {

        //Acquire mutex
        pthread_mutex_lock(&mutex);
        
        printf("\t Thread: %d | Count: %d About to request...\n", myData.id, y);
        
        //request resource, check if safe
        request_resources(myData.id, request);
        
        //Release mutex
        pthread_mutex_unlock(&mutex);
        
        //Wait
        sleep(1);
        
        //Acquire mutex
        pthread_mutex_lock(&mutex);
        
        printf("\t Thread: %d | Count: %d About to release...\n", myData.id, y);
        
        //Release random resources
        release_resources(myData.id, release);
        
        //Release mutex
        pthread_mutex_unlock(&mutex);
    }
    
    //pthread_mutex_unlock(&mutex);
    
}

//Returns 0 | UNSAFE otherwise 1 | SAFE
void request_resources(int customer_num, int request[])
{
    
    
    //Set Current Request array
    printf("P%d is requesting: [", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
        request[j] = need[customer_num][j] ? (rand() % need[customer_num][j]) : 0;
        printf("%d ", request[j]);
    }
    printf("] \n");
    
    //Check base safety cases
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
        if (request[j] > need[customer_num][j] || request[j] > available[j])
        {
            printf("Request for P%d UNSAFE, request not granted.\n\n", customer_num);
            return;
        }
    }
    
    //Assume all is good, update resource-availability matrices
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
        available[j] = available[j] - request[j];
        allocation[customer_num][j] = allocation[customer_num][j] + request[j];
        need[customer_num][j] = need[customer_num][j] - request[j];
    }
    
    //perofrm Bankers simulation
    bankers_algorithm();
    
    //If UNSAFE: Revert made changes to resource availability arrays
    if (safe == false)
    {
        available[j] = available[j] + request[j];
        allocation[customer_num][j] = allocation[customer_num][j] - request[j];
        need[customer_num][j] = need[customer_num][j] + request[j];
        printf("Request for P%d UNSAFE, request not granted.\n\n", customer_num);
        return;
    }
    //Else SAFE, return 1
    else 
    {
        printf("Updated for P%d => Allocation: [", customer_num);
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ",allocation[customer_num][j]);
        printf("], Max: [");
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ",maximum[customer_num][j]);
        printf("], Need: [");
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ",need[customer_num][j]);
        printf("],\n Available: [");
        for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ",available[j]);
        printf("]\n\n");
        
        return;
    }
        
}

void release_resources(int customer_num, int release[])
{
    
    //Now fill release array
    for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
        release[j] = allocation[customer_num][j] ? (rand() % allocation[customer_num][j]) : 0;
    }
    
    printf("P%d is releasing: [", customer_num);
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        printf("%d ",release[j]);
    printf("] \n Updated for P%d: Allocation: [",customer_num);
    
    //Update resource-allocation arrays
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
        need[customer_num][j]  = need[customer_num][j] +  release[j];
        allocation[customer_num][j] = allocation[customer_num][j] - release[j];
        available[j] = available[j] + release[j];
    }
    
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        printf("%d ",allocation[customer_num][j]);
    printf("], Max: [");
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        printf("%d ",maximum[customer_num][j]);
    printf("], Need: [");
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        printf("%d ",need[customer_num][j]);
    printf("],\n Available: [");
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        printf("%d ",available[j]);
    printf("]\n\n");
    
}

void bankers_algorithm()
{
    safe = false;
    int count1 = 0, count2 = 0, k = 0, u = 0;
    
    //work = available;
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
        work[j] = available[j];   
        
    //Set finish array to all 0's
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        finish[i] = 0;
        
    while (count1 != NUMBER_OF_CUSTOMERS)
    {
        count2 = count1;
        
        for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            for (j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                if (need[i][j] <= work[j])
                    k++;
            }
            if (k == NUMBER_OF_RESOURCES && finish[i] == 0)
            {
                finish[i] = 1;
                complete[u++] = i;
                for (j = 0; j < NUMBER_OF_RESOURCES; j++)
                    work[j] = work[j] + allocation[i][j];
                
            }
            count1++;
            k = 0;
        }
    }
    
    if (count1 == count2)
    {
        printf("\t\t DEADLOCK exitiing...\n");
        return;
    }
    
    printf("Request is granted. System is safe with sequence: [");
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        printf("%d ", complete[i]);
    printf("]\n");
    

    //Else, simulation sucessful, all finish[i] safe
    //return with safe = true;
    safe = true;
    return;
}