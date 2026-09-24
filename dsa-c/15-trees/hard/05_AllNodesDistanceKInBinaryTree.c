/**
 * Problem: All Nodes Distance K in Binary Tree (LeetCode 863)
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * Given the root of a binary tree, a target node, and an integer k, return an array
 * of the values of all nodes that have a distance k from the target node.
 * 
 * Approach:
 * 1. Tree to Graph Conversion:
 *    Traverse tree with DFS/BFS to populate a Map<TreeNode, TreeNode> parentMap,
 *    enabling bidirectional movement (to left, to right, and to parent).
 * 2. BFS from Target:
 *    Start standard BFS queue at `target` with distance = 0 and a visited set.
 *    Expand outward layer by layer until distance == k.
 *    The queue contents at distance k are the answer!
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(N) for parent map and BFS queue/set.
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

int* distanceK(TreeNode* root, TreeNode* target, int k) {
        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        buildParentMap(root, NULL, parentMap);

        Queue<TreeNode> queue = new ArrayDeque<>();
        Set<TreeNode> visited = new HashSet<>();

        queue.offer(target);
        visited.add(target);
        int currentDistance = 0;

        while (!queue.isEmpty()) {
            if (currentDistance == k) {
                int* result = new ArrayList<>();
                for (TreeNode* node : queue) {
                    result.add(node->val);
                }
                return result;
            }

            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode* curr = queue.poll();

                // Explore left
                if (curr->left != NULL && !visited.contains(curr->left)) {
                    visited.add(curr->left);
                    queue.offer(curr->left);
                }
                // Explore right
                if (curr->right != NULL && !visited.contains(curr->right)) {
                    visited.add(curr->right);
                    queue.offer(curr->right);
                }
                // Explore parent
                TreeNode* parent = parentMap.get(curr);
                if (parent != NULL && !visited.contains(parent)) {
                    visited.add(parent);
                    queue.offer(parent);
                }
            }
            currentDistance++;
        }

        return new ArrayList<>();
    }

    static void buildParentMap(TreeNode* node, TreeNode* parent, Map<TreeNode, TreeNode> map) {
        if (node == NULL) return;
        if (parent != NULL) map.put(node, parent);
        buildParentMap(node->left, node, map);
        buildParentMap(node->right, node, map);
    }

    int main(void) {
        // [3, 5, 1, 6, 2, 0, 8, NULL, NULL, 7, 4]
        TreeNode* root = createTreeNode(3);
        root->left = createTreeNode(5);
        root->right = createTreeNode(1);
        root->left->left = createTreeNode(6);
        root->left->right = createTreeNode(2);
        root->right->left = createTreeNode(0);
        root->right->right = createTreeNode(8);
        root->left->right->left = createTreeNode(7);
        root->left->right->right = createTreeNode(4);

        TreeNode* target = root->left; // Node 5
        int k = 2;

        int* result = distanceK(root, target, k);
        printf("Distance 2 nodes: %d\n", result);
        // Expected: [7, 4, 1]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
