/*
 * Problem Statement:
 * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
 * Could you do it in O(n) time and O(1) space?
 * (LeetCode 234: Palindrome Linked List)
 * 
 * Example 1:
 * Input: head = [1,2,2,1]
 * Output: true
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: false
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Apple
 */

class PalindromeLinkedList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * O(N) Time and O(1) Space In-Place Strategy:
     * 1. Find midpoint of the list using fast and slow pointers.
     * 2. Reverse the second half of the list.
     * 3. Compare the first half and the reversed second half node by node.
     * 4. (Optional) Restore the original list by reversing the second half back.
     */
    public static boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) return true;

        // 1. Find middle node (slow)
        ListNode slow = head;
        ListNode fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        // 2. Reverse second half
        ListNode secondHalfHead = reverse(slow.next);

        // 3. Compare values
        ListNode p1 = head;
        ListNode p2 = secondHalfHead;
        boolean isPal = true;

        while (p2 != null) {
            if (p1.val != p2.val) {
                isPal = false;
                break;
            }
            p1 = p1.next;
            p2 = p2.next;
        }

        // 4. Restore list structure
        slow.next = reverse(secondHalfHead);

        return isPal;
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

    public static void main(String[] args) {
        ListNode l1 = buildList(1, 2, 2, 1);
        System.out.println("[1, 2, 2, 1] is palindrome? " + isPalindrome(l1));

        ListNode l2 = buildList(1, 2, 3, 2, 1);
        System.out.println("[1, 2, 3, 2, 1] is palindrome? " + isPalindrome(l2));

        ListNode l3 = buildList(1, 2, 3);
        System.out.println("[1, 2, 3] is palindrome? " + isPalindrome(l3));
    }
}

/*
 * Time Complexity: O(N) - Half-list traversal + reversal + comparison.
 * Space Complexity: O(1) auxiliary space.
 */
