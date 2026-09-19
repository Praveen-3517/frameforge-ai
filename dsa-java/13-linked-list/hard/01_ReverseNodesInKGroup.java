/*
 * Problem Statement:
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 * k is a positive integer and is less than or equal to the length of the linked list.
 * If the number of nodes is not a multiple of k then left-out nodes, in the end,
 * should remain as it is.
 * You may not alter the values in the list's nodes, only nodes themselves may be changed.
 * (LeetCode 25: Reverse Nodes in k-Group)
 * 
 * Example:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * 
 * Asked in: Microsoft, Amazon, Facebook/Meta, Apple, Google
 */

class ReverseNodesInKGroup {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || k <= 1) return head;

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode prevGroupEnd = dummy;

        while (true) {
            // Check if there are at least k nodes remaining
            ListNode kth = getKthNode(prevGroupEnd, k);
            if (kth == null) break;

            ListNode nextGroupStart = kth.next;

            // Reverse current k-group
            ListNode prev = nextGroupStart;
            ListNode curr = prevGroupEnd.next;
            while (curr != nextGroupStart) {
                ListNode temp = curr.next;
                curr.next = prev;
                prev = curr;
                curr = temp;
            }

            // Connect previous group end to the newly reversed group head
            ListNode temp = prevGroupEnd.next;
            prevGroupEnd.next = kth;
            prevGroupEnd = temp;
        }

        return dummy.next;
    }

    private static ListNode getKthNode(ListNode curr, int k) {
        while (curr != null && k > 0) {
            curr = curr.next;
            k--;
        }
        return curr;
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

        ListNode res1 = reverseKGroup(list1, 2);
        System.out.print("k = 2 group:   "); printList(res1);

        ListNode list2 = buildList(1, 2, 3, 4, 5);
        ListNode res2 = reverseKGroup(list2, 3);
        System.out.print("k = 3 group:   "); printList(res2);
    }
}

/*
 * Time Complexity: O(N) where N is number of nodes. Each node visited at most twice.
 * Space Complexity: O(1) in-place pointer manipulation.
 */
