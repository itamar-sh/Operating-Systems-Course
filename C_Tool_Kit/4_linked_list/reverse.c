/*
In this question you need to write a function reverse that reverses a linked list.

You are given a linked list implementation that includes three functions:

push will add the element to the head of the list

deleteList deletes list elements

printList displays list elements
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
  int data;
  struct Node* next;
} Node;

Node* reverse_linked_list(Node* cur) {
    Node* prev = NULL;
    Node* next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}


int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    Node* old = head;
    for (int i = 1; i < 5; i++) {
        Node* new = (Node*)malloc(sizeof(Node));
        new->data = i;
        old->next = new;
        old = new;
    }
    old->next = NULL;
    head = reverse_linked_list(head);
    Node* temp = head;
    while (head != NULL) {
        fprintf(stdout, "%d \n", head->data);
        head = head->next;
    }
    head = temp;
    while (head != NULL) {
        old = head;
        head = head->next;
        free(old);
    }
    return 0;
}