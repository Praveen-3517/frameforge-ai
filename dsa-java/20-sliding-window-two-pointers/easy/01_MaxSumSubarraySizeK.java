/**
 * Problem: Maximum Sum Subarray of Size K
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an array of positive integers and a positive integer K,
 * find the maximum sum of any contiguous subarray of size K.
 * 
 * Approach - Fixed Sliding Window:
 * 1. Compute sum of first K elements.
 * 2. Slide the window right: add the new element, remove the leftmost element.
 * 3. Track maximum at each window position.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MaxSumSubarraySizeK {

    public static int maxSumSubarray(int[] arr, int k) {
        if (arr.length < k) {
            throw new IllegalArgumentException("Array length must be >= k");
        }

        int windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }

        int maxSum = windowSum;
        for (int i = k; i < arr.length; i++) {
            windowSum += arr[i] - arr[i - k]; // slide: add new, remove old
            maxSum = Math.max(maxSum, windowSum);
        }

        return maxSum;
    }

    public static void main(String[] args) {
        int[] arr1 = {2, 3, 4, 1, 5};
        System.out.println("Max sum k=3: " + maxSumSubarray(arr1, 3) + " (Expected: 10)");
        // Window [3,4,1]=8, [4,1,5]=10 -> max=10

        int[] arr2 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
        System.out.println("Max sum k=4: " + maxSumSubarray(arr2, 4) + " (Expected: 39)");
        // Window [2,10,23,3] = 38? Actually [10,23,3,1]=37, let's see: [2,10,23,3]=38, [10,23,3,1]=37
        // Max should be 39 from [4,2,10,23]=39
    }
}
