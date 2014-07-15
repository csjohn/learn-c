#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"

linkedListNode* createLinkedListNode(char *data)
{
  linkedListNode *newNode = malloc(sizeof(linkedListNode));
  strcpy(newNode->data, data);
  newNode->next = NULL;
  return newNode;
}

void deleteLinkedListNode(linkedListNode** head, int index)
{
  linkedListNode* prev = NULL;
  linkedListNode* current = *head;

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

void insertLinkedListNode(linkedListNode** head, linkedListNode* newNode, int index)
{
  linkedListNode* prev = NULL;
  linkedListNode* current = *head;

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

void appendLinkedListNode(linkedListNode** head, linkedListNode* newNode)
{
  linkedListNode* current = *head;

  // Empty list
  if (current == NULL) {
    return insertLinkedListNode(head, newNode, 0);
  }

  // Non-empty list
  int i = 1;
  while (current->next != NULL) {
    current = current->next;
    i++;
  }

  insertLinkedListNode(head, newNode, i);
}

void displayLinkedList(linkedListNode* head)
{
  linkedListNode *current = head;
  while (current != NULL) {
    printf ("Node with data: \"%s\" at %p.\n", current->data, current);
    current = current->next;
  }
  printf("\n\n\n");
}

/*
int main()
{
  linkedListNode* head = NULL;
  char input[40];

  while (1) {
    fgets(input, sizeof(input), stdin);
    int cmp = strcmp("done", strtok(input, "\n"));
    if (cmp == 0) {
      printf("Done and done!\n\n");
      break;
    }
    linkedListNode* newNode = createLinkedListNode(input);
    appendLinkedListNode(&head, newNode);
  }

  displayLinkedList(head);
}
*/

