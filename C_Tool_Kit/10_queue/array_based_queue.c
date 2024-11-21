#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5  // Maximum size of the queue

typedef struct {
    int data[MAX_SIZE];
    int front; // Index of the front element
    int rear;  // Index of the last element
    int size;  // Current size of the queue
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    return q->size == 0;
}

// Check if the queue is full
bool isFull(Queue* q) {
    return q->size == MAX_SIZE;
}

// Enqueue an element
bool enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return false;
    }

    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

// Dequeue an element
bool dequeue(Queue* q, int* value) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return false;
    }

    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return true;
}

// Peek the front element
bool peek(Queue* q, int* value) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return false;
    }

    *value = q->data[q->front];
    return true;
}

// Display the queue elements
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    int index = q->front;
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->data[index]);
        index = (index + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    displayQueue(&q);

    int value;
    dequeue(&q, &value);
    printf("Dequeued: %d\n", value);

    enqueue(&q, 60);

    displayQueue(&q);

    return 0;
}
