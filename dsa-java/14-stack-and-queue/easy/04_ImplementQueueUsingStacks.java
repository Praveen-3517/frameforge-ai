/*
 * Problem Statement:
 * Implement a first in first out (FIFO) queue using only two stacks.
 * The implemented queue should support all the functions of a normal queue
 * (push, peek, pop, and empty).
 * Can you implement each operation such that each operation is amortized O(1) time complexity?
 * (LeetCode 232: Implement Queue using Stacks)
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple
 */

import java.util.ArrayDeque;
import java.util.Deque;

class ImplementQueueUsingStacks {

    static class MyQueue {
        private final Deque<Integer> inStack = new ArrayDeque<>();
        private final Deque<Integer> outStack = new ArrayDeque<>();

        public void push(int x) {
            inStack.push(x);
        }

        public int pop() {
            shiftStacks();
            return outStack.pop();
        }

        public int peek() {
            shiftStacks();
            return outStack.peek();
        }

        public boolean empty() {
            return inStack.isEmpty() && outStack.isEmpty();
        }

        private void shiftStacks() {
            if (outStack.isEmpty()) {
                while (!inStack.isEmpty()) {
                    outStack.push(inStack.pop());
                }
            }
        }
    }

    public static void main(String[] args) {
        MyQueue queue = new MyQueue();

        System.out.println("--- Queue via Two Stacks ---");
        queue.push(1);
        queue.push(2);
        System.out.println("peek():  " + queue.peek()); // returns 1
        System.out.println("pop():   " + queue.pop());  // returns 1
        System.out.println("empty(): " + queue.empty()); // returns false
    }
}

/*
 * Time Complexity: push: O(1); pop & peek: Amortized O(1) (each element pushed and popped from outStack once).
 * Space Complexity: O(N) storage across the two stacks.
 */
