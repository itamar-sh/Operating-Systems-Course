#include <stdio.h>

/*
In this question you need to write a function deleteAlt that deletes alternate (every 2nd) element from a linked list, starting from its head.

You are given a linked list implementation that includes three functions:

push will add the element to the head of the list

printList displays list elements

deleteList deletes list elements

For example:

Test	Result
  push(1);
  push(2);
  push(3);
  push(4);
  printList();
  deleteAlt();
  printList();
  deleteList();
4 3 2 1
4 2
*/


typedef struct Node
{
  int data;
  Node* next;
} Node;

Node *head = NULL;

void deleteAlt()
{
    if (head == NULL) return;
    Node* prev = head;
    Node* cur = head->next;
    while (cur != NULL) {
        prev->next = cur->next;
        free(cur);
        prev = prev->next;
        if (prev && prev->next) {
            cur = prev->next;
        } else {
            break;
        }
    }
}

void push(int new_data)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data  = new_data;
    new_node->next = head;
    head = new_node;
}

void printList()
{
  Node *temp = head;
  while(temp != NULL)
    {
      printf("%d ", temp->data);
      temp = temp->next;
    }
  printf("\n");
}

void deleteList()
{
  Node *temp = head;
  while(temp != NULL)
    {
      Node *next = temp->next;
      free(temp);
      temp = next;
    }
  head = NULL;
}

int main() {
    // Create a linked list: 1 -> 2 -> 3 -> 4 -> 5
    push(5);
    push(4);
    push(3);
    push(2);
    push(1);

    printf("Original List:\n");
    printList();

    // Delete alternate nodes
    deleteAlt();

    printf("List after deleting alternate nodes:\n");
    printList();

    // Clean up
    deleteList();
    return 0;
}
