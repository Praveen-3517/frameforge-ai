/**
 * Problem: Binary Tree Inorder Traversal (LeetCode 94)
 * Asked in: Amazon, Microsoft, Adobe
 * 
 * Given the root of a binary tree, return the inorder traversal of its nodes' values.
 * (Order: Left -> Root -> Right)
 * 
 * Approach:
 * Iterative using Stack:
 * 1. Initialize current node as root.
 * 2. Push current node and go left until current is null.
 * 3. Pop from stack, add to result, and set current = popped.right.
 * 4. Repeat until stack is empty and current is null.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) where H is height of the tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

static TreeNode* createTreeNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) exit(1);
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int* inorderTraversal(TreeNode* root) {
        int* result = new ArrayList<>();
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode* curr = root;

        while (curr != NULL || !stack.isEmpty()) {
            while (curr != NULL) {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.pop();
            result.add(curr->val);
            curr = curr->right;
        }

        return result;
    }

    int main(void) {
        TreeNode* root = createTreeNode(1);
        root->right = createTreeNode(2);
        root->right->left = createTreeNode(3);

        printf("Inorder: " + inorderTraversal(root) + " (Expected: [1, 3, 2])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
