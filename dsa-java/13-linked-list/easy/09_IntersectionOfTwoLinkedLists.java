/*
 * Problem Statement:
 * Given the heads of two singly linked-lists headA and headB, return the node at which
 * the two lists intersect. If the two linked lists have no intersection at all, return null.
 * Note that the linked lists must retain their original structure after the function returns.
 * Could you write a solution that runs in O(m + n) time and use only O(1) memory?
 * (LeetCode 160: Intersection of Two Linked Lists)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Facebook/Meta
 */

class IntersectionOfTwoLinkedLists {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Two Pointers Wrapping Around:
     * Pointer pA traverses listA then wraps to headB.
     * Pointer pB traverses listB then wraps to headA.
     * Since len(A) + len(B) == len(B) + len(A), both pointers traverse the exact same total length.
     * They will either collide at the intersection node or both hit null simultaneously!
     */
    public static ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) return null;

        ListNode pA = headA;
        ListNode pB = headB;

        while (pA != pB) {
            pA = (pA == null) ? headB : pA.next;
            pB = (pB == null) ? headA : pB.next;
        }

        return pA; // Intersection node or null
    }

    public static void main(String[] args) {
        // Shared tail: 8 -> 4 -> 5
        ListNode common = new ListNode(8);
        common.next = new ListNode(4);
        common.next.next = new ListNode(5);

        // List A: 4 -> 1 -> common
        ListNode headA = new ListNode(4);
        headA.next = new ListNode(1);
        headA.next.next = common;

        // List B: 5 -> 6 -> 1 -> common
        ListNode headB = new ListNode(5);
        headB.next = new ListNode(6);
        headB.next.next = new ListNode(1);
        headB.next.next.next = common;

        ListNode intersection = getIntersectionNode(headA, headB);
        System.out.println("Intersection node value: " + (intersection != null ? intersection.val : "null") + " (Expected: 8)");
    }
}

/*
 * Time Complexity: O(M + N) where M and N are lengths of lists A and B.
 * Space Complexity: O(1) auxiliary pointers.
 */
