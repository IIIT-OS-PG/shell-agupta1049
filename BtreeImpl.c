#include <stdio.h>
#include <stdlib.h>

struct KeyPointer{
    int value;
    int *ptr;
};

int order;

struct TreeNode{
    int FreeSlots;
    struct KeyPointer *entry; //array where each slot is storing key record pointer
    struct TreeNode **branch; //array of pointers where each slot is a pointer pointing towards a child node of tree.
}*root;

void InsertKey(struct TreeNode* , int );
struct TreeNode* CreateNode(int);
struct TreeNode* FindDesiredNode(struct TreeNode *);



int main()
{
    int od,data;
    while(1)
    {
        printf("Enter the value of maximum keys in a Node");
        scanf("%d",&od);
        order = od;

        root =NULL;
        printf("\n Enter data to be inserted \n");
        scanf("%d", &data);
        InsertKey(root, data);

    }
    
    return 0;
}

void InsertKey(struct TreeNode *root, int data)
{
    if(root == NULL)
    {
        root = CreateNode(data);   // Creating first node in the tree. After this creation only splitting will be required.
        return;
    }
    else
    {
        struct TreeNode *desiredNodeAdd = FindDesiredNode(root);
    }
}


struct TreeNode* CreateNode(int data)
{
    struct TreeNode* p = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    p->FreeSlots = order;
    p->entry = (struct KeyPointer *) malloc(order*sizeof(struct KeyPointer));
    p->branch = (struct TreeNode **)malloc((order+1)*sizeof(struct TreeNode *));
    int *actualData = (int *)malloc(sizeof(int));
    *actualData = data;
    (p->entry)->value = data;
    (p->entry)->ptr = actualData;
    p->FreeSlots--;
    printf("\n First Key Inserted \n");
    return p;
}

struct TreeNode* FindDesiredNode(struct TreeNode *root)
{
    int count = 0;
    
}
