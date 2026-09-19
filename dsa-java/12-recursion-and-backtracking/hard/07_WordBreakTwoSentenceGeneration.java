/*
 * Problem Statement:
 * Given a string s and a dictionary of strings wordDict, add spaces in s to construct
 * a sentence where each word is a valid dictionary word. Return all such possible sentences
 * in any order.
 * (LeetCode 140: Word Break II)
 * 
 * Example:
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 * 
 * Asked in: Amazon, Google, Bloomberg, Microsoft
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

class WordBreakTwoSentenceGeneration {

    public static List<String> wordBreak(String s, List<String> wordDict) {
        Set<String> dict = new HashSet<>(wordDict);
        Map<String, List<String>> memo = new HashMap<>();
        return dfs(s, dict, memo);
    }

    private static List<String> dfs(String s, Set<String> dict, Map<String, List<String>> memo) {
        if (memo.containsKey(s)) return memo.get(s);

        List<String> res = new ArrayList<>();
        if (s.isEmpty()) {
            res.add("");
            return res;
        }

        for (String word : dict) {
            if (s.startsWith(word)) {
                String sub = s.substring(word.length());
                List<String> subSentences = dfs(sub, dict, memo);

                for (String sentence : subSentences) {
                    res.add(word + (sentence.isEmpty() ? "" : " ") + sentence);
                }
            }
        }

        memo.put(s, res);
        return res;
    }

    public static void main(String[] args) {
        String s = "catsanddog";
        List<String> wordDict = Arrays.asList("cat", "cats", "and", "sand", "dog");

        System.out.println("String: \"" + s + "\"");
        System.out.println("Valid sentences: " + wordBreak(s, wordDict));
    }
}

/*
 * Time Complexity: O(2^N * N) - Bounded by valid output sentences count.
 * Space Complexity: O(2^N * N) to store memoized sentences.
 */
