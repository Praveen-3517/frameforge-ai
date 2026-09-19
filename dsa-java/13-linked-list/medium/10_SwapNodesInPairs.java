/*
 * Problem Statement:
 * Given a linked list, swap every two adjacent nodes and return its head.
 * You must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 * (LeetCode 24: Swap Nodes in Pairs)
 * 
 * Example:
 * Input: head = [1,2,3,4]
 * Output: [2,1,4,3]
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple
 */

class SwapNodesInPairs {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode swapPairs(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode prev = dummy;

        while (prev.next != null && prev.next.next != null) {
            ListNode first = prev.next;
            ListNode second = prev.next.next;

            // Perform pointer swaps
            first.next = second.next;
            second.next = first;
            prev.next = second;

            // Move prev pointer forward two nodes
            prev = first;
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
        ListNode list1 = buildList(1, 2, 3, 4);
        System.out.print("Original list: "); printList(list1);

        ListNode swapped = swapPairs(list1);
        System.out.print("Swapped pairs: "); printList(swapped);

        ListNode list2 = buildList(1, 2, 3, 4, 5);
        System.out.print("\nOdd list:      "); printList(list2);
        System.out.print("Swapped pairs: "); printList(swapPairs(list2));
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) auxiliary pointers.
 */
