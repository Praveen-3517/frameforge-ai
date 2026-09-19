import java.util.Arrays;

/**
 * Problem: Squares of a Sorted Array (LeetCode 977)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Amazon, Microsoft, Google
 * 
 * Given an integer array sorted in non-decreasing order, return an array of the
 * squares of each number sorted in non-decreasing order.
 * 
 * Approach - Two-End Merge:
 * The largest square is at either the leftmost (most negative) or rightmost element.
 * Use two pointers at each end. Compare their absolute values, insert the larger
 * square at the end of the result array.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the result array.
 */
class SquaresOfSortedArrayTwoPointer {

    public static int[] sortedSquares(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int left = 0;
        int right = n - 1;
        int pos = n - 1; // fill from the end

        while (left <= right) {
            int leftSq = nums[left] * nums[left];
            int rightSq = nums[right] * nums[right];

            if (leftSq > rightSq) {
                result[pos--] = leftSq;
                left++;
            } else {
                result[pos--] = rightSq;
                right--;
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println(Arrays.toString(sortedSquares(new int[]{-4, -1, 0, 3, 10})));
        // Expected: [0, 1, 9, 16, 100]
        System.out.println(Arrays.toString(sortedSquares(new int[]{-7, -3, 2, 3, 11})));
        // Expected: [4, 9, 9, 49, 121]
    }
}
