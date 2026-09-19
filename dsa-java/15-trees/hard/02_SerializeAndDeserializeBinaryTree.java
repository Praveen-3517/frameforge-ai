import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

/**
 * Problem: Serialize and Deserialize Binary Tree (LeetCode 297)
 * Asked in: Facebook, Amazon, Google, Microsoft, Uber
 * 
 * Design an algorithm to serialize and deserialize a binary tree.
 * There is no restriction on how your serialization/deserialization algorithm
 * should work. You just need to ensure that a binary tree can be serialized
 * to a string and this string can be deserialized to the original tree structure.
 * 
 * Approach:
 * Pre-order Traversal (DFS):
 * - Serialize:
 *   If node is null, append "#,".
 *   Otherwise, append node.val + "," followed by serialize(node.left) and serialize(node.right).
 * - Deserialize:
 *   Split string by "," into a Queue/Deque.
 *   Poll token: if "#", return null.
 *   Otherwise create TreeNode(Integer.parseInt(token)), then left = build(), right = build().
 * 
 * Time Complexity: O(N) for both serialization and deserialization.
 * Space Complexity: O(N) for recursion and string storage.
 */
class SerializeAndDeserializeBinaryTree {

    static class TreeNode {
        int val;
        TreeNode left, right;
        TreeNode(int val) { this.val = val; }
    }

    private static final String NULL_NODE = "#";
    private static final String DELIMITER = ",";

    // Encodes a tree to a single string.
    public static String serialize(TreeNode root) {
        StringBuilder sb = new StringBuilder();
        serializeHelper(root, sb);
        return sb.toString();
    }

    private static void serializeHelper(TreeNode node, StringBuilder sb) {
        if (node == null) {
            sb.append(NULL_NODE).append(DELIMITER);
            return;
        }
        sb.append(node.val).append(DELIMITER);
        serializeHelper(node.left, sb);
        serializeHelper(node.right, sb);
    }

    // Decodes your encoded data to tree.
    public static TreeNode deserialize(String data) {
        Deque<String> nodes = new ArrayDeque<>(Arrays.asList(data.split(DELIMITER)));
        return deserializeHelper(nodes);
    }

    private static TreeNode deserializeHelper(Deque<String> nodes) {
        if (nodes.isEmpty()) return null;
        String val = nodes.poll();
        if (val.equals(NULL_NODE)) return null;

        TreeNode node = new TreeNode(Integer.parseInt(val));
        node.left = deserializeHelper(nodes);
        node.right = deserializeHelper(nodes);
        return node;
    }

    static void printInorder(TreeNode root) {
        if (root == null) return;
        printInorder(root.left);
        System.out.print(root.val + " ");
        printInorder(root.right);
    }

    public static void main(String[] args) {
        // [1, 2, 3, null, null, 4, 5]
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(5);

        String serialized = serialize(root);
        System.out.println("Serialized: " + serialized);

        TreeNode deserialized = deserialize(serialized);
        System.out.print("Deserialized Inorder: ");
        printInorder(deserialized);
        System.out.println();
    }
}
