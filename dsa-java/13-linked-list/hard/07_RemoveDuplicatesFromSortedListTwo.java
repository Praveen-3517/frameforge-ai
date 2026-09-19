/*
 * Problem Statement:
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list. Return the linked list sorted as well.
 * (LeetCode 82: Remove Duplicates from Sorted List II)
 * 
 * Example:
 * Input: head = [1,2,3,3,4,4,5]
 * Output: [1,2,5]
 * 
 * Example 2:
 * Input: head = [1,1,1,2,3]
 * Output: [2,3]
 * 
 * Asked in: Microsoft, Amazon, Facebook/Meta
 */

class RemoveDuplicatesFromSortedListTwo {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode deleteDuplicates(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode prev = dummy;

        while (head != null) {
            // If current node is the start of duplicates
            if (head.next != null && head.val == head.next.val) {
                // Skip all nodes with the same value
                while (head.next != null && head.val == head.next.val) {
                    head = head.next;
                }
                // Discard duplicate sequence
                prev.next = head.next;
            } else {
                prev = prev.next;
            }
            head = head.next;
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
        ListNode list1 = buildList(1, 2, 3, 3, 4, 4, 5);
        System.out.print("Original list: "); printList(list1);

        ListNode res1 = deleteDuplicates(list1);
        System.out.print("Distinct only: "); printList(res1);

        ListNode list2 = buildList(1, 1, 1, 2, 3);
        System.out.print("\nOriginal list: "); printList(list2);
        ListNode res2 = deleteDuplicates(list2);
        System.out.print("Distinct only: "); printList(res2);
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
