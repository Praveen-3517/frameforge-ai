/**
 * Problem: Serialize and Deserialize Binary Tree (LeetCode 297)
 * Asked in: Facebook, Amazon, Google, Microsoft, Uber
 * 
 * Design an algorithm to serialize and deserialize a binary tree.
 * There is no restriction on how your serialization/deserialization algorithm
 * should work. You just need to ensure that a binary tree can be serialized
 * to a string and this string can be deserialized to the original tree structure.
 * 
 * Approach:
 * Pre-order Traversal (DFS):
 * - Serialize:
 *   If node is null, append "#,".
 *   Otherwise, append node.val + "," followed by serialize(node.left) and serialize(node.right).
 * - Deserialize:
 *   Split string by "," into a Queue/Deque.
 *   Poll token: if "#", return null.
 *   Otherwise create TreeNode(Integer.parseInt(token)), then left = build(), right = build().
 * 
 * Time Complexity: O(N) for both serialization and deserialization.
 * Space Complexity: O(N) for recursion and string storage.
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

static const const char* NULL_NODE = "#";
    static const const char* DELIMITER = ",";

    // Encodes a tree to a single string.
    const char* serialize(TreeNode* root) {
        StringBuilder sb = new StringBuilder();
        serializeHelper(root, sb);
        return sb.toString();
    }

    static void serializeHelper(TreeNode* node, StringBuilder sb) {
        if (node == NULL) {
            sb.append(NULL_NODE).append(DELIMITER);
            return;
        }
        sb.append(node->val).append(DELIMITER);
        serializeHelper(node->left, sb);
        serializeHelper(node->right, sb);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const char* data) {
        Deque<const char*> nodes = new ArrayDeque<>(Arrays.asList(data.split(DELIMITER)));
        return deserializeHelper(nodes);
    }

    static TreeNode* deserializeHelper(Deque<const char*> nodes) {
        if (nodes.isEmpty()) return NULL;
        const char* val = nodes.poll();
        if ((strcmp(val, NULL_NODE) == 0)) return NULL;

        TreeNode* node = createTreeNode(int.parseInt(val));
        node->left = deserializeHelper(nodes);
        node->right = deserializeHelper(nodes);
        return node;
    }

    static void printInorder(TreeNode* root) {
        if (root == NULL) return;
        printInorder(root->left);
        printf("%s", root->val + " ");
        printInorder(root->right);
    }

    int main(void) {
        // [1, 2, 3, NULL, NULL, 4, 5]
        TreeNode* root = createTreeNode(1);
        root->left = createTreeNode(2);
        root->right = createTreeNode(3);
        root->right->left = createTreeNode(4);
        root->right->right = createTreeNode(5);

        const char* serialized = serialize(root);
        printf("Serialized: %d\n", serialized);

        TreeNode* deserialized = deserialize(serialized);
        printf("%s", "Deserialized Inorder: ");
        printInorder(deserialized);
        printf("\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
