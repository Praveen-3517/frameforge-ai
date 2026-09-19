import java.util.PriorityQueue;

/**
 * Problem: Reorganize String (LeetCode 767)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given a string s, rearrange the characters of s so that any two adjacent characters
 * are not the same. Return any possible rearrangement of s or return "" if not possible.
 * 
 * Approach:
 * Greedy Max-Heap Strategy:
 * 1. Count character frequencies. If any char count > (s.length() + 1) / 2, return "".
 * 2. Put [char, count] in a Max-Heap ordered by count descending.
 * 3. Pop the two most frequent distinct characters at a time:
 *    - Append first and second to result.
 *    - Decrement their counts.
 *    - Push back into Max-Heap if count > 0.
 * 4. If 1 character remains, append it to the end.
 * 
 * Time Complexity: O(N log A) where A is alphabet size (26) -> O(N).
 * Space Complexity: O(A) -> O(1).
 */
class ReorganizeStringGreedyHeap {

    public static String reorganizeString(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> Integer.compare(b[1], a[1]));
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                if (count[i] > (s.length() + 1) / 2) return "";
                maxHeap.offer(new int[]{i + 'a', count[i]});
            }
        }

        StringBuilder sb = new StringBuilder();
        while (maxHeap.size() >= 2) {
            int[] first = maxHeap.poll();
            int[] second = maxHeap.poll();

            sb.append((char) first[0]);
            sb.append((char) second[0]);

            if (--first[1] > 0) maxHeap.offer(first);
            if (--second[1] > 0) maxHeap.offer(second);
        }

        if (!maxHeap.isEmpty()) {
            sb.append((char) maxHeap.poll()[0]);
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("Reorganized 'aab': " + reorganizeString("aab") + " (Expected: aba)");
        System.out.println("Reorganized 'aaab': " + reorganizeString("aaab") + " (Expected: \"\")");
    }
}
