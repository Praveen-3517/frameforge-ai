/**
 * Problem: Binary Tree Right Side View (LeetCode 199)
 * Asked in: Facebook, Amazon, Bloomberg, Microsoft
 * 
 * Given the root of a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 * 
 * Approach:
 * Level-Order Traversal (BFS):
 * In each level of BFS, the last node processed in that level is the rightmost visible node.
 * Add that last node to our result list.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is maximum width of tree.
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

int* rightSideView(TreeNode* root) {
        int* result = new ArrayList<>();
        if (root == NULL) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = queue.poll();
                // If it is the last node in the current level, record it
                if (i == levelSize - 1) {
                    result.add(curr->val);
                }
                if (curr->left != NULL) queue.offer(curr->left);
                if (curr->right != NULL) queue.offer(curr->right);
            }
        }

        return result;
    }

    int main(void) {
        // [1, 2, 3, NULL, 5, NULL, 4]
        TreeNode* root = createTreeNode(1);
        root->left = createTreeNode(2);
        root->right = createTreeNode(3);
        root->left->right = createTreeNode(5);
        root->right->right = createTreeNode(4);

        printf("Right Side View: " + rightSideView(root) + " (Expected: [1, 3, 4])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
