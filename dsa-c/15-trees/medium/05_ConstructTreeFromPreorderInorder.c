/**
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal (LeetCode 105)
 * Asked in: Amazon, Microsoft, Facebook, Google, Bloomberg
 * 
 * Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same tree,
 * construct and return the binary tree.
 * 
 * Approach:
 * - Preorder provides the ROOT at the current subtree's starting index.
 * - Inorder splits nodes into LEFT subtree (left of root) and RIGHT subtree (right of root).
 * - Precompute inorder indices in a HashMap for O(1) lookup.
 * - Recursively construct left subtree and right subtree with accurate sub-array boundaries.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(N) for hash map and recursion stack.
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

static Map<int, int> inorderIndexMap;
    static int preorderIndex;

    TreeNode* buildTree(int* preorder, int* inorder) {
        inorderIndexMap = new HashMap<>();
        preorderIndex = 0;

        for (int i = 0; i < n; i++) {
            inorderIndexMap.put(inorder[i], i);
        }

        return buildSubtree(preorder, 0, n - 1);
    }

    static TreeNode* buildSubtree(int* preorder, int inStart, int inEnd) {
        if (inStart > inEnd) return NULL;

        int rootVal = preorder[preorderIndex++];
        TreeNode* root = createTreeNode(rootVal);

        int rootIndexInorder = inorderIndexMap.get(rootVal);

        // Build left subtree with elements before root in inorder
        root->left = buildSubtree(preorder, inStart, rootIndexInorder - 1);
        // Build right subtree with elements after root in inorder
        root->right = buildSubtree(preorder, rootIndexInorder + 1, inEnd);

        return root;
    }

    static void printInorder(TreeNode* root) {
        if (root == NULL) return;
        printInorder(root->left);
        printf("%s", root->val + " ");
        printInorder(root->right);
    }

    int main(void) {
        int* preorder = {3, 9, 20, 15, 7};
        int* inorder = {9, 3, 15, 20, 7};

        TreeNode* root = buildTree(preorder, inorder);
        printf("%s", "Reconstructed Inorder: ");
        printInorder(root);
        printf("\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
