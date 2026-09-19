/**
 * Problem: Path Sum (LeetCode 112)
 * Asked in: Amazon, Microsoft, Facebook, Oracle
 * 
 * Given the root of a binary tree and an integer targetSum, return true if the tree
 * has a root-to-leaf path such that adding up all the values along the path equals targetSum.
 * A leaf is a node with no children.
 * 
 * Approach:
 * Recursive DFS:
 * - If root == null, return false.
 * - If root is a leaf (left == null && right == null), check if root.val == targetSum.
 * - Recurse on left and right with remaining sum: targetSum - root.val.
 * 
 * Time Complexity: O(N) visiting each node at most once.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class PathSumRootToLeaf {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static boolean hasPathSum(TreeNode root, int targetSum) {
        if (root == null) return false;

        // Check if current node is a leaf
        if (root.left == null && root.right == null) {
            return targetSum == root.val;
        }

        int remainingSum = targetSum - root.val;
        return hasPathSum(root.left, remainingSum) || hasPathSum(root.right, remainingSum);
    }

    public static void main(String[] args) {
        // [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1]
        TreeNode root = new TreeNode(5);
        root.left = new TreeNode(4);
        root.right = new TreeNode(8);
        root.left.left = new TreeNode(11);
        root.left.left.left = new TreeNode(7);
        root.left.left.right = new TreeNode(2);
        root.right.left = new TreeNode(13);
        root.right.right = new TreeNode(4);
        root.right.right.right = new TreeNode(1);

        System.out.println("Path sum 22: " + hasPathSum(root, 22) + " (Expected: true)");
        System.out.println("Path sum 26: " + hasPathSum(root, 26) + " (Expected: true)");
        System.out.println("Path sum 50: " + hasPathSum(root, 50) + " (Expected: false)");
    }
}
