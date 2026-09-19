/*
 * Problem Statement:
 * Given the head of a linked list, return the node where the cycle begins.
 * If there is no cycle, return null. Do not modify the linked list.
 * Can you solve it using O(1) memory?
 * (LeetCode 142: Linked List Cycle II)
 * 
 * Asked in: Amazon, Microsoft, Goldman Sachs, Google
 */

class LinkedListCycleTwoFindStart {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Floyd's Cycle Finding Phase 1 and Phase 2:
     * Phase 1: Determine collision point inside loop using fast and slow pointers.
     * Phase 2: Reset slow pointer to head. Keep fast at intersection.
     * Advance both one step at a time. The point where they meet is the exact cycle entry node!
     */
    public static ListNode detectCycle(ListNode head) {
        if (head == null || head.next == null) return null;

        ListNode slow = head;
        ListNode fast = head;
        boolean hasCycle = false;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }

        if (!hasCycle) return null;

        // Phase 2: Reset slow to head
        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }

        return slow; // Cycle start node
    }

    public static void main(String[] args) {
        ListNode n1 = new ListNode(3);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(0);
        ListNode n4 = new ListNode(-4);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n2; // Loop starts at node 2

        ListNode cycleStart = detectCycle(n1);
        System.out.println("Cycle starts at node with value: " + (cycleStart != null ? cycleStart.val : "null") + " (Expected: 2)");
    }
}

/*
 * Time Complexity: O(N) linear time to detect and find cycle start.
 * Space Complexity: O(1) auxiliary space.
 */
