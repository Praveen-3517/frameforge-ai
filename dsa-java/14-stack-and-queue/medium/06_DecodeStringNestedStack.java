/*
 * Problem Statement:
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square
 * brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; there are no extra white spaces,
 * square brackets are well-formed, etc.
 * (LeetCode 394: Decode String)
 * 
 * Example 1:
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 * 
 * Example 2:
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 * 
 * Asked in: Google, Bloomberg, Cisco, Amazon
 */

import java.util.ArrayDeque;
import java.util.Deque;

class DecodeStringNestedStack {

    public static String decodeString(String s) {
        Deque<Integer> countStack = new ArrayDeque<>();
        Deque<StringBuilder> stringStack = new ArrayDeque<>();
        StringBuilder currentString = new StringBuilder();
        int k = 0;

        for (char ch : s.toCharArray()) {
            if (Character.isDigit(ch)) {
                k = k * 10 + (ch - '0');
            } else if (ch == '[') {
                // Push current count and string buffer onto stacks
                countStack.push(k);
                stringStack.push(currentString);
                // Reset
                currentString = new StringBuilder();
                k = 0;
            } else if (ch == ']') {
                // Decode segment
                StringBuilder decodedPart = stringStack.pop();
                int repeatTimes = countStack.pop();
                for (int i = 0; i < repeatTimes; i++) {
                    decodedPart.append(currentString);
                }
                currentString = decodedPart;
            } else {
                currentString.append(ch);
            }
        }

        return currentString.toString();
    }

    public static void main(String[] args) {
        String[] testCases = {
            "3[a]2[bc]",
            "3[a2[c]]",
            "2[abc]3[cd]ef"
        };

        System.out.println("--- Decode Nested String ---");
        for (String test : testCases) {
            System.out.printf("Encoded: %-15s -> Decoded: %s%n", "\"" + test + "\"", decodeString(test));
        }
    }
}

/*
 * Time Complexity: O(Total characters in decoded output).
 * Space Complexity: O(Total length of output string + nesting depth).
 */
