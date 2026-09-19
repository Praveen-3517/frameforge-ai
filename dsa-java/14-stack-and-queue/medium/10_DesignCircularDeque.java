/*
 * Problem Statement:
 * Design your implementation of the circular double-ended queue (deque).
 * Implement the MyCircularDeque class:
 * - MyCircularDeque(int k): Initializes the deque with a maximum size of k.
 * - boolean insertFront(int value): Adds an item at the front.
 * - boolean insertLast(int value): Adds an item at the rear.
 * - boolean deleteFront(): Deletes an item from the front.
 * - boolean deleteLast(): Deletes an item from the rear.
 * - int getFront(), int getRear(), boolean isEmpty(), boolean isFull().
 * (LeetCode 641: Design Circular Deque)
 * 
 * Asked in: Google, Amazon, Facebook/Meta
 */

class DesignCircularDeque {

    static class MyCircularDeque {
        private final int[] data;
        private int front;
        private int rear;
        private int count;
        private final int capacity;

        public MyCircularDeque(int k) {
            this.capacity = k;
            this.data = new int[k];
            this.front = 0;
            this.rear = 0;
            this.count = 0;
        }

        public boolean insertFront(int value) {
            if (isFull()) return false;
            front = (front - 1 + capacity) % capacity;
            data[front] = value;
            count++;
            return true;
        }

        public boolean insertLast(int value) {
            if (isFull()) return false;
            data[rear] = value;
            rear = (rear + 1) % capacity;
            count++;
            return true;
        }

        public boolean deleteFront() {
            if (isEmpty()) return false;
            front = (front + 1) % capacity;
            count--;
            return true;
        }

        public boolean deleteLast() {
            if (isEmpty()) return false;
            rear = (rear - 1 + capacity) % capacity;
            count--;
            return true;
        }

        public int getFront() {
            return isEmpty() ? -1 : data[front];
        }

        public int getRear() {
            if (isEmpty()) return -1;
            return data[(rear - 1 + capacity) % capacity];
        }

        public boolean isEmpty() { return count == 0; }
        public boolean isFull() { return count == capacity; }
    }

    public static void main(String[] args) {
        MyCircularDeque deque = new MyCircularDeque(3);

        System.out.println("--- Testing Circular Deque (Capacity = 3) ---");
        System.out.println("insertLast(1):  " + deque.insertLast(1));  // true
        System.out.println("insertLast(2):  " + deque.insertLast(2));  // true
        System.out.println("insertFront(3): " + deque.insertFront(3)); // true
        System.out.println("insertFront(4): " + deque.insertFront(4)); // false (full)

        System.out.println("getRear():      " + deque.getRear());      // 2
        System.out.println("isFull():       " + deque.isFull());       // true
        System.out.println("deleteLast():   " + deque.deleteLast());   // true (removes 2)
        System.out.println("insertFront(4): " + deque.insertFront(4)); // true
        System.out.println("getFront():     " + deque.getFront());     // 4
    }
}

/*
 * Time Complexity: O(1) for all operations.
 * Space Complexity: O(k) fixed circular buffer.
 */
