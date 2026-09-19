/**
 * Problem: Average of All Contiguous Subarrays of Size K
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Google, Goldman Sachs
 * 
 * Given an array of integers and an integer K, find the average of all contiguous
 * subarrays of size K and return them as an array.
 * 
 * Approach - Fixed Sliding Window:
 * Keep a running sum of the window.
 * Each iteration: add new right element, remove old left element, compute average.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N - K + 1) for result.
 */
class AverageOfSubarraysSizeK {

    public static double[] findAverages(int[] arr, int k) {
        int n = arr.length;
        double[] result = new double[n - k + 1];
        double windowSum = 0;

        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        result[0] = windowSum / k;

        for (int i = k; i < n; i++) {
            windowSum += arr[i] - arr[i - k];
            result[i - k + 1] = windowSum / k;
        }

        return result;
    }

    public static void main(String[] args) {
        int[] arr = {1, 3, 2, 6, -1, 4, 1, 8, 2};
        double[] avgs = findAverages(arr, 5);
        System.out.print("Averages of k=5: ");
        for (double avg : avgs) {
            System.out.printf("%.1f ", avg);
        }
        System.out.println("(Expected: 2.2 2.8 2.4 3.6 2.8)");
    }
}
