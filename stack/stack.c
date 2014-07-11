#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int* data;
  int top;
  int maxSize;
} stack;

stack* createStack(size_t initialSize)
{
  stack* newStack = (stack*) malloc(sizeof(stack));
  newStack->data = (int*) malloc(initialSize * sizeof(int));
  newStack->top = 0;
  newStack->maxSize = initialSize;
  return newStack;
}

void push(stack* targetStack, int element)
{
  if (targetStack->top >= targetStack->maxSize) {
    targetStack->maxSize *= 2;
    targetStack->data = (int*) realloc(targetStack->data, targetStack->maxSize * sizeof(int));
  }
  targetStack->data[targetStack->top] = element;
  targetStack->top++;
}

int peek(stack* targetStack)
{
  return targetStack->data[targetStack->top - 1];
}

int pop(stack* targetStack)
{
  int value = peek(targetStack);
  targetStack->top -= 1;
  if (targetStack->top < (targetStack->maxSize / 2)) {
    targetStack->maxSize = targetStack->maxSize / 2;
    targetStack->data = (int*) realloc(targetStack->data, targetStack->maxSize * sizeof(int));
  }
  return value;
}

void display(stack* myStack)
{
  printf("Stack at %p with top index: %d, max size: %d and top content: %d\n\n",
    myStack,
    myStack->top,
    myStack->maxSize,
    peek(myStack)
  );
}

int main()
{
  stack* myStack = createStack(2);

  char input[10];
  int value;
  while (1) {
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &value);

    if (strcmp("pop\n", input) == 0) {
      printf("Value %d popped.\n", pop(myStack));
    } else if (strcmp("done\n", input) == 0) {
      break;
    } else if (strcmp("peek\n", input) == 0) {
      printf("Value %d on top of stack.\n", peek(myStack));
    } else {
      push(myStack, value);
    }

    display(myStack);
  }
}
