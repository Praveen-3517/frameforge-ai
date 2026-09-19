/*
 * Problem Statement:
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists into one sorted list. The list should be made by splicing together
 * the nodes of the first two lists.
 * Return the head of the merged linked list.
 * (LeetCode 21: Merge Two Sorted Lists)
 * 
 * Example:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * 
 * Asked in: Amazon, Apple, Microsoft, Google, Bloomberg
 */

class MergeTwoSortedLists {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (list1 != null && list2 != null) {
            if (list1.val <= list2.val) {
                tail.next = list1;
                list1 = list1.next;
            } else {
                tail.next = list2;
                list2 = list2.next;
            }
            tail = tail.next;
        }

        // Attach remaining nodes
        if (list1 != null) {
            tail.next = list1;
        } else if (list2 != null) {
            tail.next = list2;
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
        ListNode l1 = buildList(1, 2, 4);
        ListNode l2 = buildList(1, 3, 4);

        System.out.print("List 1: "); printList(l1);
        System.out.print("List 2: "); printList(l2);

        ListNode merged = mergeTwoLists(l1, l2);
        System.out.print("Merged: "); printList(merged);
    }
}

/*
 * Time Complexity: O(N + M) where N and M are the lengths of the two lists.
 * Space Complexity: O(1) in-place pointer splicing.
 */
