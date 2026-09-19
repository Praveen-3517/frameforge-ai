/*
 * Problem Statement:
 * Given a positive integer n, generate all 2^n binary strings of length n.
 * 
 * Example:
 * Input: n = 3
 * Output: ["000", "001", "010", "011", "100", "101", "110", "111"]
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
 */

import java.util.ArrayList;
import java.util.List;

class GenerateAllBinaryStringsLengthN {

    public static List<String> generateBinaryStrings(int n) {
        List<String> result = new ArrayList<>();
        char[] current = new char[n];
        backtrack(0, n, current, result);
        return result;
    }

    private static void backtrack(int index, int n, char[] current, List<String> result) {
        if (index == n) {
            result.add(new String(current));
            return;
        }

        // Try '0'
        current[index] = '0';
        backtrack(index + 1, n, current, result);

        // Try '1'
        current[index] = '1';
        backtrack(index + 1, n, current, result);
    }

    public static void main(String[] args) {
        int n = 3;
        List<String> strings = generateBinaryStrings(n);

        System.out.println("Binary strings of length " + n + " (Total = " + strings.size() + "):");
        System.out.println(strings);
    }
}

/*
 * Time Complexity: O(2^N * N) - 2^N strings created, each copied in O(N).
 * Space Complexity: O(N) recursion stack and buffer.
 */
