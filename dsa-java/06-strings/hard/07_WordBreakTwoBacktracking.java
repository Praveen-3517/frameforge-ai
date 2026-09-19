import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem Statement:
 * Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct
 * a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
 * (LeetCode 140: Word Break II - Hard).
 *
 * Example:
 * s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 * Asked in: Amazon, Bloomberg, Google, Microsoft
 *
 * Approach:
 * - DFS Backtracking with Top-Down Memoization:
 *   Let `dfs(s)` return a list of all valid sentence segmentations for string `s`.
 *   - Use `Map<String, List<String>> memo` to cache results for suffixes of `s` (prevents redundant subproblem recomputation).
 *   - Base Case: If `s.isEmpty()`, return a list with an empty string `[""]`.
 *   - Transitions:
 *     For each `word` in `wordDict`:
 *       If `s.startsWith(word)`:
 *         String suffix = `s.substring(word.length())`.
 *         Recursively call `List<String> subSentences = dfs(suffix)`.
 *         For each sentence `sub` in `subSentences`:
 *           `result.add(word + (sub.isEmpty() ? "" : " ") + sub)`.
 *     Store `memo.put(s, result)` and return `result`.
 */
class WordBreakTwoBacktracking {

    public static List<String> wordBreak(String s, List<String> wordDict) {
        return dfs(s, wordDict, new HashMap<>());
    }

    private static List<String> dfs(String s, List<String> wordDict, Map<String, List<String>> memo) {
        if (memo.containsKey(s)) {
            return memo.get(s);
        }

        List<String> result = new ArrayList<>();

        if (s.isEmpty()) {
            result.add("");
            return result;
        }

        for (String word : wordDict) {
            if (s.startsWith(word)) {
                String suffix = s.substring(word.length());
                List<String> subList = dfs(suffix, wordDict, memo);

                for (String sub : subList) {
                    result.add(word + (sub.isEmpty() ? "" : " ") + sub);
                }
            }
        }

        memo.put(s, result);
        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 140: Word Break II (DFS + Memoization) ===");

        String s = "catsanddog";
        List<String> dict = Arrays.asList("cat", "cats", "and", "sand", "dog");

        List<String> sentences = wordBreak(s, dict);

        System.out.println("Input String: " + s);
        System.out.println("Dictionary  : " + dict);
        System.out.println("Valid Sentences:");
        for (String sent : sentences) {
            System.out.println("  -> \"" + sent + "\"");
        }
    }
}

/*
 * Time Complexity: O(2^N) in worst case with all possible splits, bounded by memoized substring DAG.
 * Space Complexity: O(2^N) - Storage for memoized sentences and recursion stack.
 */
