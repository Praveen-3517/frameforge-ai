/*
 * Problem Statement:
 * Given the head of a singly linked list, group all the nodes with odd indices together
 * followed by the nodes with even indices, and return the reordered list.
 * The first node is considered odd, and the second node is even, and so on.
 * Note that the relative order inside both the even and odd groups should remain as it was in the input.
 * You must solve the problem in O(1) extra space complexity and O(n) time complexity.
 * (LeetCode 328: Odd Even Linked List)
 * 
 * Example:
 * Input: head = [1,2,3,4,5]
 * Output: [1,3,5,2,4]
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple
 */

class OddEvenLinkedList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null) return head;

        ListNode odd = head;
        ListNode even = head.next;
        ListNode evenHead = even;

        while (even != null && even.next != null) {
            odd.next = even.next;
            odd = odd.next;

            even.next = odd.next;
            even = even.next;
        }

        // Connect odd list tail to even list head
        odd.next = evenHead;
        return head;
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
        ListNode list = buildList(1, 2, 3, 4, 5);
        System.out.print("Original list: "); printList(list);

        ListNode reordered = oddEvenList(list);
        System.out.print("Odd-Even list: "); printList(reordered);
    }
}

/*
 * Time Complexity: O(N) single linear pass over the list.
 * Space Complexity: O(1) in-place pointer adjustments.
 */
