/**
 * Problem: Binary Tree Maximum Path Sum (LeetCode 124)
 * Asked in: Facebook, Google, Amazon, Microsoft, ByteDance
 * 
 * A path in a binary tree is a sequence of nodes where each pair of adjacent nodes
 * has an edge connecting them. A node can only appear in the sequence at most once.
 * The path sum is the sum of the node's values in the path.
 * Given the root of a binary tree, return the maximum path sum of any non-empty path.
 * 
 * Approach:
 * Post-order DFS:
 * For each node:
 * - Recursively find max path gain from left and right children (clamped to >= 0).
 * - Max path sum passing THROUGH current node as turning point:
 *     node.val + leftGain + rightGain.
 * - Update global maximum.
 * - Return to parent: node.val + max(leftGain, rightGain) (since a path cannot branch to both children if extending to parent).
 * 
 * Time Complexity: O(N) visiting each node once.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class BinaryTreeMaximumPathSum {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static int globalMax;

    public static int maxPathSum(TreeNode root) {
        globalMax = Integer.MIN_VALUE;
        maxGain(root);
        return globalMax;
    }

    private static int maxGain(TreeNode node) {
        if (node == null) return 0;

        // If gain is negative, ignore that branch (take 0)
        int leftGain = Math.max(0, maxGain(node.left));
        int rightGain = Math.max(0, maxGain(node.right));

        // Price of the path where current node is the highest point
        int currentPathSum = node.val + leftGain + rightGain;
        globalMax = Math.max(globalMax, currentPathSum);

        // Return max single branch gain to parent
        return node.val + Math.max(leftGain, rightGain);
    }

    public static void main(String[] args) {
        // [-10, 9, 20, null, null, 15, 7]
        TreeNode root = new TreeNode(-10);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        System.out.println("Max Path Sum: " + maxPathSum(root) + " (Expected: 42)");
        // Path: 15 -> 20 -> 7 = 42
    }
}
