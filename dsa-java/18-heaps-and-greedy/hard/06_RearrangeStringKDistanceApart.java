import java.util.ArrayDeque;
import java.util.PriorityQueue;
import java.util.Queue;

/**
 * Problem: Rearrange String k Distance Apart (LeetCode 358)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given a string s and an integer k, rearrange s such that the same characters
 * are at least distance k from each other. If not possible, return "".
 * 
 * Approach:
 * Max-Heap with FIFO Cooldown Queue:
 * 1. Count character frequencies.
 * 2. Max-Heap stores [char, count] ordered by count descending.
 * 3. A cooldown queue stores characters that cannot be reused until k characters have been placed.
 * 4. In each step:
 *    - Extract highest-frequency available char from Max-Heap.
 *    - Append to result and decrement count.
 *    - Push [char, count] into cooldown queue.
 *    - If cooldown queue size == k:
 *      - Pop head from cooldown queue; if its remaining count > 0, reinsert into Max-Heap.
 * 5. If result.length() == s.length(), return result string; else return "".
 * 
 * Time Complexity: O(N log 26) = O(N)
 * Space Complexity: O(26) = O(1)
 */
class RearrangeStringKDistanceApart {

    public static String rearrangeString(String s, int k) {
        if (k <= 1) return s;

        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> Integer.compare(b[1], a[1]));
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                maxHeap.offer(new int[]{i + 'a', count[i]});
            }
        }

        Queue<int[]> cooldownQueue = new ArrayDeque<>();
        StringBuilder sb = new StringBuilder();

        while (!maxHeap.isEmpty()) {
            int[] current = maxHeap.poll();
            sb.append((char) current[0]);
            current[1]--; // one instance used

            cooldownQueue.offer(current);

            // Once k characters have elapsed, release the oldest cooled down character
            if (cooldownQueue.size() >= k) {
                int[] released = cooldownQueue.poll();
                if (released[1] > 0) {
                    maxHeap.offer(released);
                }
            }
        }

        return sb.length() == s.length() ? sb.toString() : "";
    }

    public static void main(String[] args) {
        System.out.println("Result (k=3): " + rearrangeString("aabbcc", 3)); // e.g. "abcabc"
        System.out.println("Result (k=2): " + rearrangeString("aaabc", 2));  // e.g. "" or "abaca"
        System.out.println("Result (k=3): " + rearrangeString("aaadbbcc", 2));
    }
}
