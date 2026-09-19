import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

/**
 * Problem: All Nodes Distance K in Binary Tree (LeetCode 863)
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * Given the root of a binary tree, a target node, and an integer k, return an array
 * of the values of all nodes that have a distance k from the target node.
 * 
 * Approach:
 * 1. Tree to Graph Conversion:
 *    Traverse tree with DFS/BFS to populate a Map<TreeNode, TreeNode> parentMap,
 *    enabling bidirectional movement (to left, to right, and to parent).
 * 2. BFS from Target:
 *    Start standard BFS queue at `target` with distance = 0 and a visited set.
 *    Expand outward layer by layer until distance == k.
 *    The queue contents at distance k are the answer!
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(N) for parent map and BFS queue/set.
 */
class AllNodesDistanceKInBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        Map<TreeNode, TreeNode> parentMap = new HashMap<>();
        buildParentMap(root, null, parentMap);

        Queue<TreeNode> queue = new ArrayDeque<>();
        Set<TreeNode> visited = new HashSet<>();

        queue.offer(target);
        visited.add(target);
        int currentDistance = 0;

        while (!queue.isEmpty()) {
            if (currentDistance == k) {
                List<Integer> result = new ArrayList<>();
                for (TreeNode node : queue) {
                    result.add(node.val);
                }
                return result;
            }

            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();

                // Explore left
                if (curr.left != null && !visited.contains(curr.left)) {
                    visited.add(curr.left);
                    queue.offer(curr.left);
                }
                // Explore right
                if (curr.right != null && !visited.contains(curr.right)) {
                    visited.add(curr.right);
                    queue.offer(curr.right);
                }
                // Explore parent
                TreeNode parent = parentMap.get(curr);
                if (parent != null && !visited.contains(parent)) {
                    visited.add(parent);
                    queue.offer(parent);
                }
            }
            currentDistance++;
        }

        return new ArrayList<>();
    }

    private static void buildParentMap(TreeNode node, TreeNode parent, Map<TreeNode, TreeNode> map) {
        if (node == null) return;
        if (parent != null) map.put(node, parent);
        buildParentMap(node.left, node, map);
        buildParentMap(node.right, node, map);
    }

    public static void main(String[] args) {
        // [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);

        TreeNode target = root.left; // Node 5
        int k = 2;

        List<Integer> result = distanceK(root, target, k);
        System.out.println("Distance 2 nodes: " + result);
        // Expected: [7, 4, 1]
    }
}
