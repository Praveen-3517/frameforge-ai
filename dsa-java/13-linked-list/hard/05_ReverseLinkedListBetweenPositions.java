/*
 * Problem Statement:
 * Given the head of a singly linked list and two integers left and right where left <= right,
 * reverse the nodes of the list from position left to position right, and return the reversed list.
 * (LeetCode 92: Reverse Linked List II)
 * 
 * Example:
 * Input: head = [1,2,3,4,5], left = 2, right = 4
 * Output: [1,4,3,2,5]
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Apple
 */

class ReverseLinkedListBetweenPositions {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * One-Pass In-Place Reversal:
     * 1. Advance `prev` pointer to node just before position `left`.
     * 2. Let `curr` be the first node of the segment to reverse.
     * 3. For (right - left) times:
     *    Remove `curr.next` and insert it immediately after `prev`.
     */
    public static ListNode reverseBetween(ListNode head, int left, int right) {
        if (head == null || left == right) return head;

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode prev = dummy;

        for (int i = 1; i < left; i++) {
            prev = prev.next;
        }

        ListNode curr = prev.next;
        for (int i = 0; i < right - left; i++) {
            ListNode next = curr.next;
            curr.next = next.next;
            next.next = prev.next;
            prev.next = next;
        }

        return dummy.next;
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

    private static void printList(ListNode head) {
        ListNode curr = head;
        while (curr != null) {
            System.out.print(curr.val + (curr.next != null ? " -> " : ""));
            curr = curr.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        ListNode list = buildList(1, 2, 3, 4, 5);
        System.out.print("Original list: "); printList(list);

        ListNode res = reverseBetween(list, 2, 4);
        System.out.print("Reversed between [2, 4]: "); printList(res);
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place pointer adjustments.
 */
