import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Binary Tree Level Order Traversal (LeetCode 102)
 * Asked in: Amazon, Microsoft, Facebook, Google, Bloomberg
 * 
 * Given the root of a binary tree, return the level order traversal of its nodes'
 * values (i.e., from left to right, level by level).
 * 
 * Approach:
 * Breadth-First Search (BFS) using a FIFO Queue:
 * 1. If root is null, return empty list.
 * 2. Enqueue root.
 * 3. While queue is not empty, get current level size = queue.size().
 * 4. Iterate 'size' times: dequeue node, record its value, enqueue left & right children if non-null.
 * 5. Append current level list to final result.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is max width of tree (up to N/2 in complete binary tree).
 */
class BinaryTreeLevelOrderTraversal {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            List<Integer> currentLevel = new ArrayList<>(levelSize);

            for (int i = 0; i < levelSize; i++) {
                TreeNode curr = queue.poll();
                currentLevel.add(curr.val);

                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }
            result.add(currentLevel);
        }

        return result;
    }

    public static void main(String[] args) {
        // [3, 9, 20, null, null, 15, 7]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        System.out.println("Level Order: " + levelOrder(root));
        // Expected: [[3], [9, 20], [15, 7]]
    }
}
