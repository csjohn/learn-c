#include <stdlib.h>
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

void add(queue* theQueue, float element)
{
  if (theQueue->count >= theQueue->size) {
    printf("Aint no more room left.\n");
    return;
  }

  theQueue->data[(theQueue->front + theQueue->count) % theQueue->size] = element;
  theQueue->count++;
}

float dequeue(queue* theQueue)
{
  theQueue->count--;
  return theQueue->data[theQueue->front++];
}

void display(queue* theQueue)
{
  printf("Queue at %p, front: %d, count: %d.\n", theQueue, theQueue->front, theQueue->count);
  for(int i = theQueue->front; i < theQueue->front + theQueue->count; i++) {
    printf("Element %d, Value: %f.\n", i, theQueue->data[i % theQueue->size]);
  }
}

int main()
{
  queue* myQueue = createQueue(5);
  add(myQueue, 5.0);
  add(myQueue, 8.0);
  add(myQueue, 9.0);
  add(myQueue, 10.0);
  add(myQueue, 11.0);
  display(myQueue);
  dequeue(myQueue);
  display(myQueue);
  add(myQueue, 12.0);
  display(myQueue);
  dequeue(myQueue);
  dequeue(myQueue);
  display(myQueue);
}
