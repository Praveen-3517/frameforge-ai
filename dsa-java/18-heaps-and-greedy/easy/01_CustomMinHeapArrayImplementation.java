import java.util.Arrays;
import java.util.NoSuchElementException;

/**
 * Problem: Custom Min-Heap Implementation using Array
 * Asked in: Amazon, Google, Microsoft, Adobe
 * 
 * Implement a complete Min-Heap data structure from scratch using an array supporting:
 * - insert(val): Add element and heapify up in O(log N).
 * - extractMin(): Remove and return root and heapify down in O(log N).
 * - peek(): Return root without removing in O(1).
 * - size() and isEmpty().
 * 
 * Time Complexity:
 * - insert: O(log N)
 * - extractMin: O(log N)
 * - peek: O(1)
 * Space Complexity: O(N) for internal array.
 */
class CustomMinHeapArrayImplementation {

    private int[] heap;
    private int size;
    private int capacity;

    public CustomMinHeapArrayImplementation(int capacity) {
        this.capacity = capacity;
        this.size = 0;
        this.heap = new int[capacity];
    }

    public void insert(int val) {
        if (size == capacity) {
            capacity *= 2;
            heap = Arrays.copyOf(heap, capacity);
        }
        heap[size] = val;
        heapifyUp(size);
        size++;
    }

    public int extractMin() {
        if (size == 0) throw new NoSuchElementException("Heap is empty");
        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        if (size > 0) {
            heapifyDown(0);
        }
        return min;
    }

    public int peek() {
        if (size == 0) throw new NoSuchElementException("Heap is empty");
        return heap[0];
    }

    public int size() {
        return size;
    }

    private void heapifyUp(int idx) {
        int parent = (idx - 1) / 2;
        while (idx > 0 && heap[idx] < heap[parent]) {
            swap(idx, parent);
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }

    private void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != idx) {
            swap(idx, smallest);
            heapifyDown(smallest);
        }
    }

    private void swap(int i, int j) {
        int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    public static void main(String[] args) {
        CustomMinHeapArrayImplementation minHeap = new CustomMinHeapArrayImplementation(5);
        int[] vals = {15, 10, 20, 17, 8};
        for (int v : vals) minHeap.insert(v);

        System.out.println("Peek: " + minHeap.peek() + " (Expected: 8)");
        System.out.println("Extract: " + minHeap.extractMin() + " (Expected: 8)");
        System.out.println("Peek: " + minHeap.peek() + " (Expected: 10)");
        System.out.println("Extract: " + minHeap.extractMin() + " (Expected: 10)");
    }
}
