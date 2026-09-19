/**
 * Problem: Symmetric Tree (LeetCode 101)
 * Asked in: Amazon, Microsoft, Bloomberg, Apple
 * 
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 * 
 * Approach:
 * Helper function isMirror(t1, t2):
 * - If both null -> true.
 * - If one null -> false.
 * - Return (t1.val == t2.val) && isMirror(t1.left, t2.right) && isMirror(t1.right, t2.left).
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class SymmetricTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static boolean isSymmetric(TreeNode root) {
        if (root == null) return true;
        return isMirror(root.left, root.right);
    }

    private static boolean isMirror(TreeNode t1, TreeNode t2) {
        if (t1 == null && t2 == null) return true;
        if (t1 == null || t2 == null) return false;
        return (t1.val == t2.val) 
            && isMirror(t1.left, t2.right) 
            && isMirror(t1.right, t2.left);
    }

    public static void main(String[] args) {
        // [1, 2, 2, 3, 4, 4, 3] -> Symmetric
        TreeNode root1 = new TreeNode(1);
        root1.left = new TreeNode(2);
        root1.right = new TreeNode(2);
        root1.left.left = new TreeNode(3);
        root1.left.right = new TreeNode(4);
        root1.right.left = new TreeNode(4);
        root1.right.right = new TreeNode(3);

        System.out.println("Tree 1 Symmetric: " + isSymmetric(root1) + " (Expected: true)");

        // [1, 2, 2, null, 3, null, 3] -> Not symmetric
        TreeNode root2 = new TreeNode(1);
        root2.left = new TreeNode(2);
        root2.right = new TreeNode(2);
        root2.left.right = new TreeNode(3);
        root2.right.right = new TreeNode(3);

        System.out.println("Tree 2 Symmetric: " + isSymmetric(root2) + " (Expected: false)");
    }
}
