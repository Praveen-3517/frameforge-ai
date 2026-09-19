import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem: Kth Smallest Element in a BST (LeetCode 230)
 * Asked in: Amazon, Facebook, Google, Microsoft, Uber
 * 
 * Given the root of a binary search tree, and an integer k, return the kth
 * smallest value (1-indexed) of all the values of the nodes in the tree.
 * 
 * Approach:
 * In-Order Traversal (Left -> Root -> Right):
 * BST in-order produces elements in strictly ascending order.
 * Using an iterative in-order traversal with a stack:
 * Traverse leftwards, pop node, decrement k.
 * When k reaches 0, the current popped node is the k-th smallest element!
 * 
 * Time Complexity: O(H + k) where H is tree height.
 * Space Complexity: O(H) for traversal stack.
 */
class KthSmallestElementInBST {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static int kthSmallest(TreeNode root, int k) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode curr = root;

        while (curr != null || !stack.isEmpty()) {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }

            curr = stack.pop();
            k--;
            if (k == 0) {
                return curr.val;
            }

            curr = curr.right;
        }

        return -1;
    }

    public static void main(String[] args) {
        // [3, 1, 4, null, 2]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(1);
        root.right = new TreeNode(4);
        root.left.right = new TreeNode(2);

        System.out.println("1st smallest: " + kthSmallest(root, 1) + " (Expected: 1)");
        System.out.println("2nd smallest: " + kthSmallest(root, 2) + " (Expected: 2)");
        System.out.println("3rd smallest: " + kthSmallest(root, 3) + " (Expected: 3)");
    }
}
