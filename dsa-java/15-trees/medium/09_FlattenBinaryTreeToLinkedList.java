/**
 * Problem: Flatten Binary Tree to Linked List (LeetCode 114)
 * Asked in: Facebook, Amazon, Microsoft, Bloomberg
 * 
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * - The "linked list" should use the same TreeNode class where the right child pointer
 *   points to the next node and left child pointer is always null.
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 * 
 * Approach:
 * Morris-like Pointer Rewiring (O(1) Auxiliary Space):
 * - For current node:
 *   - If current has a left child:
 *     - Find the rightmost node of the left subtree (inorder predecessor).
 *     - Connect the rightmost node's right pointer to current's right child.
 *     - Move current.left to current.right, and set current.left = null.
 *   - Move current to current.right.
 * 
 * Time Complexity: O(N) since each edge is traversed at most twice.
 * Space Complexity: O(1) auxiliary space (in-place modification).
 */
class FlattenBinaryTreeToLinkedList {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    public static void flatten(TreeNode root) {
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left != null) {
                // Find rightmost node in left subtree
                TreeNode prev = curr.left;
                while (prev.right != null) {
                    prev = prev.right;
                }

                // Connect predecessor's right to current's right
                prev.right = curr.right;
                // Move left subtree to right
                curr.right = curr.left;
                curr.left = null;
            }
            // Advance to next node on right
            curr = curr.right;
        }
    }

    public static void main(String[] args) {
        // [1, 2, 5, 3, 4, null, 6]
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(5);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(4);
        root.right.right = new TreeNode(6);

        flatten(root);

        System.out.print("Flattened List: ");
        TreeNode curr = root;
        while (curr != null) {
            System.out.print(curr.val + (curr.right != null ? " -> " : ""));
            curr = curr.right;
        }
        System.out.println();
        // Expected: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    }
}
