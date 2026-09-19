/*
 * Problem Statement:
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 * (LeetCode 23: Merge k Sorted Lists)
 * 
 * Example:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Google, Apple, Bloomberg
 */

import java.util.PriorityQueue;

class MergeKSortedListsPriorityQueue {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Min-Heap PriorityQueue:
     * - Insert the head of each non-empty linked list into a Min-Heap of capacity k.
     * - In a loop, extract the smallest node from the heap, attach to merged result list.
     * - If the extracted node has a next node, offer next node to the heap.
     * - Repeat until heap is empty.
     */
    public static ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) return null;

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));

        // Seed heap with head of each list
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

    private static ListNode buildList(int... values) {
        ListNode dummy = new ListNode(0);
        ListNode curr = dummy;
        for (int v : values) {
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

        System.out.println("--- Merging K Sorted Linked Lists ---");
        System.out.print("List 1: "); printList(l1);
        System.out.print("List 2: "); printList(l2);
        System.out.print("List 3: "); printList(l3);

        ListNode merged = mergeKLists(lists);
        System.out.print("\nMerged Sorted List: ");
        printList(merged);
    }
}

/*
 * Time Complexity: O(N log k) where N is total number of nodes across all lists, k is lists count.
 * Space Complexity: O(k) for the priority queue holding at most k list heads.
 */
