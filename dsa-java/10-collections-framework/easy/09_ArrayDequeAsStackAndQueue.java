/*
 * Problem Statement:
 * Demonstrate `java.util.ArrayDeque` as the preferred implementation for both Stacks and Queues:
 * - Why legacy `java.util.Stack` should be avoided:
 *   - Stack extends `Vector` (synchronized method overhead, breaks encapsulation by allowing index access).
 * - Using ArrayDeque as a LIFO Stack: `push()`, `pop()`, `peek()`.
 * - Using ArrayDeque as a FIFO Queue: `offer()`, `poll()`, `peek()`.
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Deque;

class ArrayDequeAsStackAndQueue {

    public static void main(String[] args) {
        // 1. ArrayDeque as a High-Performance LIFO Stack
        System.out.println("--- 1. ArrayDeque as Stack (LIFO) ---");
        Deque<String> stack = new ArrayDeque<>();
        stack.push("Page 1");
        stack.push("Page 2");
        stack.push("Page 3");

        System.out.println("Top of stack (peek): " + stack.peek());
        while (!stack.isEmpty()) {
            System.out.println("Popped from stack: " + stack.pop());
        }

        // 2. ArrayDeque as a FIFO Queue
        System.out.println("\n--- 2. ArrayDeque as Queue (FIFO) ---");
        Deque<Integer> queue = new ArrayDeque<>();
        queue.offer(100);
        queue.offer(200);
        queue.offer(300);

        System.out.println("Front of queue (peek): " + queue.peek());
        while (!queue.isEmpty()) {
            System.out.println("Served from queue: " + queue.poll());
        }
    }
}

/*
 * Time Complexity: Amortized O(1) for push, pop, offer, poll, and peek operations.
 * Space Complexity: O(N) circular array buffer memory.
 */
