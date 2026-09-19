/**
 * Problem: Lowest Common Ancestor of a Binary Tree (LeetCode 236)
 * Asked in: Facebook, Amazon, Microsoft, Apple, Google
 * 
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * The LCA is defined between two nodes p and q as the lowest node in T that has both
 * p and q as descendants (where we allow a node to be a descendant of itself).
 * 
 * Approach:
 * Post-order recursive DFS:
 * 1. Base case: if root is null, or root == p, or root == q, return root.
 * 2. Recurse on left and right subtrees.
 * 3. If left != null && right != null, both targets were found in distinct subtrees;
 *    hence current root is their lowest common ancestor!
 * 4. Otherwise, return the non-null child (left != null ? left : right).
 * 
 * Time Complexity: O(N) visiting each node at most once.
 * Space Complexity: O(H) call stack where H is tree height.
 */
class LowestCommonAncestorBT {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q) {
            return root;
        }

        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);

        if (left != null && right != null) {
            return root;
        }

        return left != null ? left : right;
    }

    public static void main(String[] args) {
        // [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);

        TreeNode lca1 = lowestCommonAncestor(root, root.left, root.right); // LCA(5, 1) = 3
        System.out.println("LCA(5, 1): " + (lca1 != null ? lca1.val : "null") + " (Expected: 3)");

        TreeNode lca2 = lowestCommonAncestor(root, root.left, root.left.right.right); // LCA(5, 4) = 5
        System.out.println("LCA(5, 4): " + (lca2 != null ? lca2.val : "null") + " (Expected: 5)");
    }
}
