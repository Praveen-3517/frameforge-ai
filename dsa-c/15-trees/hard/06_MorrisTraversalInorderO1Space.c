/**
 * Problem: Morris In-Order Traversal with O(1) Auxiliary Space
 * Asked in: Google, Microsoft, Amazon, Bloomberg
 * 
 * Given the root of a binary tree, return its in-order traversal using O(1) auxiliary space
 * (i.e. no recursion stack and no explicit stack data structure).
 * 
 * Approach:
 * Morris Traversal (Threaded Binary Tree):
 * 1. Initialize `curr` as root.
 * 2. While `curr != null`:
 *    - If `curr.left == null`:
 *      Visit `curr` (add to result) and move `curr = curr.right`.
 *    - Else:
 *      Find in-order predecessor `prev` (rightmost node in left subtree).
 *      - If `prev.right == null`:
 *        Create temporary thread: `prev.right = curr`, then advance `curr = curr.left`.
 *      - If `prev.right == curr`:
 *        Remove temporary thread: `prev.right = null`, visit `curr`, and advance `curr = curr.right`.
 * 
 * Time Complexity: O(N) because each edge is traversed at most twice (once for threading, once for visit/unthreading).
 * Space Complexity: O(1) auxiliary space.
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

int* morrisInorder(TreeNode* root) {
        int* result = new ArrayList<>();
        TreeNode* curr = root;

        while (curr != NULL) {
            if (curr->left == NULL) {
                result.add(curr->val);
                curr = curr->right;
            } else {
                // Find inorder predecessor
                TreeNode* prev = curr->left;
                while (prev->right != NULL && prev->right != curr) {
                    prev = prev->right;
                }

                if (prev->right == NULL) {
                    // Create thread to current node
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // Thread already exists -> revert change, visit node, go right
                    prev->right = NULL;
                    result.add(curr->val);
                    curr = curr->right;
                }
            }
        }

        return result;
    }

    int main(void) {
        // [1, 2, 3, 4, 5]
        TreeNode* root = createTreeNode(4);
        root->left = createTreeNode(2);
        root->right = createTreeNode(5);
        root->left->left = createTreeNode(1);
        root->left->right = createTreeNode(3);

        int* inorder = morrisInorder(root);
        printf("Morris Inorder: " + inorder + " (Expected: [1, 2, 3, 4, 5])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
