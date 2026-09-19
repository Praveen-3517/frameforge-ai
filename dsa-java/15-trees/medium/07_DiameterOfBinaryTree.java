/**
 * Problem: Diameter of Binary Tree (LeetCode 543)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given the root of a binary tree, return the length of the diameter of the tree.
 * The diameter of a binary tree is the length of the longest path between any two
 * nodes in a tree. This path may or may not pass through the root.
 * The length of a path between two nodes is represented by the number of edges between them.
 * 
 * Approach:
 * Bottom-Up DFS (Post-order):
 * For every node, the longest path passing through it as the highest point is:
 *   leftSubtreeHeight + rightSubtreeHeight
 * While computing the height of each subtree recursively, update a global maximum diameter.
 * 
 * Time Complexity: O(N) visiting each node once.
 * Space Complexity: O(H) recursion stack where H is tree height.
 */
class DiameterOfBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static int maxDiameter = 0;

    public static int diameterOfBinaryTree(TreeNode root) {
        maxDiameter = 0;
        calculateHeight(root);
        return maxDiameter;
    }

    private static int calculateHeight(TreeNode node) {
        if (node == null) return 0;

        int leftHeight = calculateHeight(node.left);
        int rightHeight = calculateHeight(node.right);

        // Path length through current node is leftHeight + rightHeight
        maxDiameter = Math.max(maxDiameter, leftHeight + rightHeight);

        return 1 + Math.max(leftHeight, rightHeight);
    }

    public static void main(String[] args) {
        // [1, 2, 3, 4, 5]
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        root.left.right = new TreeNode(5);

        System.out.println("Diameter: " + diameterOfBinaryTree(root) + " (Expected: 3)");
    }
}
