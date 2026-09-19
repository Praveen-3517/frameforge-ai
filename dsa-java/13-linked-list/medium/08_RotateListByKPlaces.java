/*
 * Problem Statement:
 * Given the head of a linked list, rotate the list to the right by k places.
 * (LeetCode 61: Rotate List)
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 * 
 * Example 2:
 * Input: head = [0,1,2], k = 4
 * Output: [2,0,1]
 * 
 * Asked in: Microsoft, Amazon, Google, Bloomberg
 */

class RotateListByKPlaces {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Ring / Cycle formation:
     * 1. Count length of list and connect tail to head (forming a circular ring).
     * 2. Effective rotation: k = k % length.
     * 3. New tail is at index (length - k - 1).
     * 4. New head is newTail.next; break circular link: newTail.next = null.
     */
    public static ListNode rotateRight(ListNode head, int k) {
        if (head == null || head.next == null || k == 0) return head;

        // 1. Calculate length and find tail
        int length = 1;
        ListNode tail = head;
        while (tail.next != null) {
            tail = tail.next;
            length++;
        }

        // 2. Modulo k
        k = k % length;
        if (k == 0) return head;

        // 3. Connect tail to head
        tail.next = head;

        // 4. Find new tail
        int stepsToNewTail = length - k;
        ListNode newTail = head;
        for (int i = 1; i < stepsToNewTail; i++) {
            newTail = newTail.next;
        }

        ListNode newHead = newTail.next;
        newTail.next = null; // Break loop

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

        ListNode rotated = rotateRight(list1, 2);
        System.out.print("Rotated by 2:  "); printList(rotated);

        ListNode list2 = buildList(0, 1, 2);
        ListNode rot2 = rotateRight(list2, 4);
        System.out.print("Rotated by 4:  "); printList(rot2);
    }
}

/*
 * Time Complexity: O(N) where N is the length of the linked list.
 * Space Complexity: O(1) in-place pointer adjustments.
 */
