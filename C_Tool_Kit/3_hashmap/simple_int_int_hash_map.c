#include <stdio.h>
#include <stdlib.h>

// Define the structure for a hash map entry (key-value pair)
typedef struct Node {
    int key;
    int value;
    struct Node* next;  // For handling collisions using chaining
} Node;

// Define the hash map structure
typedef struct HashMap {
    Node** table;  // Array of pointers to linked lists
    int size;      // Size of the hash table
} HashMap;

// Hash function to calculate index from key
int hash(int key, int size) {
    return key % size;  // Simple modulo hash function
}

// Create a new hash map
HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->table = (Node**)malloc(sizeof(Node*) * size);

    for (int i = 0; i < size; i++) {
        map->table[i] = NULL;
    }

    return map;
}

// Insert a key-value pair into the hash map
void insert(HashMap* map, int key, int value) {
    int index = hash(key, map->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->table[index];
    map->table[index] = newNode;
}

// Lookup a value by its key
int lookup(HashMap* map, int key) {
    int index = hash(key, map->size);
    Node* current = map->table[index];

    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return -1;  // Return -1 if the key doesn't exist
}

// Free the hash map and its associated memory
void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Node* current = map->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map->table);
    free(map);
}

// Test the hash map implementation
int main() {
    // Create a hash map of size 10
    HashMap* map = createHashMap(10);

    // Insert key-value pairs
    insert(map, 1, 100);
    insert(map, 2, 200);
    insert(map, 11, 300);  // This will hash to the same index as key 1 (collision)

    // Lookup values by key
    printf("Value for key 1: %d\n", lookup(map, 1));
    printf("Value for key 2: %d\n", lookup(map, 2));
    printf("Value for key 11: %d\n", lookup(map, 11));
    printf("Value for key 3: %d\n", lookup(map, 3));  // Non-existent key, should return -1

    // Free the hash map
    freeHashMap(map);

    return 0;
}
