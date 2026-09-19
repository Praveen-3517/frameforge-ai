import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Binary Tree Right Side View (LeetCode 199)
 * Asked in: Facebook, Amazon, Bloomberg, Microsoft
 * 
 * Given the root of a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 * 
 * Approach:
 * Level-Order Traversal (BFS):
 * In each level of BFS, the last node processed in that level is the rightmost visible node.
 * Add that last node to our result list.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(W) where W is maximum width of tree.
 */
class BinaryTreeRightSideView {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) return result;

        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode curr = queue.poll();
                // If it is the last node in the current level, record it
                if (i == levelSize - 1) {
                    result.add(curr.val);
                }
                if (curr.left != null) queue.offer(curr.left);
                if (curr.right != null) queue.offer(curr.right);
            }
        }

        return result;
    }

    public static void main(String[] args) {
        // [1, 2, 3, null, 5, null, 4]
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(4);

        System.out.println("Right Side View: " + rightSideView(root) + " (Expected: [1, 3, 4])");
    }
}
