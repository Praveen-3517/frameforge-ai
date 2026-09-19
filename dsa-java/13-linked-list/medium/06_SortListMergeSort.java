/*
 * Problem Statement:
 * Given the head of a linked list, return the list after sorting it in ascending order.
 * Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
 * (LeetCode 148: Sort List)
 * 
 * Example:
 * Input: head = [4,2,1,3]
 * Output: [1,2,3,4]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
 */

class SortListMergeSort {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Top-Down Divide and Conquer Merge Sort:
     * 1. Base case: if head == null || head.next == null, return head.
     * 2. Split list into two halves using fast and slow pointers.
     * 3. Recursively sort each half.
     * 4. Merge the two sorted halves using standard merge subroutine.
     */
    public static ListNode sortList(ListNode head) {
        if (head == null || head.next == null) return head;

        // Split list into two halves
        ListNode prev = null;
        ListNode slow = head;
        ListNode fast = head;

        while (fast != null && fast.next != null) {
            prev = slow;
            slow = slow.next;
            fast = fast.next.next;
        }

        prev.next = null; // Break first half from second half

        // Recursively sort halves
        ListNode l1 = sortList(head);
        ListNode l2 = sortList(slow);

        // Merge sorted halves
        return merge(l1, l2);
    }

    private static ListNode merge(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) {
                tail.next = l1;
                l1 = l1.next;
            } else {
                tail.next = l2;
                l2 = l2.next;
            }
            tail = tail.next;
        }

        if (l1 != null) tail.next = l1;
        if (l2 != null) tail.next = l2;

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
        ListNode list = buildList(4, 2, 1, 3);
        System.out.print("Original list: "); printList(list);

        ListNode sorted = sortList(list);
        System.out.print("Sorted list:   "); printList(sorted);
    }
}

/*
 * Time Complexity: O(N log N) divide and conquer MergeSort.
 * Space Complexity: O(log N) recursion call stack depth.
 */
