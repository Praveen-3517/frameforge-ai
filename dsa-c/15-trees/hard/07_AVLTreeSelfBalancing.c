/**
 * Problem: Self-Balancing Binary Search Tree (AVL Tree)
 * Asked in: Google, Oracle, Microsoft, Systems & Database Engineering
 * 
 * Implement an AVL Tree supporting:
 * - insert(key)
 * - delete(key)
 * - search(key)
 * Guaranteed O(log N) height and operation time via 4 types of rotations:
 * 1. Left-Left (LL) -> Right Rotate
 * 2. Right-Right (RR) -> Left Rotate
 * 3. Left-Right (LR) -> Left Rotate left child, then Right Rotate node
 * 4. Right-Left (RL) -> Right Rotate right child, then Left Rotate node
 * 
 * Time Complexity: O(log N) for insert, delete, and search.
 * Space Complexity: O(N) for tree storage.
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

static Node root;

    static int height(Node n) {
        return n == NULL ? 0 : n.height;
    }

    static int getBalance(Node n) {
        return n == NULL ? 0 : height(n.left) - height(n.right);
    }

    static Node rightRotate(Node y) {
        Node x = y.left;
        Node t2 = x.right;

        // Perform rotation
        x.right = y;
        y.left = t2;

        // Update heights
        y.height = MAX(height(y.left), height(y.right)) + 1;
        x.height = MAX(height(x.left), height(x.right)) + 1;

        return x;
    }

    static Node leftRotate(Node x) {
        Node y = x.right;
        Node t2 = y.left;

        // Perform rotation
        y.left = x;
        x.right = t2;

        // Update heights
        x.height = MAX(height(x.left), height(x.right)) + 1;
        y.height = MAX(height(y.left), height(y.right)) + 1;

        return y;
    }

    void insert(int key) {
        root = insertRec(root, key);
    }

    static Node insertRec(Node node, int key) {
        if (node == NULL) return new Node(key);

        if (key < node.key) {
            node.left = insertRec(node.left, key);
        } else if (key > node.key) {
            node.right = insertRec(node.right, key);
        } else {
            return node; // Duplicate keys not allowed
        }

        // Update height
        node.height = 1 + MAX(height(node.left), height(node.right));

        // Get balance factor
        int balance = getBalance(node);

        // Case 1: Left-Left
        if (balance > 1 && key < node.left.key) {
            return rightRotate(node);
        }
        // Case 2: Right-Right
        if (balance < -1 && key > node.right.key) {
            return leftRotate(node);
        }
        // Case 3: Left-Right
        if (balance > 1 && key > node.left.key) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }
        // Case 4: Right-Left
        if (balance < -1 && key < node.right.key) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder() {
        inorderRec(root);
        printf("\n");
    }

    static void inorderRec(Node root) {
        if (root != NULL) {
            inorderRec(root.left);
            printf("%s", root.key + " ");
            inorderRec(root.right);
        }
    }

    int main(void) {
        AVLTreeSelfBalancing avl = new AVLTreeSelfBalancing();
        int* keys = {10, 20, 30, 40, 50, 25};

        for (size_t _idx = 0; _idx < sizeof(keys)/sizeof(keys[0]); _idx++) {
        int key = keys[_idx];
            avl.insert(key);
        }

        printf("%s", "AVL Inorder Traversal: ");
        avl.inorder();
        printf("Root key: " + avl.root.key + " (Expected: 30)\n");
        printf("Root height: " + avl.root.height + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
