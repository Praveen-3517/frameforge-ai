/*
 * Problem Statement:
 * Given an array of integers temperatures represents the daily temperatures, return an array
 * answer such that answer[i] is the number of days you have to wait after the i-th day to get
 * a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0.
 * (LeetCode 739: Daily Temperatures)
 * 
 * Example:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class DailyTemperaturesMonotonicStack {

    /**
     * Approach:
     * Monotonic Decreasing Stack of Indices:
     * - Iterate through temperatures:
     *   - While stack is not empty and temperatures[i] > temperatures[stack.peek()]:
     *     - warmer day found! idx = stack.pop(); result[idx] = i - idx;
     *   - Push index i onto stack.
     */
    public static int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Stores indices

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevDay = stack.pop();
                result[prevDay] = i - prevDay;
            }
            stack.push(i);
        }

        return result;
    }

    public static void main(String[] args) {
        int[] temps = {73, 74, 75, 71, 69, 72, 76, 73};

        System.out.println("Temperatures: " + Arrays.toString(temps));
        System.out.println("Wait days:    " + Arrays.toString(dailyTemperatures(temps)));
    }
}

/*
 * Time Complexity: O(N) - Each index pushed and popped at most once.
 * Space Complexity: O(N) monotonic index stack.
 */
