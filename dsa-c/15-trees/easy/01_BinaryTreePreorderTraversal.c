/**
 * Problem: Binary Tree Preorder Traversal (LeetCode 144)
 * Asked in: Google, Amazon, Microsoft
 * 
 * Given the root of a binary tree, return the preorder traversal of its nodes' values.
 * (Order: Root -> Left -> Right)
 * 
 * Approach:
 * 1. Recursive: Call root, then preorder(left), then preorder(right).
 * 2. Iterative: Use a stack. Push root. Pop node, record val, push right child first,
 *    then left child (so left is processed next).
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) where H is tree height for stack recursion/iteration.
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

int* preorderTraversalIterative(TreeNode* root) {
        int* result = new ArrayList<>();
        if (root == NULL) return result;

        Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode* curr = stack.pop();
            result.add(curr->val);

            // Push right first so left is popped and visited first
            if (curr->right != NULL) stack.push(curr->right);
            if (curr->left != NULL) stack.push(curr->left);
        }
        return result;
    }

    int main(void) {
        // Tree: 1 -> right: 2 -> left: 3
        TreeNode* root = createTreeNode(1);
        root->right = createTreeNode(2);
        root->right->left = createTreeNode(3);

        printf("Preorder: " + preorderTraversalIterative(root) + " (Expected: [1, 2, 3])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
