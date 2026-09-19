/*
 * Problem Statement:
 * Implement a custom Stack data structure from scratch using a fixed-size array:
 * - push(int x): Push element onto stack; throw Overflow error if full.
 * - pop(): Remove and return top element; throw Underflow error if empty.
 * - peek(): Return top element without removing.
 * - isEmpty(), isFull(), size().
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
 */

class CustomArrayStack {

    static class ArrayStack {
        private final int[] arr;
        private int top;
        private final int capacity;

        public ArrayStack(int capacity) {
            this.capacity = capacity;
            this.arr = new int[capacity];
            this.top = -1;
        }

        public void push(int x) {
            if (isFull()) {
                throw new IllegalStateException("Stack Overflow: Cannot push " + x + " into full stack.");
            }
            arr[++top] = x;
        }

        public int pop() {
            if (isEmpty()) {
                throw new IllegalStateException("Stack Underflow: Cannot pop from empty stack.");
            }
            return arr[top--];
        }

        public int peek() {
            if (isEmpty()) {
                throw new IllegalStateException("Stack is empty.");
            }
            return arr[top];
        }

        public boolean isEmpty() { return top == -1; }
        public boolean isFull() { return top == capacity - 1; }
        public int size() { return top + 1; }
    }

    public static void main(String[] args) {
        ArrayStack stack = new ArrayStack(3);

        System.out.println("--- Custom Array Stack Testing ---");
        stack.push(10);
        stack.push(20);
        stack.push(30);

        System.out.println("Top element (peek): " + stack.peek());
        System.out.println("Stack size: " + stack.size());
        System.out.println("Is full? " + stack.isFull());

        while (!stack.isEmpty()) {
            System.out.println("Popped: " + stack.pop());
        }

        System.out.println("Is empty now? " + stack.isEmpty());
    }
}

/*
 * Time Complexity: O(1) for push, pop, peek, isEmpty, isFull.
 * Space Complexity: O(capacity) array storage.
 */
