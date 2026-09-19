/*
 * Problem Statement:
 * A linked list of length n is given such that each node contains an additional random pointer,
 * which could point to any node in the list, or null.
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes.
 * None of the pointers in the new list should point to nodes in the original list.
 * Return the head of the copied linked list.
 * Can you solve it in O(1) auxiliary space?
 * (LeetCode 138: Copy List with Random Pointer)
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Bloomberg
 */

class CopyListWithRandomPointer {

    static class Node {
        int val;
        Node next;
        Node random;
        Node(int val) { this.val = val; }
    }

    /**
     * Approach:
     * 3-Pass O(1) Auxiliary Space Interleaving Strategy:
     * Pass 1: Create a clone of each node and interleave it directly next to original:
     *         A -> A' -> B -> B' -> C -> C'
     * Pass 2: Assign random pointers for the copied nodes:
     *         curr.next.random = curr.random.next (if curr.random != null)
     * Pass 3: Detangle original list and cloned list.
     */
    public static Node copyRandomList(Node head) {
        if (head == null) return null;

        // Pass 1: Interleave cloned nodes
        Node curr = head;
        while (curr != null) {
            Node copy = new Node(curr.val);
            copy.next = curr.next;
            curr.next = copy;
            curr = copy.next;
        }

        // Pass 2: Set random pointers
        curr = head;
        while (curr != null) {
            if (curr.random != null) {
                curr.next.random = curr.random.next;
            }
            curr = curr.next.next;
        }

        // Pass 3: Separate original and cloned lists
        curr = head;
        Node copyHead = head.next;
        Node copyCurr = copyHead;

        while (curr != null) {
            curr.next = curr.next.next;
            curr = curr.next;

            if (copyCurr.next != null) {
                copyCurr.next = copyCurr.next.next;
                copyCurr = copyCurr.next;
            }
        }

        return copyHead;
    }

    public static void main(String[] args) {
        Node n1 = new Node(7);
        Node n2 = new Node(13);
        Node n3 = new Node(11);

        n1.next = n2;
        n2.next = n3;

        n1.random = null;
        n2.random = n1;
        n3.random = n2;

        Node clone = copyRandomList(n1);
        System.out.println("--- Copy List with Random Pointer ---");
        System.out.println("Original Head val: " + n1.val + ", Clone Head val: " + clone.val);
        System.out.println("Are heads distinct objects? " + (n1 != clone));
        System.out.println("Clone node 2 random val: " + clone.next.random.val + " (Expected: 7)");
    }
}

/*
 * Time Complexity: O(N) three linear passes.
 * Space Complexity: O(1) auxiliary space (excluding the output list).
 */
