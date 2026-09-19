/*
 * Problem Statement:
 * Design a complete Doubly Linked List with Sentinel (dummy head and dummy tail) nodes:
 * - Each node has `prev` and `next` references.
 * - Support `addFirst`, `addLast`, `removeFirst`, `removeLast`, and bidirectional printing.
 * - Sentinel nodes eliminate edge-case null checks during insertion and deletion.
 * 
 * Asked in: Amazon, Google, Microsoft, Oracle
 */

class DesignDoublyLinkedList {

    static class DLLNode {
        int val;
        DLLNode prev, next;
        DLLNode(int val) { this.val = val; }
    }

    static class DoublyLinkedList {
        private final DLLNode head;
        private final DLLNode tail;
        private int size;

        public DoublyLinkedList() {
            head = new DLLNode(0); // Dummy head
            tail = new DLLNode(0); // Dummy tail
            head.next = tail;
            tail.prev = head;
            size = 0;
        }

        public void addFirst(int val) {
            DLLNode node = new DLLNode(val);
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
            size++;
        }

        public void addLast(int val) {
            DLLNode node = new DLLNode(val);
            node.next = tail;
            node.prev = tail.prev;
            tail.prev.next = node;
            tail.prev = node;
            size++;
        }

        public int removeFirst() {
            if (isEmpty()) throw new IllegalStateException("List is empty");
            DLLNode first = head.next;
            head.next = first.next;
            first.next.prev = head;
            size--;
            return first.val;
        }

        public int removeLast() {
            if (isEmpty()) throw new IllegalStateException("List is empty");
            DLLNode last = tail.prev;
            tail.prev = last.prev;
            last.prev.next = tail;
            size--;
            return last.val;
        }

        public boolean isEmpty() { return size == 0; }
        public int size() { return size; }

        public void printForward() {
            DLLNode curr = head.next;
            System.out.print("Forward:  ");
            while (curr != tail) {
                System.out.print(curr.val + (curr.next != tail ? " <-> " : ""));
                curr = curr.next;
            }
            System.out.println();
        }

        public void printBackward() {
            DLLNode curr = tail.prev;
            System.out.print("Backward: ");
            while (curr != head) {
                System.out.print(curr.val + (curr.prev != head ? " <-> " : ""));
                curr = curr.prev;
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        DoublyLinkedList dll = new DoublyLinkedList();

        System.out.println("--- Doubly Linked List Operations ---");
        dll.addFirst(20);
        dll.addFirst(10);
        dll.addLast(30);
        dll.addLast(40);

        dll.printForward();
        dll.printBackward();

        System.out.println("Removed First: " + dll.removeFirst());
        System.out.println("Removed Last:  " + dll.removeLast());

        dll.printForward();
    }
}

/*
 * Time Complexity: O(1) for addFirst, addLast, removeFirst, removeLast.
 * Space Complexity: O(N) storage for doubly linked nodes.
 */
