import java.util.HashMap;
import java.util.Map;

/**
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal (LeetCode 105)
 * Asked in: Amazon, Microsoft, Facebook, Google, Bloomberg
 * 
 * Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same tree,
 * construct and return the binary tree.
 * 
 * Approach:
 * - Preorder provides the ROOT at the current subtree's starting index.
 * - Inorder splits nodes into LEFT subtree (left of root) and RIGHT subtree (right of root).
 * - Precompute inorder indices in a HashMap for O(1) lookup.
 * - Recursively construct left subtree and right subtree with accurate sub-array boundaries.
 * 
 * Time Complexity: O(N) where N is number of nodes.
 * Space Complexity: O(N) for hash map and recursion stack.
 */
class ConstructTreeFromPreorderInorder {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static Map<Integer, Integer> inorderIndexMap;
    private static int preorderIndex;

    public static TreeNode buildTree(int[] preorder, int[] inorder) {
        inorderIndexMap = new HashMap<>();
        preorderIndex = 0;

        for (int i = 0; i < inorder.length; i++) {
            inorderIndexMap.put(inorder[i], i);
        }

        return buildSubtree(preorder, 0, inorder.length - 1);
    }

    private static TreeNode buildSubtree(int[] preorder, int inStart, int inEnd) {
        if (inStart > inEnd) return null;

        int rootVal = preorder[preorderIndex++];
        TreeNode root = new TreeNode(rootVal);

        int rootIndexInorder = inorderIndexMap.get(rootVal);

        // Build left subtree with elements before root in inorder
        root.left = buildSubtree(preorder, inStart, rootIndexInorder - 1);
        // Build right subtree with elements after root in inorder
        root.right = buildSubtree(preorder, rootIndexInorder + 1, inEnd);

        return root;
    }

    static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }

    public static void main(String[] args) {
        int[] preorder = {3, 9, 20, 15, 7};
        int[] inorder = {9, 3, 15, 20, 7};

        TreeNode root = buildTree(preorder, inorder);
        System.out.print("Reconstructed Inorder: ");
        printInorder(root);
        System.out.println();
    }
}
