#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
  char data[40];
  struct node* prev;
  struct node* next;
} node;

typedef struct {
  node* head;
} linkedList;

linkedList* createList()
{
  linkedList* list = malloc(sizeof(linkedList));
  list->head = NULL;
  return list;
}

void insertNode(linkedList* list, node* newNode, int index)
{
  node* prev = NULL;
  node* current = list->head;

  if (index == 0) {
    if (current != NULL) {
      current->prev = newNode;
    }
    newNode->next = current;
    list->head = newNode;
    return;
  }

  for (int i = 0; i < index; i++) {
    prev = current;
    current = current->next;
  }

  prev->next = newNode;
  newNode->next = current;
  newNode->prev = prev;
  if (current != NULL) {
    current->prev = newNode;
  }
}

void appendNode(linkedList* list, node* newNode)
{
  node* prev = NULL;
  node* current = list->head;
  int i = 0;

  while (current != NULL) {
    current = current->next;
    i++;
  }

  insertNode(list, newNode, i);
}

node* createNode(char* data)
{
  node* newNode = malloc(sizeof(node));
  strcpy(newNode->data, data);
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void display(linkedList* list)
{
  node* current = list->head;
  while(current != NULL) {
    printf("Node with data: %s at %p.\n", current->data, &(*current));
    current = current->next;
  }
}

void displayReverse(linkedList* list)
{
  node* current = list->head;
  while(current->next != NULL) {
    current = current->next;
  }

  while(current != NULL) {
    printf("Node with data: %s at %p.\n", current->data, &(*current));
    current = current->prev;
  }
}

int main()
{
  linkedList* list = createList();

  char input[100];
  char data[40];
  while (1) {
    int position = -1;
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%s %d\n", data, &position);

    if (strcmp("done", data) == 0) {
      break;
    }

    if (position == -1) {
      appendNode(list, createNode(data));
    } else {
      insertNode(list, createNode(data), position);
    }
  }

  display(list);
  printf("\n\n");
  displayReverse(list);
}
