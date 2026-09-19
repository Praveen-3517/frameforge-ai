/*
 * Problem Statement:
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * Implement both:
 * 1. Iterative Approach (three pointers: prev, curr, next).
 * 2. Recursive Approach.
 * (LeetCode 206: Reverse Linked List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 * 
 * Asked in: Amazon, Apple, Google, Microsoft, Facebook/Meta
 */

class ReverseSinglyLinkedList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    // 1. Iterative Reversal
    public static ListNode reverseListIterative(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;

        while (curr != null) {
            ListNode nextTemp = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextTemp;
        }

        return prev;
    }

    // 2. Recursive Reversal
    public static ListNode reverseListRecursive(ListNode head) {
        if (head == null || head.next == null) return head;

        ListNode newHead = reverseListRecursive(head.next);
        head.next.next = head;
        head.next = null;
        return newHead;
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

        ListNode rev1 = reverseListIterative(list1);
        System.out.print("Reversed (Iterative): "); printList(rev1);

        ListNode rev2 = reverseListRecursive(rev1);
        System.out.print("Reversed back (Recursive): "); printList(rev2);
    }
}

/*
 * Time Complexity: O(N) linear pass over all N nodes.
 * Space Complexity: Iterative: O(1) in-place; Recursive: O(N) call stack.
 */
