import java.util.Arrays;

/**
 * Problem Statement:
 * Given an array `nums` with `n` objects colored red (0), white (1), or blue (2),
 * sort them in-place in a single pass so that objects of the same color are adjacent:
 * 0s first, then 1s, then 2s.
 * You must solve this without using any library sort function and using only O(1) extra memory.
 * (LeetCode 75: Sort Colors - Dutch National Flag).
 *
 * Asked in: Amazon, Microsoft, Facebook / Meta, Google, Apple
 *
 * Approach:
 * - Dijkstra's Dutch National Flag 3-Way Partitioning:
 *   Maintain 3 pointers:
 *   - `low`: Boundary for 0s (nums[0 .. low-1] are all 0s)
 *   - `mid`: Current scanning pointer (nums[low .. mid-1] are all 1s)
 *   - `high`: Boundary for 2s (nums[high+1 .. n-1] are all 2s)
 *   While `mid <= high`:
 *   - Case `nums[mid] == 0`:
 *     Swap `nums[low]` and `nums[mid]`. Advance both `low++` and `mid++`.
 *   - Case `nums[mid] == 1`:
 *     Already in correct middle bucket. Advance `mid++`.
 *   - Case `nums[mid] == 2`:
 *     Swap `nums[mid]` and `nums[high]`. Decrement `high--`.
 *     CRITICAL: Do NOT advance `mid`, because the element swapped from `high` has not been evaluated yet!
 */
class SortColorsDutchNationalFlag {

    public static void sortColors(int[] nums) {
        if (nums == null || nums.length <= 1) return;

        int low = 0;
        int mid = 0;
        int high = nums.length - 1;

        while (mid <= high) {
            switch (nums[mid]) {
                case 0 -> {
                    swap(nums, low, mid);
                    low++;
                    mid++;
                }
                case 1 -> mid++;
                case 2 -> {
                    swap(nums, mid, high);
                    high--; // Do NOT increment mid here!
                }
            }
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 75: Dutch National Flag (One-Pass 3-Way Partition) ===");

        int[][] testCases = {
            { 2, 0, 2, 1, 1, 0 },
            { 2, 0, 1 },
            { 0 },
            { 1, 0, 2 },
            { 2, 2, 1, 0, 1, 0, 2, 0, 1 }
        };

        for (int[] arr : testCases) {
            int[] original = arr.clone();
            sortColors(arr);
            System.out.printf("Original: %-25s ==> Sorted: %s%n",
                    Arrays.toString(original), Arrays.toString(arr));
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(1) - Constant stack space (pure in-place swaps).
 */
