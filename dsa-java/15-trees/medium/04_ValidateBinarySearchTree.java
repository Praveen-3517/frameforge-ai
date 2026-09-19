/**
 * Problem: Validate Binary Search Tree (LeetCode 98)
 * Asked in: Amazon, Bloomberg, Microsoft, Facebook, Apple
 * 
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 * A valid BST is defined as:
 * - The left subtree of a node contains only nodes with keys strictly less than the node's key.
 * - The right subtree of a node contains only nodes with keys strictly greater than the node's key.
 * - Both the left and right subtrees must also be binary search trees.
 * 
 * Approach:
 * Range DFS with Long bounds:
 * Pass allowable range [minVal, maxVal] for each node.
 * - For root: (-infinity, +infinity).
 * - For left child of node: (minVal, node.val).
 * - For right child of node: (node.val, maxVal).
 * - If current node value not in (minVal, maxVal), return false.
 * 
 * Time Complexity: O(N) visiting each node once.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class ValidateBinarySearchTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static boolean isValidBST(TreeNode root) {
        return validate(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }

    private static boolean validate(TreeNode node, long minVal, long maxVal) {
        if (node == null) return true;

        if (node.val <= minVal || node.val >= maxVal) {
            return false;
        }

        return validate(node.left, minVal, node.val) 
            && validate(node.right, node.val, maxVal);
    }

    public static void main(String[] args) {
        // Valid BST: [2, 1, 3]
        TreeNode root1 = new TreeNode(2);
        root1.left = new TreeNode(1);
        root1.right = new TreeNode(3);
        System.out.println("Tree 1 Valid: " + isValidBST(root1) + " (Expected: true)");

        // Invalid BST: [5, 1, 4, null, null, 3, 6]
        TreeNode root2 = new TreeNode(5);
        root2.left = new TreeNode(1);
        root2.right = new TreeNode(4);
        root2.right.left = new TreeNode(3);
        root2.right.right = new TreeNode(6);
        System.out.println("Tree 2 Valid: " + isValidBST(root2) + " (Expected: false)");
    }
}
