/**
 * Problem: Binary Tree Cameras (LeetCode 968)
 * Asked in: Google, Amazon, Microsoft
 * 
 * You are given the root of a binary tree. We install cameras on the tree nodes where
 * each camera can monitor its parent, itself, and its immediate children.
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 * 
 * Approach:
 * Greedy Bottom-Up DFS (Post-order):
 * Never place cameras on leaf nodes if avoidable; place cameras on parents of leaves!
 * Define 3 states:
 * - 0: NOT_COVERED (Node is not monitored by any camera)
 * - 1: HAS_CAMERA (A camera is installed at this node)
 * - 2: COVERED (Node is safely monitored by one of its children)
 * 
 * Logic:
 * - Null nodes are considered COVERED (2).
 * - If either child is NOT_COVERED (0): Current node MUST place a camera (return 1, cameras++).
 * - Else if either child HAS_CAMERA (1): Current node is now COVERED (return 2).
 * - Else (both children are COVERED): Current node is NOT_COVERED (return 0).
 * - Edge case: If root is NOT_COVERED after traversal, install one camera at root.
 * 
 * Time Complexity: O(N) visiting each node once.
 * Space Complexity: O(H) recursion stack.
 */
class BinaryTreeCameras {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static int cameraCount;

    public static int minCameraCover(TreeNode root) {
        cameraCount = 0;
        if (dfs(root) == 0) {
            cameraCount++;
        }
        return cameraCount;
    }

    private static int dfs(TreeNode node) {
        if (node == null) return 2; // null nodes are considered covered

        int leftState = dfs(node.left);
        int rightState = dfs(node.right);

        // If any child is not covered, we must place a camera here
        if (leftState == 0 || rightState == 0) {
            cameraCount++;
            return 1;
        }

        // If any child has a camera, this node is covered
        if (leftState == 1 || rightState == 1) {
            return 2;
        }

        // Both children are covered, so this node is not covered yet
        return 0;
    }

    public static void main(String[] args) {
        // [0, 0, null, 0, 0]
        TreeNode root = new TreeNode(0);
        root.left = new TreeNode(0);
        root.left.left = new TreeNode(0);
        root.left.right = new TreeNode(0);

        System.out.println("Min cameras: " + minCameraCover(root) + " (Expected: 1)");
    }
}
