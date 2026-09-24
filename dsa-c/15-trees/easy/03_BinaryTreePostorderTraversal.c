/**
 * Problem: Binary Tree Postorder Traversal (LeetCode 145)
 * Asked in: Facebook, Amazon, Google
 * 
 * Given the root of a binary tree, return the postorder traversal of its nodes' values.
 * (Order: Left -> Right -> Root)
 * 
 * Approach:
 * Iterative using modified preorder:
 * Standard preorder is Root -> Left -> Right.
 * If we traverse Root -> Right -> Left, and then reverse the entire output list,
 * we get Left -> Right -> Root (exact postorder sequence)!
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) where H is tree height.
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

int* postorderTraversal(TreeNode* root) {
        int* result = new ArrayList<>();
        if (root == NULL) return result;

        Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode* curr = stack.pop();
            result.add(curr->val);

            // Push left first so right is processed first (Root -> Right -> Left)
            if (curr->left != NULL) stack.push(curr->left);
            if (curr->right != NULL) stack.push(curr->right);
        }

        Collections.reverse(result);
        return result;
    }

    int main(void) {
        TreeNode* root = createTreeNode(1);
        root->right = createTreeNode(2);
        root->right->left = createTreeNode(3);

        printf("Postorder: " + postorderTraversal(root) + " (Expected: [3, 2, 1])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
