/*
 * Problem Statement:
 * There is a singly-linked list and you are given only the node to be deleted node.
 * You will not be given access to the first node of the list.
 * All values of the linked list are unique, and it is guaranteed that the given node
 * is not the last node in the linked list.
 * (LeetCode 237: Delete Node in a Linked List)
 * 
 * Example:
 * Input: head = [4,5,1,9], node = 5
 * Output: [4,1,9]
 * 
 * Asked in: Amazon, Apple, Microsoft, Adobe
 */

class DeleteNodeWithoutHeadPointer {

    static class ListNode {
        int val;
        ListNode next;
        ListNode(int val) { this.val = val; }
    }

    /**
     * Approach:
     * Value Overwrite / Identity Swap:
     * Since we do not have access to the previous node:
     * 1. Copy the value of the next node into the current node (`node.val = node.next.val`).
     * 2. Bypass the next node (`node.next = node.next.next`).
     * Effectively, the next node is deleted while the target node adopts its identity!
     */
    public static void deleteNode(ListNode node) {
        node.val = node.next.val;
        node.next = node.next.next;
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
        ListNode n1 = new ListNode(4);
        ListNode n2 = new ListNode(5);
        ListNode n3 = new ListNode(1);
        ListNode n4 = new ListNode(9);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;

        System.out.print("Original list: ");
        printList(n1);

        System.out.println("Deleting node with value 5 directly...");
        deleteNode(n2);

        System.out.print("Updated list:  ");
        printList(n1);
    }
}

/*
 * Time Complexity: O(1) constant time value assignment and pointer change.
 * Space Complexity: O(1) auxiliary space.
 */
