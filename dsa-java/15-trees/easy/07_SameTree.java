/**
 * Problem: Same Tree (LeetCode 100)
 * Asked in: Amazon, Google, Bloomberg
 * 
 * Given the roots of two binary trees p and q, write a function to check if they
 * are the same or not. Two binary trees are considered the same if they are
 * structurally identical, and the nodes have the same value.
 * 
 * Approach:
 * Recursive DFS:
 * - If both nodes are null, return true.
 * - If only one is null or values differ, return false.
 * - Return isSameTree(p.left, q.left) && isSameTree(p.right, q.right).
 * 
 * Time Complexity: O(min(N, M)) where N, M are number of nodes.
 * Space Complexity: O(min(H1, H2)) stack space.
 */
class SameTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static boolean isSameTree(TreeNode p, TreeNode q) {
        if (p == null && q == null) return true;
        if (p == null || q == null) return false;
        if (p.val != q.val) return false;

        return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }

    public static void main(String[] args) {
        // Tree p: [1, 2, 3]
        TreeNode p = new TreeNode(1);
        p.left = new TreeNode(2);
        p.right = new TreeNode(3);

        // Tree q: [1, 2, 3]
        TreeNode q = new TreeNode(1);
        q.left = new TreeNode(2);
        q.right = new TreeNode(3);

        System.out.println("Are trees equal: " + isSameTree(p, q) + " (Expected: true)");

        TreeNode r = new TreeNode(1);
        r.left = new TreeNode(2); // right is null

        System.out.println("Are trees equal: " + isSameTree(p, r) + " (Expected: false)");
    }
}
