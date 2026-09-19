/**
 * Problem: Maximum Depth of Binary Tree (LeetCode 104)
 * Asked in: Amazon, Apple, Microsoft, Google
 * 
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 * 
 * Approach:
 * Depth-First Search (DFS) Recursion:
 * - Base case: if root is null, depth is 0.
 * - Recursive step: maxDepth(root) = 1 + max(maxDepth(root.left), maxDepth(root.right)).
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class MaximumDepthOfBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static int maxDepth(TreeNode root) {
        if (root == null) return 0;
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }

    public static void main(String[] args) {
        // [3, 9, 20, null, null, 15, 7]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        System.out.println("Max Depth: " + maxDepth(root) + " (Expected: 3)");
    }
}
