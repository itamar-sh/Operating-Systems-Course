#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a node for the linked list
typedef struct Node {
    int data;
    struct Node* next;
    // struct Node* prev;  If a double linked list - where you can remove from the back
} Node;

// Define the queue using a linked list
typedef struct {
    Node* front;  // Pointer to the front node
    Node* rear;   // Pointer to the rear node
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue an element
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue an element
bool dequeue(Queue* q, int* value) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return false;
    }

    Node* temp = q->front;
    *value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) { // If the queue is now empty
        q->rear = NULL;
    }

    free(temp);
    return true;
}

// Peek the front element
bool peek(Queue* q, int* value) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return false;
    }

    *value = q->front->data;
    return true;
}

// Display the queue elements
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    Node* current = q->front;
    printf("Queue elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
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

    displayQueue(&q);

    int value;
    dequeue(&q, &value);
    printf("Dequeued: %d\n", value);

    displayQueue(&q);

    return 0;
}
