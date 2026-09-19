import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * Problem: K Closest Points to Origin (LeetCode 973)
 * Asked in: Facebook, Amazon, Google, Apple
 * 
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane
 * and an integer k, return the k closest points to the origin (0, 0).
 * Distance is Euclidean: sqrt(x^2 + y^2).
 * 
 * Approach:
 * Max-Heap of size K:
 * Keep the k smallest distances by maintaining a Max-Heap of size k comparing (x^2 + y^2).
 * When heap size exceeds k, poll the point with the largest distance.
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(K) for the Max-Heap.
 */
class KClosestPointsToOrigin {

    public static int[][] kClosest(int[][] points, int k) {
        // Max-heap comparing distance squared: (x^2 + y^2) descending
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> 
            Integer.compare(b[0] * b[0] + b[1] * b[1], a[0] * a[0] + a[1] * a[1])
        );

        for (int[] p : points) {
            maxHeap.offer(p);
            if (maxHeap.size() > k) {
                maxHeap.poll();
            }
        }

        int[][] result = new int[k][2];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.poll();
        }

        return result;
    }

    public static void main(String[] args) {
        int[][] points1 = {{1, 3}, {-2, 2}};
        int[][] res1 = kClosest(points1, 1);
        System.out.println("Closest 1: " + Arrays.deepToString(res1)); // [[-2, 2]]

        int[][] points2 = {{3, 3}, {5, -1}, {-2, 4}};
        int[][] res2 = kClosest(points2, 2);
        System.out.println("Closest 2: " + Arrays.deepToString(res2)); // [[3, 3], [-2, 4]]
    }
}
