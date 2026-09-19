/*
 * Problem Statement:
 * Given an integer array nums, return the maximum difference between two successive
 * elements in its sorted form. If the array contains less than two elements, return 0.
 * You must write an algorithm that runs in linear time and uses linear extra space.
 * (LeetCode 164: Maximum Gap)
 * 
 * Example:
 * Input: nums = [3,6,9,1]
 * Output: 3 (Sorted: [1,3,6,9]; max difference between successive elements is 3)
 * 
 * Asked in: Amazon, Google, Microsoft, Adobe
 */

import java.util.Arrays;

class MaximumGapBucketSort {

    /**
     * Approach:
     * Bucket Sort using Pigeonhole Principle:
     * - Let min and max be the extreme values of the array.
     * - The average gap between N elements across range [min, max] is:
     *   gap = ceil((max - min) / (N - 1)).
     * - The maximum gap MUST be >= this average gap!
     * - By creating buckets of size 'gap', the maximum gap CANNOT occur between two
     *   elements inside the SAME bucket!
     * - Thus, we only need to store min and max for each bucket, and compare each
     *   bucket's min with the previous non-empty bucket's max.
     */
    public static int maximumGap(int[] nums) {
        if (nums == null || nums.length < 2) return 0;

        int n = nums.length;
        int min = nums[0];
        int max = nums[0];

        for (int x : nums) {
            min = Math.min(min, x);
            max = Math.max(max, x);
        }

        if (min == max) return 0;

        // Bucket size and count
        int bucketSize = Math.max(1, (max - min) / (n - 1));
        int bucketCount = (max - min) / bucketSize + 1;

        int[] bucketMin = new int[bucketCount];
        int[] bucketMax = new int[bucketCount];
        Arrays.fill(bucketMin, Integer.MAX_VALUE);
        Arrays.fill(bucketMax, Integer.MIN_VALUE);

        // Put numbers into buckets
        for (int x : nums) {
            int idx = (x - min) / bucketSize;
            bucketMin[idx] = Math.min(bucketMin[idx], x);
            bucketMax[idx] = Math.max(bucketMax[idx], x);
        }

        // Calculate max gap between consecutive non-empty buckets
        int maxGap = 0;
        int prevMax = min;

        for (int i = 0; i < bucketCount; i++) {
            if (bucketMin[i] == Integer.MAX_VALUE) continue; // Empty bucket

            maxGap = Math.max(maxGap, bucketMin[i] - prevMax);
            prevMax = bucketMax[i];
        }

        return maxGap;
    }

    public static void main(String[] args) {
        int[] nums = {3, 6, 9, 1};

        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Maximum Gap: " + maximumGap(nums) + " (Expected: 3)");

        int[] nums2 = {10};
        System.out.println("Single element array maximum gap: " + maximumGap(nums2));
    }
}

/*
 * Time Complexity: O(N) linear time bucket assignment and pass.
 * Space Complexity: O(N) bucket arrays.
 */
