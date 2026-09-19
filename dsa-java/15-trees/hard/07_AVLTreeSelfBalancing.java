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
class AVLTreeSelfBalancing {

    static class Node {
        int key, height;
        Node left, right;

        Node(int key) {
            this.key = key;
            this.height = 1;
        }
    }

    private Node root;

    private int height(Node n) {
        return n == null ? 0 : n.height;
    }

    private int getBalance(Node n) {
        return n == null ? 0 : height(n.left) - height(n.right);
    }

    private Node rightRotate(Node y) {
        Node x = y.left;
        Node t2 = x.right;

        // Perform rotation
        x.right = y;
        y.left = t2;

        // Update heights
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;

        return x;
    }

    private Node leftRotate(Node x) {
        Node y = x.right;
        Node t2 = y.left;

        // Perform rotation
        y.left = x;
        x.right = t2;

        // Update heights
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        y.height = Math.max(height(y.left), height(y.right)) + 1;

        return y;
    }

    public void insert(int key) {
        root = insertRec(root, key);
    }

    private Node insertRec(Node node, int key) {
        if (node == null) return new Node(key);

        if (key < node.key) {
            node.left = insertRec(node.left, key);
        } else if (key > node.key) {
            node.right = insertRec(node.right, key);
        } else {
            return node; // Duplicate keys not allowed
        }

        // Update height
        node.height = 1 + Math.max(height(node.left), height(node.right));

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

    public void inorder() {
        inorderRec(root);
        System.out.println();
    }

    private void inorderRec(Node root) {
        if (root != null) {
            inorderRec(root.left);
            System.out.print(root.key + " ");
            inorderRec(root.right);
        }
    }

    public static void main(String[] args) {
        AVLTreeSelfBalancing avl = new AVLTreeSelfBalancing();
        int[] keys = {10, 20, 30, 40, 50, 25};

        for (int key : keys) {
            avl.insert(key);
        }

        System.out.print("AVL Inorder Traversal: ");
        avl.inorder();
        System.out.println("Root key: " + avl.root.key + " (Expected: 30)");
        System.out.println("Root height: " + avl.root.height + " (Expected: 3)");
    }
}
