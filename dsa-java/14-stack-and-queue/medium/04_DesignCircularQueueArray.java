/*
 * Problem Statement:
 * Design your implementation of the circular queue (LeetCode 622: Design Circular Queue):
 * - MyCircularQueue(k): Initializes the object with the size of the queue to be k.
 * - int Front(): Gets the front item from the queue. If empty, return -1.
 * - int Rear(): Gets the last item from the queue. If empty, return -1.
 * - boolean enQueue(int value): Inserts an element into the circular queue. Return true if successful.
 * - boolean deQueue(): Deletes an element from the circular queue. Return true if successful.
 * - boolean isEmpty(), boolean isFull().
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Goldman Sachs
 */

class DesignCircularQueueArray {

    static class MyCircularQueue {
        private final int[] data;
        private int head;
        private int tail;
        private int count;
        private final int capacity;

        public MyCircularQueue(int k) {
            this.capacity = k;
            this.data = new int[k];
            this.head = 0;
            this.tail = 0;
            this.count = 0;
        }

        public boolean enQueue(int value) {
            if (isFull()) return false;
            data[tail] = value;
            tail = (tail + 1) % capacity;
            count++;
            return true;
        }

        public boolean deQueue() {
            if (isEmpty()) return false;
            head = (head + 1) % capacity;
            count--;
            return true;
        }

        public int Front() {
            return isEmpty() ? -1 : data[head];
        }

        public int Rear() {
            if (isEmpty()) return -1;
            // tail points to next write position, so last element is at (tail - 1 + capacity) % capacity
            int lastIdx = (tail - 1 + capacity) % capacity;
            return data[lastIdx];
        }

        public boolean isEmpty() {
            return count == 0;
        }

        public boolean isFull() {
            return count == capacity;
        }
    }

    public static void main(String[] args) {
        MyCircularQueue cq = new MyCircularQueue(3);

        System.out.println("--- Testing Circular Queue (k = 3) ---");
        System.out.println("enQueue(1): " + cq.enQueue(1)); // true
        System.out.println("enQueue(2): " + cq.enQueue(2)); // true
        System.out.println("enQueue(3): " + cq.enQueue(3)); // true
        System.out.println("enQueue(4): " + cq.enQueue(4)); // false (full)

        System.out.println("Rear():     " + cq.Rear());     // 3
        System.out.println("isFull():   " + cq.isFull());   // true
        System.out.println("deQueue():  " + cq.deQueue());  // true (removes 1)
        System.out.println("enQueue(4): " + cq.enQueue(4)); // true
        System.out.println("Rear():     " + cq.Rear());     // 4
    }
}

/*
 * Time Complexity: O(1) for all operations.
 * Space Complexity: O(k) fixed circular buffer.
 */
