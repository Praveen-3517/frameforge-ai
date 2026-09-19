import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem: Substring with Concatenation of All Words (LeetCode 30)
 * Category: Fixed Sliding Window | Hard
 * Asked in: Amazon, Google, Microsoft
 * 
 * You are given a string s and an array of strings words. All the strings of words are of the
 * same length. A concatenated substring in s is a substring that contains all the strings of
 * any permutation of words concatenated.
 * Return the starting indices of all the concatenated substrings in s.
 * 
 * Approach - Sliding Window per Offset + HashMap:
 * Each word has length wordLen. Total window size = wordLen * words.length.
 * Run wordLen separate sliding windows (offsets 0 to wordLen-1).
 * For each window, maintain word frequency using a sliding-word window.
 * 
 * Time Complexity: O(N * wordLen) where N = s.length
 * Space Complexity: O(words.length)
 */
class SubstringConcatenationAllWords {

    public static List<Integer> findSubstring(String s, String[] words) {
        List<Integer> result = new ArrayList<>();
        if (s.isEmpty() || words.length == 0) return result;

        int wordLen = words[0].length();
        int numWords = words.length;
        int totalLen = wordLen * numWords;

        // Build word frequency map
        Map<String, Integer> wordFreq = new HashMap<>();
        for (String w : words) wordFreq.merge(w, 1, Integer::sum);

        for (int offset = 0; offset < wordLen; offset++) {
            Map<String, Integer> windowFreq = new HashMap<>();
            int left = offset;
            int matchCount = 0; // words matched so far

            for (int right = offset; right + wordLen <= s.length(); right += wordLen) {
                String word = s.substring(right, right + wordLen);

                if (wordFreq.containsKey(word)) {
                    windowFreq.merge(word, 1, Integer::sum);
                    matchCount++;

                    // If this word appears more times than needed, shrink left
                    while (windowFreq.get(word) > wordFreq.get(word)) {
                        String leftWord = s.substring(left, left + wordLen);
                        windowFreq.merge(leftWord, -1, Integer::sum);
                        matchCount--;
                        left += wordLen;
                    }

                    if (matchCount == numWords) {
                        result.add(left);
                        // Slide window by one word
                        String leftWord = s.substring(left, left + wordLen);
                        windowFreq.merge(leftWord, -1, Integer::sum);
                        matchCount--;
                        left += wordLen;
                    }
                } else {
                    // Unknown word — reset window
                    windowFreq.clear();
                    matchCount = 0;
                    left = right + wordLen;
                }
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println(findSubstring("barfoothefoobarman", new String[]{"foo", "bar"}));
        // Expected: [0, 9]
        System.out.println(findSubstring("wordgoodgoodgoodbestword", new String[]{"word", "good", "best", "word"}));
        // Expected: []
        System.out.println(findSubstring("barfoofoobarthefoobarman", new String[]{"bar", "foo", "the"}));
        // Expected: [6, 9, 12]
    }
}
