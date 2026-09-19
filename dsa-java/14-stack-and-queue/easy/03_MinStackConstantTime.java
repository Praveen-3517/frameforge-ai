/*
 * Problem Statement:
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * Implement the MinStack class:
 * - void push(int val): pushes the element val onto the stack.
 * - void pop(): removes the element on the top of the stack.
 * - int top(): gets the top element of the stack.
 * - int getMin(): retrieves the minimum element in the stack.
 * You must implement a solution with O(1) time complexity for each function.
 * (LeetCode 155: Min Stack)
 * 
 * Asked in: Amazon, Bloomberg, Microsoft, Google, Facebook/Meta
 */

import java.util.ArrayDeque;
import java.util.Deque;

class MinStackConstantTime {

    static class MinStack {
        // Main stack stores values
        private final Deque<Integer> stack = new ArrayDeque<>();
        // Auxiliary stack tracks running minimums
        private final Deque<Integer> minStack = new ArrayDeque<>();

        public MinStack() {}

        public void push(int val) {
            stack.push(val);
            if (minStack.isEmpty() || val <= minStack.peek()) {
                minStack.push(val);
            }
        }

        public void pop() {
            if (stack.isEmpty()) return;
            int removed = stack.pop();
            if (removed == minStack.peek()) {
                minStack.pop();
            }
        }

        public int top() {
            return stack.peek();
        }

        public int getMin() {
            return minStack.peek();
        }
    }

    public static void main(String[] args) {
        MinStack minStack = new MinStack();

        System.out.println("--- Min Stack Operations ---");
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);

        System.out.println("getMin(): " + minStack.getMin()); // Returns -3
        minStack.pop();
        System.out.println("top():    " + minStack.top());    // Returns 0
        System.out.println("getMin(): " + minStack.getMin()); // Returns -2
    }
}

/*
 * Time Complexity: O(1) strictly for push, pop, top, and getMin.
 * Space Complexity: O(N) auxiliary space for minStack.
 */
