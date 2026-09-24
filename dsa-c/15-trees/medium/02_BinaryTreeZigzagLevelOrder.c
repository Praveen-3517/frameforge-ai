/**
 * Problem: Binary Tree Zigzag Level Order Traversal (LeetCode 103)
 * Asked in: Amazon, Microsoft, Facebook, Bloomberg
 * 
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes'
 * values. (i.e., from left to right, then right to left for the next level and alternate between).
 * 
 * Approach:
 * BFS with LinkedList / Deque for each level:
 * - Maintain a boolean flag `leftToRight`.
 * - For each level, if leftToRight is true, append values to the back (`addLast`).
 * - If false, prepend values to the front (`addFirst`).
 * - Invert flag after each level.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is maximum width of the tree.
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

int*> zigzagLevelOrder(TreeNode* root) {
        int*> result = new ArrayList<>();
        if (root == NULL) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);
        bool leftToRight = true;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            LinkedList<int> currentLevel = new LinkedList<>();

            for (int i = 0; i < levelSize; i++) {
                TreeNode* curr = queue.poll();
                if (leftToRight) {
                    currentLevel.addLast(curr->val);
                } else {
                    currentLevel.addFirst(curr->val);
                }

                if (curr->left != NULL) queue.offer(curr->left);
                if (curr->right != NULL) queue.offer(curr->right);
            }

            result.add(currentLevel);
            leftToRight = !leftToRight;
        }

        return result;
    }

    int main(void) {
        // [3, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(9);
        root->right = createTreeNode(20);
        root->right->left = createTreeNode(15);
        root->right->right = createTreeNode(7);

        printf("Zigzag: %d\n", zigzagLevelOrder(root));
        // Expected: [[3], [20, 9], [15, 7]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
