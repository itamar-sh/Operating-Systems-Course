#include <stdlib.h>
#include "binary_tree_basic_checks.h"


struct TreeNode* createNode(int val, struct TreeNode* left, struct TreeNode* right) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}


int isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL) {
        return 1;
    } else if (p == NULL || q == NULL || p->val != q->val) {
        return 0;
    } else {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
}


// Given the root of a binary tree and an integer targetSum, return true if
// the tree has a root-to-leaf path such that adding up all the values
// along the path equals targetSum. A leaf is a node with no children.
int hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL && root->val == targetSum) {
        return 1;
    }
    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}


// Test functions
void testIsSameTree() {
    printf("testIsSameTree\n");

    // Test case 1: Both trees are empty
    struct TreeNode* tree1 = NULL;
    struct TreeNode* tree2 = NULL;
    printf("Test case 1: %s\n", isSameTree(tree1, tree2) ? "Passed" : "Failed");

    // Test case 2: Both trees are the same
    tree1 = createNode(1, createNode(2, NULL, NULL), createNode(3, NULL, NULL));
    tree2 = createNode(1, createNode(2, NULL, NULL), createNode(3, NULL, NULL));
    printf("Test case 2: %s\n", isSameTree(tree1, tree2) ? "Passed" : "Failed");

    // Clean up memory
    free(tree1->left);
    free(tree1->right);
    free(tree1);
    free(tree2->left);
    free(tree2->right);
    free(tree2);

    // Test case 3: Trees have different structures
    tree1 = createNode(1, createNode(2, NULL, NULL), NULL);
    tree2 = createNode(1, NULL, createNode(2, NULL, NULL));
    printf("Test case 3: %s\n", isSameTree(tree1, tree2) ? "Failed" : "Passed");

    // Clean up memory
    free(tree1->left);
    free(tree1);
    free(tree2->right);
    free(tree2);
}

void testHasPathSum() {
    printf("testHasPathSum\n");

    // Test case 1: Tree has a path that sums to target
    struct TreeNode* root1 = createNode(5,
        createNode(4,
            createNode(11,
                createNode(7, NULL, NULL),
                createNode(2, NULL, NULL)
            ), NULL
        ),
        createNode(8,
            createNode(13, NULL, NULL),
            createNode(4, NULL, createNode(1, NULL, NULL))
        )
    );
    printf("Test case 1: %s\n", hasPathSum(root1, 22) ? "Passed" : "Failed");

    // Test case 2: Tree does not have a path that sums to target
    struct TreeNode* root2 = createNode(1, createNode(2, NULL, NULL), createNode(3, NULL, NULL));
    printf("Test case 2: %s\n", hasPathSum(root2, 5) ? "Failed" : "Passed");

    // Test case 3: Empty tree
    struct TreeNode* root3 = NULL;
    printf("Test case 3: %s\n", hasPathSum(root3, 0) ? "Failed" : "Passed");

    // Clean up memory
    free(root1->left->left->left);
    free(root1->left->left->right);
    free(root1->left->left);
    free(root1->left);
    free(root1->right->right);
    free(root1->right->left);
    free(root1->right);
    free(root1);

    free(root2->left);
    free(root2->right);
    free(root2);
}

int main() {
    testIsSameTree();
    testHasPathSum();
    return 0;
}