/**
 * Problem: Invert Binary Tree (LeetCode 226)
 * Asked in: Google, Amazon, Twitter, Microsoft
 * 
 * Given the root of a binary tree, invert the tree (mirror reflection) and return its root.
 * 
 * Approach:
 * Recursively invert left and right subtrees, then swap the left and right pointers.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) call stack where H is tree height.
 */
class InvertBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static TreeNode invertTree(TreeNode root) {
        if (root == null) return null;

        TreeNode left = invertTree(root.left);
        TreeNode right = invertTree(root.right);

        root.left = right;
        root.right = left;

        return root;
    }

    // Helper to print inorder
    static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }

    public static void main(String[] args) {
        // Tree: 4, left: 2 (1, 3), right: 7 (6, 9)
        TreeNode root = new TreeNode(4);
        root.left = new TreeNode(2);
        root.right = new TreeNode(7);
        root.left.left = new TreeNode(1);
        root.left.right = new TreeNode(3);
        root.right.left = new TreeNode(6);
        root.right.right = new TreeNode(9);

        System.out.print("Original Inorder: ");
        printInorder(root);
        System.out.println();

        TreeNode inverted = invertTree(root);

        System.out.print("Inverted Inorder: ");
        printInorder(inverted);
        System.out.println();
    }
}
