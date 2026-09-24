/**
 * Problem: Kth Smallest Element in a BST (LeetCode 230)
 * Asked in: Amazon, Facebook, Google, Microsoft, Uber
 * 
 * Given the root of a binary search tree, and an integer k, return the kth
 * smallest value (1-indexed) of all the values of the nodes in the tree.
 * 
 * Approach:
 * In-Order Traversal (Left -> Root -> Right):
 * BST in-order produces elements in strictly ascending order.
 * Using an iterative in-order traversal with a stack:
 * Traverse leftwards, pop node, decrement k.
 * When k reaches 0, the current popped node is the k-th smallest element!
 * 
 * Time Complexity: O(H + k) where H is tree height.
 * Space Complexity: O(H) for traversal stack.
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

int kthSmallest(TreeNode* root, int k) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode* curr = root;

        while (curr != NULL || !stack.isEmpty()) {
            while (curr != NULL) {
                stack.push(curr);
                curr = curr->left;
            }

            curr = stack.pop();
            k--;
            if (k == 0) {
                return curr->val;
            }

            curr = curr->right;
        }

        return -1;
    }

    int main(void) {
        // [3, 1, 4, NULL, 2]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(1);
        root->right = createTreeNode(4);
        root->left->right = createTreeNode(2);

        printf("1st smallest: " + kthSmallest(root, 1) + " (Expected: 1)\n");
        printf("2nd smallest: " + kthSmallest(root, 2) + " (Expected: 2)\n");
        printf("3rd smallest: " + kthSmallest(root, 3) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
