#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../linked-list/linked-list.h"

typedef struct node {
  int data;
  struct node* left;
  struct node* right;
} node;

node* createNode(int data)
{
  node* newNode = (node*) malloc(sizeof(node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

node* insert(node* targetNode, int data)
{
  if (targetNode == NULL) {
    return createNode(data);
  }

  if (data >= targetNode->data) {
    targetNode->right = insert(targetNode->right, data);
  } else {
    targetNode->left = insert(targetNode->left, data);
  }

  return targetNode;
}

bool lookup(node* node, int value)
{
  if (node == NULL) {
    return false;
  }

  if (node->data == value) {
    return true;
  }

  if (node->data < value) {
    return lookup(node->right, value);
  } else {
    return lookup(node->left, value);
  }
}

void display(node* root)
{
  if (root == NULL) {
    return;
  }

  display(root->left);
  printf("%d\n", root->data);
  display(root->right);
}

int size(node* node)
{
  if (node == NULL) {
    return 0;
  }

  return size(node->left) + size(node->right) + 1;
}

int maxDepth(node* node)
{
  if (node == NULL) {
    return 0;
  }

  int leftDepth = maxDepth(node->left);
  int rightDepth = maxDepth(node->right);

  if (leftDepth > rightDepth)
    return leftDepth + 1;
  else
    return rightDepth + 1;
}

int minValue(node* node)
{
  if (node->left == NULL) {
    return node->data;
  }

  return minValue(node->left);
}

int minValueNonRecursive(node* theNode)
{
  node* current = theNode;
  int minValue;
  do {
    minValue = current->data;
    current = current->left;
  } while (current != NULL);

  return minValue;
}

void displayIncreasing(node* theNode)
{
  if (theNode->left != NULL)
    displayIncreasing(theNode->left);

  printf("%d\n", theNode->data);

  if (theNode->right != NULL)
    displayIncreasing(theNode->right);
}

void displayPostOrder(node* theNode)
{
  if (theNode->left != NULL)
    displayPostOrder(theNode->left);

  if (theNode->right != NULL)
    displayPostOrder(theNode->right);

  printf("%d\n", theNode->data);
}

void tallyLeaves(node* theNode, int* numLeaves)
{
  if (theNode == NULL)
    return;

  if (theNode->left == NULL && theNode->right == NULL) {
    (*numLeaves)++;
    return;
  }

  tallyLeaves(theNode->left, numLeaves);
  tallyLeaves(theNode->right, numLeaves);
}

int numLeaves(node* theNode)
{
  int numLeaves = 0;
  tallyLeaves(theNode, &numLeaves);
  return numLeaves;
}

bool hasTargetSum(node* theNode, int target, int currentSum)
{
  if (theNode->left == NULL && theNode->right == NULL)
    return (bool) ((currentSum + theNode->data) == target);

  bool leftSum = false;
  bool rightSum = false;
  if (theNode->left != NULL)
    leftSum = (bool) hasTargetSum(theNode->left, target, currentSum + theNode->data);
  if (theNode->right != NULL)
    rightSum = (bool) hasTargetSum(theNode->right, target, currentSum + theNode->data);

  return leftSum || rightSum;
}

bool hasPathSum(node* theNode, int target)
{
  return hasTargetSum(theNode, target, 0);
}

void findSums(node* theNode, linkedListNode** list, int currentSum)
{
  if (theNode->left == NULL && theNode->right == NULL) {
    char str[5];
    sprintf(str, "%d", currentSum + theNode->data);
    appendLinkedListNode(list, createLinkedListNode(str));
  }

  if (theNode->left != NULL)
    findSums(theNode->left, list, currentSum + theNode->data);
  if (theNode->right != NULL)
    findSums(theNode->right, list, currentSum + theNode->data);
}

void getSums(node* theNode)
{
  int count = 0;
  linkedListNode* list = NULL;
  findSums(theNode, &list, 0);
  displayLinkedList(list);
}

int main()
{
  node* myTree = createNode(2);
  insert(myTree, 4);
  insert(myTree, 9);
  insert(myTree, 6);
  insert(myTree, 3);
  insert(myTree, 0);
  insert(myTree, 1);
  insert(myTree, 10);
  insert(myTree, -2);
  display(myTree);
  if(lookup(myTree, -2)) {
    printf("yay\n");
  } else {
    printf("no dice!\n");
  }
  printf("Num nodes: %d.\n", size(myTree));
  printf("Max depth: %d.\n", maxDepth(myTree));
  printf("Min value: %d.\n", minValue(myTree));
  printf("Min value: %d.\n", minValueNonRecursive(myTree));
  printf("Increasing:\n");
  displayIncreasing(myTree);
  printf("Post order:\n");
  displayPostOrder(myTree);
  printf("Num leaves: %d\n", numLeaves(myTree));
  printf("Has sum 25?: %s\n", hasPathSum(myTree, 25) ? "Yup" : "Nope");
  getSums(myTree);
}
