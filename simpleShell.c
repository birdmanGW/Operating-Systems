#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE 80 /* The maximum length command */
#define MAX_HISTORY 1000  /* Maximum history length (Will loop around and reset counter if over ) */

void parseCmd(char* cmd, char** args);          
int execMostRecHist(char* hist[], int current);
int ampersand = 0;          //Hold value if ampersand is present

int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    char cmd[MAX_LINE/2 + 1];  /* command line input */
    char *hist[MAX_HISTORY];   /* history array */
    //char *newArray[1];
    int i, num, current = 0;
    
    //Initiate history array
    for (i = 0; i < MAX_HISTORY; i++)
        hist[i] = NULL;
    
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) 
    {
        printf("osh>");
        fflush(stdout);
        ampersand = 0;
        
        // Read command from standard input, exit on Ctrl+D
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break;

        // Remove trailing newline character, if any
        if(cmd[strlen(cmd)-1] == '\n') 
            cmd[strlen(cmd)-1] = '\0';
        
        //Removes current history value in array, to free space to add next new value
        free(hist[current]);
       
        //Set current new value in history to stdin from cmd 
        hist[current] = strdup(cmd);
        
        //Append cuurent, but always by modulo max history size (to loop)
        current = (current + 1) % MAX_HISTORY;
        
        //keeps track of !nth number
        int num;
        
        //If history detected, execute history function to print
        if (strcmp(cmd, "history") == 0)  
        {                                      
            if (hist[0] != NULL)
                //Display history (numbered)
                history(hist, current);

            //else empty history array
            else
                printf("Empty history. \n");
        }

        //else if !! detected, execute most recent command
        else if (strcmp(cmd, "!!") == 0) 
        {
            printf("here bc im an idiot \n");
            if (hist[current-2] != NULL || hist[current] != NULL) {
                //printf("here bc im an idiot \n");
                execMostRecHist(hist, current-2);
            }

            //Error statement *no recent history detetced*
            else
                printf("No recent history command to execute. \n");
        }

        //else if !n detected, execute nth command in history
        else if (sscanf(cmd, "!%d", &num) == 1) 
        {
            if (hist[num] != NULL)
                execMostRecHist(hist, num-1);

            //Error statement *no !nth command detected*
            else
                printf("No history command !%d found. \n", num);
        }

        //Else no special commands detetced, assume regular unix command
        else    
        {
            //Parse through the stdin cmd array, delimiteing whitespace and store in args
            parseCmd(cmd, args);
            
            // Exit?
            if(strcmp(args[0], "exit") == 0) break;
    
            // Execute command
            if(executeCmd(args) == 0) break;
        }
    }
    /**
    * After reading user input, the steps are:
    * (1) fork a child process using fork()
    * (2) the child process will invoke execvp()
    * (3) if command included &, parent will invoke wait()
    */
    return 0;
}

//Function to print out every value in the stored history array
int history(char *hist[], int current)
{
    int i = current;
    int hist_num = 1;
    
    //Do *this* while i !=current history value
    do 
    {
        //if hist[i] exists
        if (hist[i])
        {
            //print that hist value, along with corresponding hist number(placement in hist array)
            printf("%4d %s\n", hist_num, hist[i]);
            hist_num++;
        }

        //Append i, but always by modulo history size (Like appending current)
        i = (i + 1) % MAX_HISTORY;
    } while (i != current);
    
    return 0;
}

//Method that will parse std cmd array, delimiting whitespace and storing in args array
void parseCmd(char* cmd, char** args)
{       
    int i;
    
    //iterate through cmd up to its max length
    for(i = 0; i < MAX_LINE; i++) {

        //set equal to args[i] everything before the delimeter " " in cmd
        args[i] = strsep(&cmd, " "); 
        
        //if NULL found, break!
        if(args[i] == NULL) break;

    }
}

//FUnction that seperatly calls fork to execute all recent history values and specified !n values
int execMostRecHist(char* hist[], int num)
{

    //temp array to send to execvp()
    char *newArray[2];
    newArray[0] = hist[num];
    newArray[1] = NULL;

    //Check for ampersand, if found, change the value of ampersand to 1
    if (strchr(newArray[0], '&') != NULL) {
        ampersand = 1;
        newArray[0][strlen(newArray[0])-1] = 0;
    }

    //fork here
    pid_t pid = fork();
    
    //If error found, call to erno
    if (pid < 0) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }
    
    //else if child found, execute child in execvp
    else if (pid == 0) {
        // Execute command

        execvp(newArray[0], newArray);  

        // Error occurred
        char* error = strerror(errno);
        printf("shell: %s: %s\n", newArray[0], error);
        return 0;
    }

    // else if Parent process, check for ampersand and either wait, or dont
    else {
        // Wait for child process to finish
        int childStatus;

        if (ampersand == 0)
            waitpid(pid, &childStatus, 0);

        return 1;
    }
    
}

//method to execute normal non special history unix commands
int executeCmd(char** args)
{
    // Fork process
    pid_t pid = fork();

    //Check for ampersand, if found, change the value of ampersand to 1
    if (strchr(args[0], '&') != NULL) {
        ampersand = 1;
        args[0][strlen(args[0])-1] = 0;
    }

    // Error
    if (pid < 0) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }

    // Child process
    else if (pid == 0) {

        // Execute command
        execvp(args[0], args);  

        // Error occurred
        char* error = strerror(errno);
        printf("shell: %s: %s\n", args[0], error);
        return 0;
    }

    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
        
        if (ampersand == 0)
            waitpid(pid, &childStatus, 0);

        return 1;
    }
}
