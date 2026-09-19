import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Morris In-Order Traversal with O(1) Auxiliary Space
 * Asked in: Google, Microsoft, Amazon, Bloomberg
 * 
 * Given the root of a binary tree, return its in-order traversal using O(1) auxiliary space
 * (i.e. no recursion stack and no explicit stack data structure).
 * 
 * Approach:
 * Morris Traversal (Threaded Binary Tree):
 * 1. Initialize `curr` as root.
 * 2. While `curr != null`:
 *    - If `curr.left == null`:
 *      Visit `curr` (add to result) and move `curr = curr.right`.
 *    - Else:
 *      Find in-order predecessor `prev` (rightmost node in left subtree).
 *      - If `prev.right == null`:
 *        Create temporary thread: `prev.right = curr`, then advance `curr = curr.left`.
 *      - If `prev.right == curr`:
 *        Remove temporary thread: `prev.right = null`, visit `curr`, and advance `curr = curr.right`.
 * 
 * Time Complexity: O(N) because each edge is traversed at most twice (once for threading, once for visit/unthreading).
 * Space Complexity: O(1) auxiliary space.
 */
class MorrisTraversalInorderO1Space {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> morrisInorder(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left == null) {
                result.add(curr.val);
                curr = curr.right;
            } else {
                // Find inorder predecessor
                TreeNode prev = curr.left;
                while (prev.right != null && prev.right != curr) {
                    prev = prev.right;
                }

                if (prev.right == null) {
                    // Create thread to current node
                    prev.right = curr;
                    curr = curr.left;
                } else {
                    // Thread already exists -> revert change, visit node, go right
                    prev.right = null;
                    result.add(curr.val);
                    curr = curr.right;
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        // [1, 2, 3, 4, 5]
        TreeNode root = new TreeNode(4);
        root.left = new TreeNode(2);
        root.right = new TreeNode(5);
        root.left.left = new TreeNode(1);
        root.left.right = new TreeNode(3);

        List<Integer> inorder = morrisInorder(root);
        System.out.println("Morris Inorder: " + inorder + " (Expected: [1, 2, 3, 4, 5])");
    }
}
