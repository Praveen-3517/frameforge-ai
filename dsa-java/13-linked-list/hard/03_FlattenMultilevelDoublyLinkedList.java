/*
 * Problem Statement:
 * You are given a doubly linked list, which contains nodes that have a next pointer,
 * a previous pointer, and an additional child pointer. This child pointer may or may not
 * point to a separate doubly linked list, also containing these special nodes.
 * Flatten the list so that all the nodes appear in a single-level, doubly linked list.
 * (LeetCode 430: Flatten a Multilevel Doubly Linked List)
 * 
 * Asked in: Bloomberg, Amazon, Microsoft, Apple
 */

class FlattenMultilevelDoublyLinkedList {

    static class Node {
        int val;
        Node prev;
        Node next;
        Node child;
        Node(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Iterative Pointer Splicing:
     * While iterating:
     * 1. If curr has no child, proceed to curr.next.
     * 2. If curr has a child:
     *    - Find the tail of the child branch.
     *    - Connect child tail's next to curr.next (if curr.next != null).
     *    - Connect curr.next to curr.child.
     *    - Set curr.child.prev to curr.
     *    - Clear curr.child = null.
     */
    public static Node flatten(Node head) {
        if (head == null) return null;

        Node curr = head;
        while (curr != null) {
            if (curr.child != null) {
                Node next = curr.next;

                // Find tail of child list
                Node childTail = curr.child;
                while (childTail.next != null) {
                    childTail = childTail.next;
                }

                // Splice child list in between curr and next
                curr.next = curr.child;
                curr.child.prev = curr;

                if (next != null) {
                    childTail.next = next;
                    next.prev = childTail;
                }

                curr.child = null; // Clear child pointer
            }

            curr = curr.next;
        }

        return head;
    }

    public static void main(String[] args) {
        Node n1 = new Node(1);
        Node n2 = new Node(2);
        Node n3 = new Node(3);
        n1.next = n2; n2.prev = n1;
        n2.next = n3; n3.prev = n2;

        Node c1 = new Node(7);
        Node c2 = new Node(8);
        c1.next = c2; c2.prev = c1;

        // Node 2 has child c1
        n2.child = c1;

        Node flattened = flatten(n1);
        System.out.println("--- Flattened Doubly Linked List ---");
        Node curr = flattened;
        while (curr != null) {
            System.out.print(curr.val + (curr.next != null ? " <-> " : ""));
            curr = curr.next;
        }
        System.out.println();
    }
}

/*
 * Time Complexity: O(N) where N is total nodes across all levels.
 * Space Complexity: O(1) in-place pointer stitching.
 */
