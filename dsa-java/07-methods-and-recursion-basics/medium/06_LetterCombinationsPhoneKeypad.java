/*
 * Problem Statement:
 * Given a string containing digits from 2-9 inclusive, return all possible letter
 * combinations that the number could represent according to classic telephone buttons.
 * Return the answer in any order.
 * 
 * 2 -> "abc", 3 -> "def", 4 -> "ghi", 5 -> "jkl"
 * 6 -> "mno", 7 -> "pqrs", 8 -> "tuv", 9 -> "wxyz"
 * 
 * Example:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * Asked in: Amazon, Google, Uber, Facebook/Meta, Microsoft
 */

import java.util.ArrayList;
import java.util.List;

class LetterCombinationsPhoneKeypad {

    private static final String[] KEYPAD = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    /**
     * Approach:
     * Recursive DFS / Backtracking:
     * For each digit at index in digits string, iterate over mapped letters.
     * Append letter to StringBuilder, recurse for index + 1, and backtrack.
     */
    public static List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();
        if (digits == null || digits.isEmpty()) return result;

        StringBuilder sb = new StringBuilder();
        dfs(digits, 0, sb, result);
        return result;
    }

    private static void dfs(String digits, int index, StringBuilder sb, List<String> result) {
        if (index == digits.length()) {
            result.add(sb.toString());
            return;
        }

        int digit = digits.charAt(index) - '0';
        String letters = KEYPAD[digit];

        for (int i = 0; i < letters.length(); i++) {
            sb.append(letters.charAt(i));
            dfs(digits, index + 1, sb, result);
            sb.deleteCharAt(sb.length() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        String digits = "23";
        List<String> combinations = letterCombinations(digits);
        System.out.println("Digits: \"" + digits + "\"");
        System.out.println("Letter combinations (" + combinations.size() + "): " + combinations);

        String digits2 = "79";
        List<String> combinations2 = letterCombinations(digits2);
        System.out.println("\nDigits: \"" + digits2 + "\"");
        System.out.println("Count (4 * 4 = 16): " + combinations2.size());
    }
}

/*
 * Time Complexity: O(4^N * N) - In worst case (digits 7 and 9), each has 4 letters.
 * Space Complexity: O(N) - Recursion stack depth equals length of digits string.
 */
