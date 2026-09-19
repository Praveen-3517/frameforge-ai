/**
 * Problem: Task Scheduler (LeetCode 621)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given a characters array tasks, representing CPU tasks (A through Z) and non-negative
 * integer n representing the cooling period between identical tasks.
 * Return the minimum number of units of times that the CPU will take to finish all the given tasks.
 * 
 * Approach:
 * Greedy Math / Formula:
 * 1. Find the task with maximum frequency `maxFreq`.
 * 2. Count how many tasks share this maximum frequency `maxCount`.
 * 3. The most frequent tasks define the framing structure:
 *    There are (maxFreq - 1) chunks of length (n + 1), plus the final trailing tasks `maxCount`.
 * 4. The minimum time needed is at least:
 *    (maxFreq - 1) * (n + 1) + maxCount
 * 5. If there are enough other tasks to fill all idle slots, time is simply tasks.length.
 *    Result = max(tasks.length, (maxFreq - 1) * (n + 1) + maxCount).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) for fixed alphabet frequencies (size 26).
 */
class TaskSchedulerIntervals {

    public static int leastInterval(char[] tasks, int n) {
        int[] freq = new int[26];
        int maxFreq = 0;

        for (char t : tasks) {
            freq[t - 'A']++;
            maxFreq = Math.max(maxFreq, freq[t - 'A']);
        }

        int maxCount = 0;
        for (int f : freq) {
            if (f == maxFreq) {
                maxCount++;
            }
        }

        int time = (maxFreq - 1) * (n + 1) + maxCount;
        return Math.max(tasks.length, time);
    }

    public static void main(String[] args) {
        char[] tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
        System.out.println("Least intervals (n=2): " + leastInterval(tasks1, 2) + " (Expected: 8)");
        // A -> B -> idle -> A -> B -> idle -> A -> B

        char[] tasks2 = {'A', 'A', 'A', 'B', 'B', 'B'};
        System.out.println("Least intervals (n=0): " + leastInterval(tasks2, 0) + " (Expected: 6)");
    }
}
