#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}BST;

BST* createNode(int value) {
	BST *newnode = (BST *)malloc(sizeof(BST));
	newnode->data = value;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

BST* insertNode(BST *root, int value) {

	if(root == NULL)
		return createNode(value);

	if(root->data == value)
		return root;
	else if(root->data > value)
		root->left = insertNode(root->left, value);
	else
		root->right = insertNode(root->right, value);

	return root;
}

void inOrder(BST *root) {
	if(root) {
		inOrder(root->left);
		printf("%d\t",root->data);
		inOrder(root->right);
	}
}

void postOrder(BST *root) {
	if(root) {
		inOrder(root->left);
		inOrder(root->right);
		printf("%d\t",root->data);
	}
}

void preOrder(BST *root) {
	if(root) {
		printf("%d\t",root->data);
		inOrder(root->left);
		inOrder(root->right);
	}
}

int height(BST* node)
{
   if (node==NULL)
       return 0;
   else
   {
     /* compute the height of each subtree */
     int lheight = height(node->left);
     int rheight = height(node->right);
 
     /* use the larger one */
     if (lheight > rheight)
         return(lheight+1);
     else return(rheight+1);
   }
}

void printLevelOrder(BST* root)
{
  int h = height(root);
  int i;
  for(i=1; i<=h; i++)
    printGivenLevel(root, i);
}     
 
void printGivenLevel(BST* root, int level)
{
  if(root == NULL)
    return;
  if(level == 1)
    printf("%d\t",root->data);
  else if (level > 1)
  {
    printGivenLevel(root->left, level-1);
    printGivenLevel(root->right, level-1);
  }
}

int main(int argc, char const *argv[])
{
	BST *tree = NULL;
	tree = insertNode(tree, 12);
	tree = insertNode(tree, 10);
	tree = insertNode(tree, 20);
	tree = insertNode(tree, 9);
	tree = insertNode(tree, 11);
	printf("\nIn Order Traversal:\t");
	inOrder(tree);
	printf("\nPre Order Traversal:\t");
	preOrder(tree);
	printf("\nPost Order Traversal:\t");
	postOrder(tree);
	printf("\nLevel Order Traversal:\t");
	printLevelOrder(tree);
	printf("\n");
	return 0;
}