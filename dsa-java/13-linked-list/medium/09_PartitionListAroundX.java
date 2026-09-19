/*
 * Problem Statement:
 * Given the head of a linked list and a value x, partition it such that all nodes
 * less than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 * (LeetCode 86: Partition List)
 * 
 * Example:
 * Input: head = [1,4,3,2,5,2], x = 3
 * Output: [1,2,2,4,3,5]
 * 
 * Asked in: Microsoft, Adobe, Amazon
 */

class PartitionListAroundX {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Dual Dummy Sentinel Lists:
     * 1. Create two lists: `lessList` (for values < x) and `greaterList` (for values >= x).
     * 2. Iterate through original list, distributing nodes based on value.
     * 3. Join tail of `lessList` to head of `greaterList`.
     * 4. Set tail of `greaterList` to null.
     */
    public static ListNode partition(ListNode head, int x) {
        ListNode lessDummy = new ListNode(0);
        ListNode greaterDummy = new ListNode(0);

        ListNode less = lessDummy;
        ListNode greater = greaterDummy;

        ListNode curr = head;
        while (curr != null) {
            if (curr.val < x) {
                less.next = curr;
                less = less.next;
            } else {
                greater.next = curr;
                greater = greater.next;
            }
            curr = curr.next;
        }

        greater.next = null; // Terminate greater list
        less.next = greaterDummy.next; // Stitch lists together

        return lessDummy.next;
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
        ListNode list = buildList(1, 4, 3, 2, 5, 2);
        System.out.print("Original list: "); printList(list);

        ListNode partitioned = partition(list, 3);
        System.out.print("Partitioned around 3: "); printList(partitioned);
    }
}

/*
 * Time Complexity: O(N) single pass through the list.
 * Space Complexity: O(1) in-place pointer stitching.
 */
