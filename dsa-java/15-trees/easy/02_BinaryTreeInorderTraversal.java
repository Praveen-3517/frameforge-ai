import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Problem: Binary Tree Inorder Traversal (LeetCode 94)
 * Asked in: Amazon, Microsoft, Adobe
 * 
 * Given the root of a binary tree, return the inorder traversal of its nodes' values.
 * (Order: Left -> Root -> Right)
 * 
 * Approach:
 * Iterative using Stack:
 * 1. Initialize current node as root.
 * 2. Push current node and go left until current is null.
 * 3. Pop from stack, add to result, and set current = popped.right.
 * 4. Repeat until stack is empty and current is null.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(H) where H is height of the tree.
 */
class BinaryTreeInorderTraversal {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode curr = root;

        while (curr != null || !stack.isEmpty()) {
            while (curr != null) {
                stack.push(curr);
                curr = curr.left;
            }
            curr = stack.pop();
            result.add(curr.val);
            curr = curr.right;
        }

        return result;
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(1);
        root.right = new TreeNode(2);
        root.right.left = new TreeNode(3);

        System.out.println("Inorder: " + inorderTraversal(root) + " (Expected: [1, 3, 2])");
    }
}
