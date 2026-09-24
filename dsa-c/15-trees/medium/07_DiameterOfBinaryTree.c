/**
 * Problem: Diameter of Binary Tree (LeetCode 543)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two
 * nodes in a tree. This path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges between them.
 * 
 * Approach:
 * Bottom-Up DFS (Post-order):
 * For every node, the longest path passing through it as the highest point is:
 *   leftSubtreeHeight + rightSubtreeHeight
 * While computing the height of each subtree recursively, update a global maximum diameter.
 * 
 * Time Complexity: O(N) visiting each node once.
 * Space Complexity: O(H) recursion stack where H is tree height.
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

static int maxDiameter = 0;

    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        calculateHeight(root);
        return maxDiameter;
    }

    static int calculateHeight(TreeNode* node) {
        if (node == NULL) return 0;

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        // Path length through current node is leftHeight + rightHeight
        maxDiameter = MAX(maxDiameter, leftHeight + rightHeight);

        return 1 + MAX(leftHeight, rightHeight);
    }

    int main(void) {
        // [1, 2, 3, 4, 5]
        TreeNode* root = createTreeNode(1);
        root->left = createTreeNode(2);
        root->right = createTreeNode(3);
        root->left->left = createTreeNode(4);
        root->left->right = createTreeNode(5);

        printf("Diameter: " + diameterOfBinaryTree(root) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
