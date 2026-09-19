/*
 * Problem Statement:
 * Special binary strings are binary strings with two properties:
 * 1. The number of 0's is equal to the number of 1's.
 * 2. Every prefix of the binary string has at least as many 1's as 0's.
 * 
 * You are given a special binary string s. A move consists of choosing two consecutive,
 * non-empty special substrings of s, and swapping them.
 * Return the lexicographically largest resulting string possible after any number of moves.
 * 
 * Example:
 * Input: s = "11011000"
 * Output: "11100100"
 * 
 * Asked in: Google, Citadel, Coursera
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class SpecialBinaryStringRecursion {

    /**
     * Approach:
     * Recursive Divide and Sort:
     * Notice that special strings are isomorphic to valid parentheses strings:
     * '1' = '(', '0' = ')'.
     * Any special string can be decomposed into irreducible special substrings:
     * "1" + innerSpecialString + "0".
     * 
     * Strategy:
     * 1. Split string s into primitive balanced special substrings.
     * 2. Recursively sort inner contents of each primitive string:
     *    "1" + makeLargestSpecial(inner) + "0".
     * 3. Sort the primitive substrings in descending order to achieve lexicographical maximum.
     * 4. Join together.
     */
    public static String makeLargestSpecial(String s) {
        int count = 0;
        int i = 0;
        List<String> list = new ArrayList<>();

        for (int j = 0; j < s.length(); j++) {
            if (s.charAt(j) == '1') count++;
            else count--;

            if (count == 0) {
                // Irreducible block found from i to j: 1 + inner + 0
                String inner = s.substring(i + 1, j);
                list.add("1" + makeLargestSpecial(inner) + "0");
                i = j + 1;
            }
        }

        // Sort descending
        list.sort(Collections.reverseOrder());
        return String.join("", list);
    }

    public static void main(String[] args) {
        String[] testCases = {
            "11011000",
            "10",
            "1100",
            "1010"
        };

        System.out.println("--- Special Binary String Recursive Optimizer ---");
        for (String s : testCases) {
            System.out.printf("Original: %-12s -> Largest: %s%n", s, makeLargestSpecial(s));
        }
    }
}

/*
 * Time Complexity: O(N^2) - Substring splitting and recursive string joins.
 * Space Complexity: O(N) - Storing substrings and call stack frames.
 */
