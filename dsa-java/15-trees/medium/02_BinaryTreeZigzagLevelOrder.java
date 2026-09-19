import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Binary Tree Zigzag Level Order Traversal (LeetCode 103)
 * Asked in: Amazon, Microsoft, Facebook, Bloomberg
 * 
 * Given the root of a binary tree, return the zigzag level order traversal of its nodes'
 * values. (i.e., from left to right, then right to left for the next level and alternate between).
 * 
 * Approach:
 * BFS with LinkedList / Deque for each level:
 * - Maintain a boolean flag `leftToRight`.
 * - For each level, if leftToRight is true, append values to the back (`addLast`).
 * - If false, prepend values to the front (`addFirst`).
 * - Invert flag after each level.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is maximum width of the tree.
 */
class BinaryTreeZigzagLevelOrder {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);
        boolean leftToRight = true;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            LinkedList<Integer> currentLevel = new LinkedList<>();

            for (int i = 0; i < levelSize; i++) {
                TreeNode curr = queue.poll();
                if (leftToRight) {
                    currentLevel.addLast(curr.val);
                } else {
                    currentLevel.addFirst(curr.val);
                }

                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }

            result.add(currentLevel);
            leftToRight = !leftToRight;
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

        System.out.println("Zigzag: " + zigzagLevelOrder(root));
        // Expected: [[3], [20, 9], [15, 7]]
    }
}
