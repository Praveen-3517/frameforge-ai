/*
 * Problem Statement:
 * Implement a custom Queue data structure from scratch using a Circular Array:
 * - enqueue(int x): Insert at tail; throw Overflow if full.
 * - dequeue(): Remove from front; throw Underflow if empty.
 * - front(): Inspect front element.
 * - isEmpty(), isFull(), size().
 * 
 * Asked in: Amazon, Oracle, Wipro, TCS
 */

class CustomArrayQueue {

    static class CircularArrayQueue {
        private final int[] arr;
        private int front;
        private int rear;
        private int count;
        private final int capacity;

        public CircularArrayQueue(int capacity) {
            this.capacity = capacity;
            this.arr = new int[capacity];
            this.front = 0;
            this.rear = 0;
            this.count = 0;
        }

        public void enqueue(int x) {
            if (isFull()) {
                throw new IllegalStateException("Queue Overflow: Cannot enqueue " + x);
            }
            arr[rear] = x;
            rear = (rear + 1) % capacity;
            count++;
        }

        public int dequeue() {
            if (isEmpty()) {
                throw new IllegalStateException("Queue Underflow: Cannot dequeue from empty queue.");
            }
            int val = arr[front];
            front = (front + 1) % capacity;
            count--;
            return val;
        }

        public int front() {
            if (isEmpty()) throw new IllegalStateException("Queue is empty.");
            return arr[front];
        }

        public boolean isEmpty() { return count == 0; }
        public boolean isFull() { return count == capacity; }
        public int size() { return count; }
    }

    public static void main(String[] args) {
        CircularArrayQueue q = new CircularArrayQueue(3);

        System.out.println("--- Custom Circular Array Queue Testing ---");
        q.enqueue(100);
        q.enqueue(200);
        q.enqueue(300);

        System.out.println("Front element: " + q.front());
        System.out.println("Dequeued: " + q.dequeue()); // frees space at index 0

        q.enqueue(400); // wraps around to index 0!
        System.out.println("Enqueued 400 with wrap around. Front: " + q.front());

        while (!q.isEmpty()) {
            System.out.println("Dequeued: " + q.dequeue());
        }
    }
}

/*
 * Time Complexity: O(1) for enqueue, dequeue, front, size.
 * Space Complexity: O(capacity) array storage.
 */
