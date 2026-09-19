/*
 * Problem Statement:
 * Merge k sorted linked lists and return it as one sorted list using Pairwise Divide and Conquer:
 * - Instead of a Min-Heap, merge pairs of lists iteratively:
 *   lists[0] with lists[1], lists[2] with lists[3], and so on.
 * - In each round, the number of lists is halved (k -> k/2 -> k/4 -> ... -> 1).
 * (LeetCode 23: Merge k Sorted Lists via Divide and Conquer)
 * 
 * Asked in: Google, Facebook/Meta, Amazon, Microsoft
 */

class MergeKSortedListsDivideConquer {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) return null;
        return mergeRange(lists, 0, lists.length - 1);
    }

    private static ListNode mergeRange(ListNode[] lists, int left, int right) {
        if (left == right) return lists[left];
        int mid = left + (right - left) / 2;

        ListNode l1 = mergeRange(lists, left, mid);
        ListNode l2 = mergeRange(lists, mid + 1, right);

        return mergeTwo(l1, l2);
    }

    private static ListNode mergeTwo(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (l1 != null && l2 != null) {
            if (l1.val <= l2.val) {
                tail.next = l1;
                l1 = l1.next;
            } else {
                tail.next = l2;
                l2 = l2.next;
            }
            tail = tail.next;
        }

        if (l1 != null) tail.next = l1;
        if (l2 != null) tail.next = l2;

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
        ListNode l1 = buildList(1, 4, 5);
        ListNode l2 = buildList(1, 3, 4);
        ListNode l3 = buildList(2, 6);

        ListNode[] lists = {l1, l2, l3};
        ListNode merged = mergeKLists(lists);

        System.out.println("--- Divide and Conquer Merge of K Sorted Lists ---");
        System.out.print("Merged Result: ");
        printList(merged);
    }
}

/*
 * Time Complexity: O(N log k) where N is total nodes and k is number of lists.
 * Space Complexity: O(log k) recursion tree depth.
 */
