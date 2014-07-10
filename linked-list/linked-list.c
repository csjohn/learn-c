#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  char data[40];
  struct node *next;
} node;

node* createNode(char *data)
{
  node *newNode = malloc(sizeof(node));
  strcpy(newNode->data, data);
  newNode->next = NULL;
  return newNode;
}

void deleteNode(node** head, int index)
{
  node* prev = NULL;
  node* current = *head;

  for (int i = 0; i < index; i++) {
    prev = current;
    current = current->next;
  }

  if (index == 0) {
    *head = current->next;
  } else {
    prev->next = current->next;
  }

  free(current);
}

void insertNode(node** head, node* newNode, int index)
{
  node* prev = NULL;
  node* current = *head;

  for (int i = 0; i < index; i++) {
    prev = current;
    current = current->next;
  }

  if (index == 0) {
    *head = newNode;
  } else {
    prev->next = newNode;
  }
  newNode->next = current;
}

void appendNode(node** head, node* newNode)
{
  node* current = *head;

  // Empty list
  if (current == NULL) {
    return insertNode(head, newNode, 0);
  }

  // Non-empty list
  int i = 1;
  while (current->next != NULL) {
    current = current->next;
    i++;
  }

  insertNode(head, newNode, i);
}

void display(node* head)
{
  node *current = head;
  while (current != NULL) {
    printf ("Node with data: \"%s\" at %p.\n", current->data, current);
    current = current->next;
  }
  printf("\n\n\n");
}

int main()
{
  node* head = NULL;
  char input[40];

  while (1) {
    fgets(input, sizeof(input), stdin);
    int cmp = strcmp("done", strtok(input, "\n"));
    if (cmp == 0) {
      printf("Done and done!\n\n");
      break;
    }
    node* newNode = createNode(input);
    appendNode(&head, newNode);
  }

  display(head);
}
