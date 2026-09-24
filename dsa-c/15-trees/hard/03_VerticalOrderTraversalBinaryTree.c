/**
 * Problem: Vertical Order Traversal of a Binary Tree (LeetCode 987)
 * Asked in: Facebook, Amazon, Google, Bloomberg
 * 
 * Given the root of a binary tree, calculate the vertical order traversal.
 * For each node at (row, col):
 * - Left child is at (row + 1, col - 1)
 * - Right child is at (row + 1, col + 1)
 * 
 * Sort criteria:
 * 1. By column (left to right)
 * 2. Within same column, by row (top to bottom)
 * 3. Within same column and row, by value ascending
 * 
 * Approach:
 * DFS with TreeMap:
 * - Map: col -> (row -> List of values)
 * - Sort the list of values for matching (col, row) before appending to output.
 * 
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(N) to store node coordinates and values.
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

static Map<int, Map<int, int*>> map;

    int*> verticalTraversal(TreeNode* root) {
        map = new TreeMap<>();
        dfs(root, 0, 0);

        int*> result = new ArrayList<>();
        for (Map<int, int*> rowMap : map.values()) {
            int* colResult = new ArrayList<>();
            for (int* list : rowMap.values()) {
                Collections.sort(list);
                colResult.addAll(list);
            }
            result.add(colResult);
        }

        return result;
    }

    static void dfs(TreeNode* node, int row, int col) {
        if (node == NULL) return;

        map.putIfAbsent(col, new TreeMap<>());
        map.get(col).putIfAbsent(row, new ArrayList<>());
        map.get(col).get(row).add(node->val);

        dfs(node->left, row + 1, col - 1);
        dfs(node->right, row + 1, col + 1);
    }

    int main(void) {
        // [3, 9, 20, NULL, NULL, 15, 7]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(9);
        root->right = createTreeNode(20);
        root->right->left = createTreeNode(15);
        root->right->right = createTreeNode(7);

        printf("Vertical Traversal: %d\n", verticalTraversal(root));
        // Expected: [[9], [3, 15], [20], [7]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
