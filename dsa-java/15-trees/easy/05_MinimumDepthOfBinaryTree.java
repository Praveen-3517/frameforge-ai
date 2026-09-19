/**
 * Problem: Minimum Depth of Binary Tree (LeetCode 111)
 * Asked in: Facebook, Amazon, Bloomberg
 * 
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the
 * root node down to the nearest leaf node (a node with no children).
 * 
 * Approach:
 * If a node has only one child, we cannot consider the null path as depth 0!
 * We must continue down the non-null child's path.
 * - If root == null, return 0.
 * - If left is null, return 1 + minDepth(right).
 * - If right is null, return 1 + minDepth(left).
 * - Otherwise return 1 + min(minDepth(left), minDepth(right)).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) recursion stack.
 */
class MinimumDepthOfBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static int minDepth(TreeNode root) {
        if (root == null) return 0;
        if (root.left == null) return 1 + minDepth(root.right);
        if (root.right == null) return 1 + minDepth(root.left);
        return 1 + Math.min(minDepth(root.left), minDepth(root.right));
    }

    public static void main(String[] args) {
        // [3, 9, 20, null, null, 15, 7]
        TreeNode root1 = new TreeNode(3);
        root1.left = new TreeNode(9);
        root1.right = new TreeNode(20);
        root1.right.left = new TreeNode(15);
        root1.right.right = new TreeNode(7);

        System.out.println("Min Depth 1: " + minDepth(root1) + " (Expected: 2)");

        // Skewed tree: 2 -> 3 -> 4 -> 5 -> 6
        TreeNode root2 = new TreeNode(2);
        root2.right = new TreeNode(3);
        root2.right.right = new TreeNode(4);
        root2.right.right.right = new TreeNode(5);
        root2.right.right.right.right = new TreeNode(6);

        System.out.println("Min Depth 2: " + minDepth(root2) + " (Expected: 5)");
    }
}
