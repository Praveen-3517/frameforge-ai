import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * Problem: Vertical Order Traversal of a Binary Tree (LeetCode 987)
 * Asked in: Facebook, Amazon, Google, Bloomberg
 * 
 * Given the root of a binary tree, calculate the vertical order traversal.
 * For each node at (row, col):
 * - Left child is at (row + 1, col - 1)
 * - Right child is at (row + 1, col + 1)
 * 
 * Sort criteria:
 * 1. By column (left to right)
 * 2. Within same column, by row (top to bottom)
 * 3. Within same column and row, by value ascending
 * 
 * Approach:
 * DFS with TreeMap:
 * - Map: col -> (row -> List of values)
 * - Sort the list of values for matching (col, row) before appending to output.
 * 
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(N) to store node coordinates and values.
 */
class VerticalOrderTraversalBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static Map<Integer, Map<Integer, List<Integer>>> map;

    public static List<List<Integer>> verticalTraversal(TreeNode root) {
        map = new TreeMap<>();
        dfs(root, 0, 0);

        List<List<Integer>> result = new ArrayList<>();
        for (Map<Integer, List<Integer>> rowMap : map.values()) {
            List<Integer> colResult = new ArrayList<>();
            for (List<Integer> list : rowMap.values()) {
                Collections.sort(list);
                colResult.addAll(list);
            }
            result.add(colResult);
        }

        return result;
    }

    private static void dfs(TreeNode node, int row, int col) {
        if (node == null) return;

        map.putIfAbsent(col, new TreeMap<>());
        map.get(col).putIfAbsent(row, new ArrayList<>());
        map.get(col).get(row).add(node.val);

        dfs(node.left, row + 1, col - 1);
        dfs(node.right, row + 1, col + 1);
    }

    public static void main(String[] args) {
        // [3, 9, 20, null, null, 15, 7]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);

        System.out.println("Vertical Traversal: " + verticalTraversal(root));
        // Expected: [[9], [3, 15], [20], [7]]
    }
}
