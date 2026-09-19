import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Problem: Merge k Sorted Lists (LeetCode 23)
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Approach:
 * Min-Heap of Size K:
 * 1. Insert the head of each non-empty linked list into a Min-Heap.
 * 2. While heap is not empty:
 *    - Extract node with smallest value (`curr = heap.poll()`).
 *    - Append `curr` to the merged result list.
 *    - If `curr.next != null`, push `curr.next` into the heap.
 * 
 * Time Complexity: O(N log K) where N is total nodes, K is number of lists.
 * Space Complexity: O(K) for Min-Heap.
 */
class MergeKSortedListsMinHeap {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    public static ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) return null;

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a.val));

        for (ListNode node : lists) {
            if (node != null) {
                minHeap.offer(node);
            }
        }

        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while (!minHeap.isEmpty()) {
            ListNode smallest = minHeap.poll();
            tail.next = smallest;
            tail = tail.next;

            if (smallest.next != null) {
                minHeap.offer(smallest.next);
            }
        }

        return dummy.next;
    }

    public static void main(String[] args) {
        // List 1: 1 -> 4 -> 5
        ListNode l1 = new ListNode(1);
        l1.next = new ListNode(4);
        l1.next.next = new ListNode(5);

        // List 2: 1 -> 3 -> 4
        ListNode l2 = new ListNode(1);
        l2.next = new ListNode(3);
        l2.next.next = new ListNode(4);

        // List 3: 2 -> 6
        ListNode l3 = new ListNode(2);
        l3.next = new ListNode(6);

        ListNode merged = mergeKLists(new ListNode[]{l1, l2, l3});

        System.out.print("Merged List: ");
        while (merged != null) {
            System.out.print(merged.val + (merged.next != null ? " -> " : ""));
            merged = merged.next;
        }
        System.out.println();
        // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6
    }
}
