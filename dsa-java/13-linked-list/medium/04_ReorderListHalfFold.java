/*
 * Problem Statement:
 * You are given the head of a singly linked-list. The list can be represented as:
 * L0 -> L1 -> ... -> Ln - 1 -> Ln
 * Reorder the list to be on the following form:
 * L0 -> Ln -> L1 -> Ln - 1 -> L2 -> Ln - 2 -> ...
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 * (LeetCode 143: Reorder List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [1,5,2,4,3]
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, ByteDance
 */

class ReorderListHalfFold {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * 3-Step In-Place Algorithm:
     * 1. Find midpoint of list using fast and slow pointers.
     * 2. Split into two halves and reverse the second half.
     * 3. Interleave/merge the two halves together node-by-node.
     */
    public static void reorderList(ListNode head) {
        if (head == null || head.next == null) return;

        // Step 1: Find middle
        ListNode slow = head;
        ListNode fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // Step 2: Reverse second half
        ListNode secondHalf = reverse(slow.next);
        slow.next = null; // Break link between halves

        // Step 3: Interleave p1 (first half) and p2 (reversed second half)
        ListNode p1 = head;
        ListNode p2 = secondHalf;

        while (p2 != null) {
            ListNode next1 = p1.next;
            ListNode next2 = p2.next;

            p1.next = p2;
            p2.next = next1;

            p1 = next1;
            p2 = next2;
        }
    }

    private static ListNode reverse(ListNode head) {
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
        reorderList(list1);
        System.out.print("Reordered list: "); printList(list1);

        ListNode list2 = buildList(1, 2, 3, 4);
        System.out.print("\nOriginal list: "); printList(list2);
        reorderList(list2);
        System.out.print("Reordered list: "); printList(list2);
    }
}

/*
 * Time Complexity: O(N) - Linear pass through list.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
