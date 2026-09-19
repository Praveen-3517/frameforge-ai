/*
 * Problem Statement:
 * Design your implementation of the linked list (LeetCode 707: Design Linked List):
 * - MyLinkedList(): Initializes the MyLinkedList object.
 * - int get(int index): Get the value of the index-th node in the linked list. If invalid, return -1.
 * - void addAtHead(int val): Add a node of value val before the first element.
 * - void addAtTail(int val): Append a node of value val as the last element.
 * - void addAtIndex(int index, int val): Add a node of value val before the index-th node.
 * - void deleteAtIndex(int index): Delete the index-th node in the linked list.
 * 
 * Asked in: Amazon, Apple, Microsoft, Bloomberg
 */

class DesignSinglyLinkedList {

    static class MyLinkedList {
        static class Node {
            int val;
            Node next;
            Node(int val) { this.val = val; }
        }

        private final Node head; // Sentinel dummy head
        private int size;

        public MyLinkedList() {
            head = new Node(0);
            size = 0;
        }

        public int get(int index) {
            if (index < 0 || index >= size) return -1;
            Node curr = head.next;
            for (int i = 0; i < index; i++) {
                curr = curr.next;
            }
            return curr.val;
        }

        public void addAtHead(int val) {
            addAtIndex(0, val);
        }

        public void addAtTail(int val) {
            addAtIndex(size, val);
        }

        public void addAtIndex(int index, int val) {
            if (index < 0 || index > size) return;

            Node prev = head;
            for (int i = 0; i < index; i++) {
                prev = prev.next;
            }

            Node newNode = new Node(val);
            newNode.next = prev.next;
            prev.next = newNode;
            size++;
        }

        public void deleteAtIndex(int index) {
            if (index < 0 || index >= size) return;

            Node prev = head;
            for (int i = 0; i < index; i++) {
                prev = prev.next;
            }

            prev.next = prev.next.next;
            size--;
        }

        public void printList() {
            Node curr = head.next;
            System.out.print("List (size " + size + "): ");
            while (curr != null) {
                System.out.print(curr.val + (curr.next != null ? " -> " : ""));
                curr = curr.next;
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        MyLinkedList list = new MyLinkedList();

        System.out.println("--- Testing Custom Linked List ---");
        list.addAtHead(1);
        list.addAtTail(3);
        list.addAtIndex(1, 2); // Linked list becomes 1 -> 2 -> 3
        list.printList();

        System.out.println("get(1): " + list.get(1)); // returns 2

        list.deleteAtIndex(1);  // Now 1 -> 3
        list.printList();
        System.out.println("get(1) after delete: " + list.get(1)); // returns 3
    }
}

/*
 * Time Complexity: addAtHead: O(1), get/addAtIndex/deleteAtIndex: O(N).
 * Space Complexity: O(N) for stored nodes.
 */
