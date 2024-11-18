#include <stdio.h>
#include "binary_tree_basic_checks.c"


typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Vector;


typedef struct {
    struct TreeNode** data;
    size_t size;
    size_t capacity;
} NodeQueue;


void append_to_vector(Vector* vector, int element) {
    if (vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (int*)realloc(vector->data, vector->capacity * sizeof(int));
    }
    vector->data[vector->size] = element;
    vector->size++;
}


void append_to_node_queue(NodeQueue* queue, struct TreeNode* element) {
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->data = (struct TreeNode**)realloc(queue->data, queue->capacity * sizeof(struct TreeNode*));
    }
    queue->data[queue->size] = element;
    queue->size++;
}


int* right_side_view_naive(struct TreeNode* root, size_t* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    int* result_pointer;
    Vector* result = (struct Vector*)malloc(sizeof(Vector));
    if (!result) return NULL;
    result->capacity = 16;
    result->size = 0;
    result->data = (int*)malloc(sizeof(int)*result->capacity);

    NodeQueue* queue = (NodeQueue*)malloc(sizeof(NodeQueue));
    if (!queue) return NULL;
    queue->capacity = 16;
    queue->size = 0;
    queue->data = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * queue->capacity);

    NodeQueue* next_queue = (NodeQueue*)malloc(sizeof(NodeQueue));
    if (!next_queue) return NULL;
    next_queue->capacity = 16;
    next_queue->size = 0;
    next_queue->data = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * next_queue->capacity);

    append_to_node_queue(queue, root);


    struct TreeNode* cur_node;
    NodeQueue* temp;
    while(queue->size > 0) {
        int queue_index = 0;
        for (; queue_index < queue->size; queue_index++) {
            cur_node = queue->data[queue_index];
            if (cur_node->left) {
                append_to_node_queue(next_queue, cur_node->left);
            }
            if (cur_node->right) {
                append_to_node_queue(next_queue, cur_node->right);
            }
        }
        append_to_vector(result, queue->data[queue_index-1]->val);
        temp = queue;
        queue = next_queue;
        next_queue = temp;
        next_queue->size = 0;
    }
    *returnSize = result->size;
    result_pointer = result->data;
    free(result);
    free(queue->data);
    free(queue);
    free(next_queue->data);
    free(next_queue);
    return result_pointer;
}