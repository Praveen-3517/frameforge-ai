import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem: Max Chunks To Make Sorted II (LeetCode 768)
 * Asked in: Google, Amazon, Microsoft
 * 
 * Given an integer array arr (which may contain duplicates), split arr into the
 * maximum number of chunks such that sorting each chunk individually and
 * concatenating the results produces a sorted array.
 * 
 * Approach:
 * Monotonic Stack of Chunk Maximums:
 * - Each element in the stack represents the maximum value in that chunk.
 * - For each number num in arr:
 *     - If stack is empty or num >= stack.peek(), num can start a new chunk -> push(num).
 *     - If num < stack.peek(), num must merge with previous chunks whose max > num.
 *       Pop the current chunk's max as curMax, then keep popping any chunk max > num.
 *       Finally, push curMax back into the stack.
 * - The number of chunks is stack.size().
 * 
 * Time Complexity: O(N) where each element is pushed and popped at most once.
 * Space Complexity: O(N) for stack storage.
 */
class MaxChunksToMakeSortedTwo {

    public static int maxChunksToSorted(int[] arr) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (int num : arr) {
            if (stack.isEmpty() || num >= stack.peek()) {
                stack.push(num);
            } else {
                int curMax = stack.pop();
                while (!stack.isEmpty() && stack.peek() > num) {
                    stack.pop();
                }
                stack.push(curMax);
            }
        }

        return stack.size();
    }

    public static void main(String[] args) {
        int[] arr1 = {2, 1, 3, 4, 4};
        System.out.println("Test 1: " + maxChunksToSorted(arr1) + " (Expected: 4)");

        int[] arr2 = {5, 4, 3, 2, 1};
        System.out.println("Test 2: " + maxChunksToSorted(arr2) + " (Expected: 1)");

        int[] arr3 = {1, 0, 1, 3, 2};
        System.out.println("Test 3: " + maxChunksToSorted(arr3) + " (Expected: 3)");
    }
}
