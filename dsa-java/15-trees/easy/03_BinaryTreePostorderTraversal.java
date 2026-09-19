import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Deque;
import java.util.List;

/**
 * Problem: Binary Tree Postorder Traversal (LeetCode 145)
 * Asked in: Facebook, Amazon, Google
 * 
 * Given the root of a binary tree, return the postorder traversal of its nodes' values.
 * (Order: Left -> Right -> Root)
 * 
 * Approach:
 * Iterative using modified preorder:
 * Standard preorder is Root -> Left -> Right.
 * If we traverse Root -> Right -> Left, and then reverse the entire output list,
 * we get Left -> Right -> Root (exact postorder sequence)!
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) where H is tree height.
 */
class BinaryTreePostorderTraversal {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();
            result.add(curr.val);

            // Push left first so right is processed first (Root -> Right -> Left)
            if (curr.left != null) stack.push(curr.left);
            if (curr.right != null) stack.push(curr.right);
        }

        Collections.reverse(result);
        return result;
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(1);
        root.right = new TreeNode(2);
        root.right.left = new TreeNode(3);

        System.out.println("Postorder: " + postorderTraversal(root) + " (Expected: [3, 2, 1])");
    }
}
