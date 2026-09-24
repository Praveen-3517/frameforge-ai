/**
 * Problem: Flatten Binary Tree to Linked List (LeetCode 114)
 * Asked in: Facebook, Amazon, Microsoft, Bloomberg
 * 
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * - The "linked list" should use the same TreeNode class where the right child pointer
 *   points to the next node and left child pointer is always null.
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 * 
 * Approach:
 * Morris-like Pointer Rewiring (O(1) Auxiliary Space):
 * - For current node:
 *   - If current has a left child:
 *     - Find the rightmost node of the left subtree (inorder predecessor).
 *     - Connect the rightmost node's right pointer to current's right child.
 *     - Move current.left to current.right, and set current.left = null.
 *   - Move current to current.right.
 * 
 * Time Complexity: O(N) since each edge is traversed at most twice.
 * Space Complexity: O(1) auxiliary space (in-place modification).
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

void flatten(TreeNode* root) {
        TreeNode* curr = root;

        while (curr != NULL) {
            if (curr->left != NULL) {
                // Find rightmost node in left subtree
                TreeNode* prev = curr->left;
                while (prev->right != NULL) {
                    prev = prev->right;
                }

                // Connect predecessor's right to current's right
                prev->right = curr->right;
                // Move left subtree to right
                curr->right = curr->left;
                curr->left = NULL;
            }
            // Advance to next node on right
            curr = curr->right;
        }
    }

    int main(void) {
        // [1, 2, 5, 3, 4, NULL, 6]
        TreeNode* root = createTreeNode(1);
        root->left = createTreeNode(2);
        root->right = createTreeNode(5);
        root->left->left = createTreeNode(3);
        root->left->right = createTreeNode(4);
        root->right->right = createTreeNode(6);

        flatten(root);

        printf("%s", "Flattened List: ");
        TreeNode* curr = root;
        while (curr != NULL) {
            printf("%s", curr->val + (curr->right != NULL ? " -> " : ""));
            curr = curr->right;
        }
        printf("\n");
        // Expected: 1 -> 2 -> 3 -> 4 -> 5 -> 6
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
