/*
 * Problem Statement:
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * (LeetCode 2: Add Two Numbers)
 * 
 * Example:
 * Input: l1 = [2,4,3], l2 = [5,6,4] (342 + 465)
 * Output: [7,0,8] (807)
 * 
 * Asked in: Amazon, Microsoft, Apple, Google, Facebook/Meta
 */

class AddTwoNumbersReversedList {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode curr = dummy;
        int carry = 0;

        while (l1 != null || l2 != null || carry != 0) {
            int sum = carry;
            if (l1 != null) {
                sum += l1.val;
                l1 = l1.next;
            }
            if (l2 != null) {
                sum += l2.val;
                l2 = l2.next;
            }

            carry = sum / 10;
            curr.next = new ListNode(sum % 10);
            curr = curr.next;
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
        ListNode l1 = buildList(2, 4, 3); // 342
        ListNode l2 = buildList(5, 6, 4); // 465

        System.out.print("List 1: "); printList(l1);
        System.out.print("List 2: "); printList(l2);

        ListNode sum = addTwoNumbers(l1, l2);
        System.out.print("Sum:    "); printList(sum);
    }
}

/*
 * Time Complexity: O(max(N, M)) where N and M are list lengths.
 * Space Complexity: O(max(N, M)) for output list.
 */
