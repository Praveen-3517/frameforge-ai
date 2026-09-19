/**
 * Problem: Two Sum II - Input Array Is Sorted (LeetCode 167)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Amazon, Apple, Microsoft, Google
 * 
 * Given a 1-indexed array of integers that is already sorted in non-decreasing order,
 * find two numbers such that they add up to a specific target number.
 * Return indices [index1, index2] (1-indexed, index1 < index2).
 * 
 * Approach - Two Pointer (Opposite Ends):
 * Use left pointer starting at index 0, right pointer at index n-1.
 * - If sum == target: found.
 * - If sum < target: move left pointer right (increase sum).
 * - If sum > target: move right pointer left (decrease sum).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class TwoSumIISortedArrayTwoPointer {

    public static int[] twoSum(int[] numbers, int target) {
        int left = 0;
        int right = numbers.length - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return new int[]{left + 1, right + 1}; // 1-indexed
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }

        return new int[]{-1, -1}; // no answer (guaranteed to have one per problem)
    }

    public static void main(String[] args) {
        int[] arr = {2, 7, 11, 15};
        java.util.Arrays.stream(twoSum(arr, 9)).forEach(x -> System.out.print(x + " "));
        System.out.println("(Expected: 1 2)");

        int[] arr2 = {2, 3, 4};
        java.util.Arrays.stream(twoSum(arr2, 6)).forEach(x -> System.out.print(x + " "));
        System.out.println("(Expected: 1 3)");
    }
}
