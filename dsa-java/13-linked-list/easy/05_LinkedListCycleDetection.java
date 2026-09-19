/*
 * Problem Statement:
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached
 * again by continuously following the next pointer.
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 * (LeetCode 141: Linked List Cycle)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Spotify
 */

class LinkedListCycleDetection {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Floyd's Cycle-Finding Algorithm (Tortoise and Hare):
     * If there is no cycle, fast pointer will reach null.
     * If there is a cycle, the fast pointer will eventually lap and collide with
     * the slow pointer within the loop.
     */
    public static boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) return false;

        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) {
        // List with cycle: 3 -> 2 -> 0 -> -4 -> (points back to 2)
        ListNode n1 = new ListNode(3);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(0);
        ListNode n4 = new ListNode(-4);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n2; // Creates cycle

        System.out.println("Cyclic list has cycle? " + hasCycle(n1));

        // Acyclic list: 1 -> 2 -> null
        ListNode a1 = new ListNode(1);
        ListNode a2 = new ListNode(2);
        a1.next = a2;

        System.out.println("Acyclic list has cycle? " + hasCycle(a1));
    }
}

/*
 * Time Complexity: O(N) where N is the number of nodes.
 * Space Complexity: O(1) auxiliary space (no hash sets needed).
 */
