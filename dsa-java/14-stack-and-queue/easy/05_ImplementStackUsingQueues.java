/*
 * Problem Statement:
 * Implement a last-in-first-out (LIFO) stack using only queues.
 * The implemented stack should support all functions of a normal stack (push, top, pop, and empty).
 * Implement it using a single Queue!
 * (LeetCode 225: Implement Stack using Queues)
 * 
 * Asked in: Google, Amazon, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Queue;

class ImplementStackUsingQueues {

    static class MyStack {
        private final Queue<Integer> queue = new ArrayDeque<>();

        public void push(int x) {
            queue.offer(x);
            int size = queue.size();
            // Rotate previous elements behind the newly pushed element
            for (int i = 0; i < size - 1; i++) {
                queue.offer(queue.poll());
            }
        }

        public int pop() {
            return queue.poll();
        }

        public int top() {
            return queue.peek();
        }

        public boolean empty() {
            return queue.isEmpty();
        }
    }

    public static void main(String[] args) {
        MyStack stack = new MyStack();

        System.out.println("--- Stack via Single Queue ---");
        stack.push(1);
        stack.push(2);
        System.out.println("top():   " + stack.top());   // returns 2
        System.out.println("pop():   " + stack.pop());   // returns 2
        System.out.println("empty(): " + stack.empty()); // returns false
    }
}

/*
 * Time Complexity: push: O(N) where N is current queue size; pop, top, empty: O(1).
 * Space Complexity: O(N) storage for single queue.
 */
