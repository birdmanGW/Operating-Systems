#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct bin_tree {
    int value;
    struct bin_tree *right, *left;
};

typedef struct bin_tree node;
int searchResult;

void insert(node **tree, int value)
{
    node *temp = NULL;
    if(!(*tree))                                                                //If empty tree
    {
        temp = (node *)malloc(sizeof(node));                                    //make first node
        temp->left = temp->right = NULL;                                        //assign empty children
        temp->value = value;                                                    //create value
        *tree = temp;                                                           
        return;
    }

    if(value < (*tree)->value)                                                  //if inserted value is less than parent node
    {
        insert(&(*tree)->left, value);                                          //insert left child
    }
    else if(value > (*tree)->value)                                             //if inserted value is greater than parent node
    {
        insert(&(*tree)->right, value);                                         //insert right child
    }

}

void print(node *tree)
{
    if (tree)
    {
        printf("%d \t",tree->value);
        print(tree->left);
        print(tree->right);
    }
    

}


void deleteNode(node **tree, int value)
{
    node *del,*sub;

    //Find the place where node should be 
    for ( ; del = *tree; tree = (value < del->value) ? &del->left : &del->right ) 
        if (del->value == value) break;
        
    //not found: nothing to do 
    if ( !*tree) return;

    /* When we get here, `*tree` points to the pointer that points to the node_to_be_deleted
    ** If any of its subtrees is NULL, the other will become the new root
    ** ,replacing the deleted node..
    */
    if ( !del->left) { *tree = del->right; free(del); return; }
    if ( !del->right) { *tree = del->left; free(del); return; }

    /* Both subtrees non-empty:
    ** Pick one (the left) subchain , save it, and set it to NULL */
    sub = del->left;
    del->left = NULL;

    //Find leftmost subtree of right subtree of 'tree' 
    for (tree =  &del->right; *tree; tree =  &(*tree)->left) {;}
    
    //and put the remainder there 
    *tree = sub;
    free (del);
}

bool search(node **tree, int value)
{
    if(!(*tree))
    {
        return 0;
    }

    if(value < (*tree)->value)                                                  //if value less than parent value
    {
        search(&((*tree)->left), value);                                        //search through left child
    }
    else if(value > (*tree)->value)                                             //if value greater than parent value
    {
        search(&((*tree)->right), value);                                       //search through right child
    }
    else if(value == (*tree)->value)                                            //else if value found
    {
        printf("Found search node. \n");
        searchResult = 1;
        return 1;
    }
    
    if (searchResult != 1)
        printf("Did not find search node. \n");

    return 0;
}

void main()
{
    node *root;
    int tmp;
    //int i;

    root = NULL;
    /* Inserting nodes into tree */
    printf("Insert 0... \n");
    insert(&root, 0);
    print(root);
    
    printf("Insert 2... \n");
    insert(&root, 2);
    print(root);
    
    printf("Insert 1... \n");
    insert(&root, 1);
    print(root);
    
    printf("Insert 6... \n");
    insert(&root, 6);
    print(root);

    printf("Insert 7... \n");
    insert(&root, 7);
    print(root);

    printf("Insert 3... \n");
    insert(&root, 3);
    print(root);

    printf("Insert 4... \n");
    insert(&root, 4);
    print(root);
    
    printf("Insert 5... \n");
    insert(&root, 5);
    print(root);


    /* Search node into tree */
    printf("Searching for 2...\n");
    search(&root, 2);

    /* Deleting all nodes of tree */
    printf("Deleting 2... \n");
    deleteNode(&root, 2);
    print(root);
    
    searchResult = 0;
    
    /* Search node into tree */
    printf("Searching for 2...\n");
    search(&root, 2);
    
    
}