import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Problem: Binary Tree Preorder Traversal (LeetCode 144)
 * Asked in: Google, Amazon, Microsoft
 * 
 * Given the root of a binary tree, return the preorder traversal of its nodes' values.
 * (Order: Root -> Left -> Right)
 * 
 * Approach:
 * 1. Recursive: Call root, then preorder(left), then preorder(right).
 * 2. Iterative: Use a stack. Push root. Pop node, record val, push right child first,
 *    then left child (so left is processed next).
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(H) where H is tree height for stack recursion/iteration.
 */
class BinaryTreePreorderTraversal {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> preorderTraversalIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Deque<TreeNode> stack = new ArrayDeque<>();
        stack.push(root);

        while (!stack.isEmpty()) {
            TreeNode curr = stack.pop();
            result.add(curr.val);

            // Push right first so left is popped and visited first
            if (curr.right != null) stack.push(curr.right);
            if (curr.left != null) stack.push(curr.left);
        }
        return result;
    }

    public static void main(String[] args) {
        // Tree: 1 -> right: 2 -> left: 3
        TreeNode root = new TreeNode(1);
        root.right = new TreeNode(2);
        root.right.left = new TreeNode(3);

        System.out.println("Preorder: " + preorderTraversalIterative(root) + " (Expected: [1, 2, 3])");
    }
}
