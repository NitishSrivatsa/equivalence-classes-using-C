


/*
ONLINE EQUIVALENCE CLASSES USING BINARY TREES
BY:
NITISH S (PES2201800368)
SANDEEP BHAT (PES2201800632)
CLASS: 3rd SEM ,'A"
*/






#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
int parent[MAX_SIZE];

typedef struct Node
{
    int key;
    struct Node *left, *right;
}Node;


Node *newNode(int key)
{
    Node *temp = malloc(sizeof(Node));
    temp->key  = key;
    temp->left  = temp->right = NULL;
    return (temp);
}


void createNode(int parent[], int i, Node *created[], Node **root)
{

    if (created[i] != NULL)
        return;

    created[i] = newNode(i);

    if (parent[i] == -1)
    {
        *root = created[i];
        return;
    }

    if (created[parent[i]] == NULL)
        createNode(parent, parent[i], created, root);

    Node *p = created[parent[i]];

    if (p->left == NULL)
        {
		
		p->left = created[i];

	}
    else 
        {

		p->right = created[i];

	}

}

Node *createTree(int parent[], int n)
{
    
    Node *created[n];
    for (int i=0; i<n; i++)
        created[i] = NULL;

    Node *root = NULL;
    for (int i=0; i<n; i++)
        createNode(parent, i, created, &root);

    return root;
}


void inorder(Node *root)
{

    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ",root->key);
        inorder(root->right);
    }

}

int find(int i)
{
	while(parent[i]!=-1)
	{
		i=parent[i];
		find(i);

   	}
   	return i;
}

int create_parent_array(int n)
{
	printf("Enter the elements for the parent array:\n");
	for (int i=0;i<n;i++)
        {
		scanf("%d",&parent[i]);
	}

}

int unioni(int i,int j,int n)
{
    	parent[j]=i;
	Node *root1=createTree(parent,n);
	inorder(root1);
}

void initialize()
{
	for (int i=0;i<sizeof(parent);i++)
		parent[i]=-2;
}

int compact_find(int i)
{
	int j=i;
	while (parent[i]!=-1)
	{
		i=parent[i];
		find(i);
	}
	int f=j;
	while (f!=i)
	{
		int pf=parent[f];
		parent[f]=i;
		f=pf;
	}
	return i;
}

void main()
{
	int num,find_ele;
	initialize();
	printf("\nEnter the number of elements:");
    	scanf("%d",&num);
    	create_parent_array(num);
	Node *root = createTree(parent, num);
    	printf("The inorder traversal for the created tree:\n");
	inorder(root);
   	printf("\n");
	int choice,no1,no2,flag=0;
	for (;;)
	{
	printf("Press 1 for find operation,2 for union operation and 3 for path compaction:");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			printf("Enter element to be found:\n");
			scanf("%d",&find_ele);
			for(int i=0;i<num;i++)
    			{
        			if(i==find_ele)
            				flag=1;
   			}
   			if(flag==1)
        			printf("The element %d belongs to the class with node element %d\n",find_ele,find(find_ele));
    			else
        			printf("Element not in the class\n");

			break;
		case 2: 
			//num++;
			printf("Enter new element to be added:");
			scanf("%d",&no1);
			printf("Enter parent for the new element:");
			scanf("%d",&no2);
			num=1+no1;
			unioni(no2,no1,num);
			break;
		case 3:
			printf("Enter element to be found:");
			scanf("%d",&find_ele);
			for(int i=0;i<num;i++)
    			{
        			if(i==find_ele)
            				flag=1;
   			}
   			if(flag==1)
        			printf("The element %d belongs to the class with node element %d\n",find_ele,compact_find(find_ele));
    			else
        			printf("Element not in the class\n");
			for (int j=0;j<num;j++)
				printf("%d ",parent[j]);
			printf("\n");

			break;
			
		default:
			exit(0);
	}
}
	
	
}
