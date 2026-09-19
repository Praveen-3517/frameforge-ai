/**
 * Problem: Search in a Binary Search Tree (LeetCode 700)
 * Asked in: Amazon, Adobe, Microsoft
 * 
 * You are given the root of a binary search tree (BST) and an integer val.
 * Find the node in the BST that the node's value equals val and return the
 * subtree rooted with that node. If such a node does not exist, return null.
 * 
 * Approach:
 * BST Property:
 * - If target val < root.val, search in left subtree.
 * - If target val > root.val, search in right subtree.
 * - If target val == root.val, return root.
 * Can be solved iteratively in O(1) extra space!
 * 
 * Time Complexity: O(H) where H is tree height (O(log N) for balanced BST, O(N) worst case).
 * Space Complexity: O(1) auxiliary space using iterative search.
 */
class SearchInBinarySearchTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static TreeNode searchBST(TreeNode root, int val) {
        TreeNode curr = root;
        while (curr != null && curr.val != val) {
            if (val < curr.val) {
                curr = curr.left;
            } else {
                curr = curr.right;
            }
        }
        return curr;
    }

    public static void main(String[] args) {
        // BST: [4, 2, 7, 1, 3]
        TreeNode root = new TreeNode(4);
        root.left = new TreeNode(2);
        root.right = new TreeNode(7);
        root.left.left = new TreeNode(1);
        root.left.right = new TreeNode(3);

        TreeNode result2 = searchBST(root, 2);
        System.out.println("Search 2: " + (result2 != null ? result2.val : "null") + " (Expected: 2)");

        TreeNode result5 = searchBST(root, 5);
        System.out.println("Search 5: " + (result5 != null ? result5.val : "null") + " (Expected: null)");
    }
}
