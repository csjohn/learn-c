#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  float* data;
  int front;
  int size;
  int count;
} queue;

queue* createQueue(int size)
{
  queue* newQueue = (queue*) malloc(sizeof(queue));
  newQueue->data = (float*) malloc(sizeof(float) * size);
  newQueue->front = 0;
  newQueue->size = size;
  newQueue->count = 0;
  return newQueue;
}

void display(queue* theQueue)
{
  printf("Size: %d, Front: %d, Count: %d. - ", theQueue->size, theQueue->front, theQueue->count);
  for(int i = theQueue->front; i < theQueue->front + theQueue->count; i++) {
    printf("%d: %3.2f, ", i, theQueue->data[i % theQueue->size]);
  }
  printf("\n");
}

void enqueue(queue* theQueue, float element)
{
  // Grow the data block
  if (theQueue->count >= theQueue->size) {
    float* newData = (float*) malloc(sizeof(float) * (theQueue->size * 2));
    for (int i = 0; i < theQueue->count; i++) {
      newData[i] = theQueue->data[(theQueue->front + i) % theQueue->size];
    }
    free(theQueue->data);
    theQueue->data = newData;
    theQueue->front = 0;
    theQueue->size = theQueue->size * 2;
  }

  theQueue->data[(theQueue->front + theQueue->count) % theQueue->size] = element;
  theQueue->count++;
  printf("Add.   ");
  display(theQueue);
}

float dequeue(queue* theQueue)
{
  if (theQueue->count == 0) {
    return 0;
  }

  if (theQueue->count < (theQueue->size / 2)) {
    float* newData = (float*) malloc(sizeof(float) * (theQueue->size / 2));
    for (int i = 0; i < theQueue->count; i++) {
      newData[i] = theQueue->data[(theQueue->front + i) % theQueue->size];
    }
    free(theQueue->data);
    theQueue->data = newData;
    theQueue->front = 0;
    theQueue->size = theQueue->size / 2;
  }

  float val = theQueue->data[theQueue->front];
  theQueue->count--;
  theQueue->front++;
  theQueue->front = theQueue->front % theQueue->size;
  return val;
}

int main()
{
  queue* myQueue = createQueue(2);

  char input[12];
  char command[5];
  float value;
  while (1) {
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%s %f", command, &value);

    if (strcmp("add", strtok(command, "\n")) == 0) {
      enqueue(myQueue, value);
    } else if (strcmp("get", strtok(command, "\n")) == 0) {
      printf("%3.2f\n", dequeue(myQueue));
    } else if (strcmp("display", strtok(command, "\n")) == 0) {
      display(myQueue);
    }
  }
}
