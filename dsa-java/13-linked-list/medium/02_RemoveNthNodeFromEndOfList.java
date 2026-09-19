/*
 * Problem Statement:
 * Given the head of a linked list, remove the n-th node from the end of the list
 * and return its head. Solve this in one pass!
 * (LeetCode 19: Remove Nth Node From End of List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * 
 * Asked in: Facebook/Meta, Amazon, Apple, Microsoft
 */

class RemoveNthNodeFromEndOfList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * One-Pass Two Pointers with Sentinel Dummy Node:
     * 1. Advance `fast` pointer n + 1 steps ahead of `slow`.
     * 2. Move both `slow` and `fast` together until `fast` reaches null.
     * 3. Now `slow` is pointing right BEFORE the target node to delete!
     * 4. Perform deletion: `slow.next = slow.next.next`.
     */
    public static ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode slow = dummy;
        ListNode fast = dummy;

        // Move fast n + 1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast.next;
        }

        // Move both until fast hits end
        while (fast != null) {
            slow = slow.next;
            fast = fast.next;
        }

        // Delete the nth node from end
        slow.next = slow.next.next;

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
        ListNode list1 = buildList(1, 2, 3, 4, 5);
        System.out.print("Original list: "); printList(list1);

        ListNode res1 = removeNthFromEnd(list1, 2);
        System.out.print("After removing 2nd from end: "); printList(res1);

        ListNode list2 = buildList(1);
        ListNode res2 = removeNthFromEnd(list2, 1);
        System.out.print("After removing 1st from end of single-node list: "); printList(res2);
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
