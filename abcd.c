#include <stdio.h>
#include <stdlib.h>

struct KeyPointer{
    int value;
    int *ptr;
}kp;
int order;
struct TreeNode{
    int FreeSlots;
    struct KeyPointer *entry; //array where each slot is storing key record pointer
    struct TreeNode **branch; //array of pointers where each slot is a pointer pointing towards a child node of tree.
}*root;

void InsertKey(int );
struct TreeNode* CreateNode(int);
struct TreeNode* FindDesiredNode(int);

int main()
{
    int od,data;
    root =NULL;
    printf("Enter the value of maximum keys in a Node");
    scanf("%d",&od);
    order = od;
    while(od--)
    {
        printf("\n Enter data to be inserted \n");
        scanf("%d", &data);
        InsertKey(data);
    }
    for(int i=0;i<order;i++){
        printf("Data %d is %d and data at addresses is  \n", i, ((root->entry)+i)->value/*, *(((root->entry)+i)->ptr)*/);
    }
    return 0;
}

void InsertKey(int data)
{
    if(root == NULL)
    {
        root = CreateNode(data); // Creating first node in the tree. After this creation only splitting will be required.
        printf("\n Root Freeslots are : %d value inserted is %d and poinnter is %p\n",root->FreeSlots, root->entry->value, root->entry->ptr);
        return;
    }
    else
    {
        if(root->FreeSlots)
        {
            InsertIntoRoot(data);
            printf("\n Root Freeslots are : %d\n",root->FreeSlots);
        }
        else
            FindDesiredNode(data);
    }
}


struct TreeNode* CreateNode(int data)
{
    struct TreeNode* p = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    p->FreeSlots = order;
    p->entry = (struct KeyPointer *) malloc(order*sizeof(struct KeyPointer));
    p->branch = (struct TreeNode **)malloc((order+1)*sizeof(struct TreeNode *));
    int *actualDataPtr = (int *)malloc(sizeof(int));
    *actualDataPtr = data;
    (p->entry)->value = data;
    (p->entry)->ptr = actualDataPtr;
    p->FreeSlots--;
    return p;
}

void InsertIntoRoot(int data)
{
    int occupied = order-(root->FreeSlots);
    int  i = occupied-1, shifts =0;
    while(i>=0)
    {
        int comp = ((root->entry)+i)->value;
        if(comp>data)
        {
            printf("\n i IS : %d \n", data, i);
            (((root->entry)+i)+1)->value =((root->entry)+i)->value;
            (((root->entry)+i)+1)->ptr = ((root->entry)+i)->ptr;
            shifts++;
        }
        i--;
    }
    int *actualDataPtr = (int *)malloc(sizeof(int));
    *actualDataPtr = data;
    ((root->entry)+i+2)->value = data;
    ((root->entry)+i+2)->ptr = actualDataPtr;
    printf("\n Data INSERTED %d is %d ", i, ((root->entry)+i+1)->value/*, *(((root->entry)+i)->ptr)*/);
    root->FreeSlots--;
}

struct TreeNode* FindDesiredNode(int data)
{
    /*int count = 0,i=0;
    while(data<(((root->entry)+i)->value))
    {
        ((root->entry)+i+1);
    }*/

    printf("\n No More Slots : %d \n", root->FreeSlots);
}


    