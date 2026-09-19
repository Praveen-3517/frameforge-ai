/*
 * Problem Statement:
 * Demonstrate `java.util.LinkedList` operating as both a Queue (FIFO) and a Deque (Double-Ended Queue):
 * - Adding and removing from both ends in O(1) time: addFirst, addLast, removeFirst, removeLast.
 * - Peeking elements without removal: peekFirst, peekLast.
 * - Converting between Queue and Deque interfaces.
 * 
 * Asked in: Amazon, Oracle, Goldman Sachs, Cognizant
 */

import java.util.Deque;
import java.util.LinkedList;
import java.util.Queue;

class LinkedListAsDequeAndQueue {

    public static void main(String[] args) {
        // 1. LinkedList as a Standard FIFO Queue
        System.out.println("--- 1. LinkedList as FIFO Queue ---");
        Queue<String> printQueue = new LinkedList<>();
        printQueue.offer("Doc_Invoice.pdf");
        printQueue.offer("Doc_Resume.docx");
        printQueue.offer("Doc_Presentation.pptx");

        System.out.println("Next document in queue (peek): " + printQueue.peek());
        while (!printQueue.isEmpty()) {
            System.out.println("Printing: " + printQueue.poll());
        }

        // 2. LinkedList as a Double-Ended Queue (Deque)
        System.out.println("\n--- 2. LinkedList as Deque (Front & Back Operations) ---");
        Deque<Integer> deque = new LinkedList<>();
        deque.addFirst(10); // [10]
        deque.addLast(20);  // [10, 20]
        deque.addFirst(5);  // [5, 10, 20]
        deque.addLast(25);  // [5, 10, 20, 25]

        System.out.println("Deque state: " + deque);
        System.out.println("First element: " + deque.peekFirst() + ", Last element: " + deque.peekLast());

        System.out.println("Removed from front: " + deque.removeFirst()); // 5
        System.out.println("Removed from back:  " + deque.removeLast());  // 25
        System.out.println("Remaining deque:    " + deque);
    }
}

/*
 * Time Complexity: O(1) for all addFirst, addLast, removeFirst, removeLast, peek operations.
 * Space Complexity: O(N) where N is number of node elements.
 */
