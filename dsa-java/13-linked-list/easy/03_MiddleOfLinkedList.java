/*
 * Problem Statement:
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 * (LeetCode 876: Middle of the Linked List)
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [3,4,5] (node with value 3)
 * 
 * Example 2:
 * Input: head = [1,2,3,4,5,6]
 * Output: [4,5,6] (second middle node)
 * 
 * Asked in: Amazon, Adobe, Google, Microsoft
 */

class MiddleOfLinkedList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Tortoise and Hare (Fast & Slow Pointers):
     * Initialize both slow and fast at head.
     * While fast != null and fast.next != null:
     *   slow = slow.next;
     *   fast = fast.next.next;
     * When fast reaches the end, slow is exactly at the middle node!
     */
    public static ListNode middleNode(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        return slow;
    }

    private static ListNode buildList(int... vals) {
        ListNode dummy = new ListNode(0);
        ListNode curr = dummy;
        for (int v : vals) {
            curr.next = new ListNode(v);
            curr = curr.next;
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        ListNode l1 = buildList(1, 2, 3, 4, 5);
        System.out.println("Odd length list [1,2,3,4,5] middle value: " + middleNode(l1).val + " (Expected: 3)");

        ListNode l2 = buildList(1, 2, 3, 4, 5, 6);
        System.out.println("Even length list [1,2,3,4,5,6] middle value: " + middleNode(l2).val + " (Expected: 4)");
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
