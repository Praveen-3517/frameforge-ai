/*
 * Problem Statement:
 * Given the head of a linked list and an integer val, remove all the nodes of the
 * linked list that has Node.val == val, and return the new head.
 * (LeetCode 203: Remove Linked List Elements)
 * 
 * Example:
 * Input: head = [1,2,6,3,4,5,6], val = 6
 * Output: [1,2,3,4,5]
 * 
 * Asked in: Apple, Amazon, Microsoft
 */

class RemoveLinkedListElements {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Sentinel Dummy Node:
     * Create dummy node pointing to head to seamlessly handle deletions of head nodes.
     */
    public static ListNode removeElements(ListNode head, int val) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode curr = dummy;

        while (curr.next != null) {
            if (curr.next.val == val) {
                curr.next = curr.next.next; // Delete node
            } else {
                curr = curr.next;
            }
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
        ListNode list = buildList(1, 2, 6, 3, 4, 5, 6);
        System.out.print("Original list: "); printList(list);

        ListNode filtered = removeElements(list, 6);
        System.out.print("After removing 6: "); printList(filtered);

        ListNode list2 = buildList(7, 7, 7, 7);
        ListNode filtered2 = removeElements(list2, 7);
        System.out.print("All 7s removed: "); printList(filtered2);
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place deletion.
 */
