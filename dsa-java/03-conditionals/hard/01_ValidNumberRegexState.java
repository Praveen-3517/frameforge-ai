/**
 * Problem Statement:
 * Given a string `s`, determine if `s` is a valid number.
 * A valid number can be an integer or a decimal number, optionally followed by an exponent ('e' or 'E').
 * Rules:
 *   - Sign: optional leading '+' or '-' before digits or dot, or after exponent.
 *   - Decimal: digits + dot, digits + dot + digits, or dot + digits.
 *   - Exponent: 'e' or 'E' followed by a valid signed or unsigned integer.
 *   - Any other character (letters, spaces, extra dots/signs) makes it invalid.
 * (LeetCode 65: Valid Number - Hard).
 *
 * Asked in: LinkedIn, Facebook / Meta, Google, Microsoft
 *
 * Approach:
 * - Deterministic Finite Automaton (DFA) / State Machine:
 *   Input character groups:
 *     0: Digit (0-9)
 *     1: Sign (+ / -)
 *     2: Dot (.)
 *     3: Exponent (e / E)
 *   State Definitions:
 *     State 0: Initial starting state
 *     State 1: Sign before number (e.g. "+", "-")
 *     State 2: Integer digits before dot (e.g. "123") [VALID]
 *     State 3: Dot preceded by digits (e.g. "123.") [VALID]
 *     State 4: Dot not preceded by digits (e.g. ".") [NEEDS DIGIT]
 *     State 5: Fractional digits after dot (e.g. ".5", "12.34") [VALID]
 *     State 6: Exponent marker (e.g. "12e", ".5E") [NEEDS INT]
 *     State 7: Sign after exponent (e.g. "12e+", "12e-") [NEEDS DIGIT]
 *     State 8: Exponent integer digits (e.g. "12e5", "12e-4") [VALID]
 *     State -1: Trap / Invalid state
 *   Valid accepting states: { 2, 3, 5, 8 }.
 */
class ValidNumberRegexState {

    // DFA Transition Table: transitionTable[state][charGroup]
    // charGroup: 0: Digit, 1: Sign, 2: Dot, 3: Exponent
    private static final int[][] DFA = {
        // State 0: Start
        { 2, 1, 4, -1 },
        // State 1: Sign before number
        { 2, -1, 4, -1 },
        // State 2: Digits before dot [ACCEPT]
        { 2, -1, 3, 6 },
        // State 3: Dot with digits before [ACCEPT]
        { 5, -1, -1, 6 },
        // State 4: Dot without digits before
        { 5, -1, -1, -1 },
        // State 5: Digits after dot [ACCEPT]
        { 5, -1, -1, 6 },
        // State 6: Exponent symbol
        { 8, 7, -1, -1 },
        // State 7: Sign after exponent
        { 8, -1, -1, -1 },
        // State 8: Digits after exponent [ACCEPT]
        { 8, -1, -1, -1 }
    };

    private static int getCharGroup(char ch) {
        if (ch >= '0' && ch <= '9') return 0;
        if (ch == '+' || ch == '-') return 1;
        if (ch == '.')              return 2;
        if (ch == 'e' || ch == 'E') return 3;
        return -1; // Illegal character
    }

    public static boolean isNumber(String s) {
        int state = 0;

        for (int i = 0; i < s.length(); i++) {
            int group = getCharGroup(s.charAt(i));
            if (group == -1) {
                return false;
            }

            state = DFA[state][group];
            if (state == -1) {
                return false; // Trapped in invalid state
            }
        }

        // Must end in an accepting state: 2, 3, 5, or 8
        return state == 2 || state == 3 || state == 5 || state == 8;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 65: Valid Number (Deterministic Finite Automaton) ===");

        String[] validExamples = {
            "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"
        };

        String[] invalidExamples = {
            "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", ".", ".-4"
        };

        System.out.println("--- Valid Test Cases ---");
        for (String s : validExamples) {
            System.out.printf("%-15s ==> %s%n", "\"" + s + "\"", isNumber(s));
        }

        System.out.println("\n--- Invalid Test Cases ---");
        for (String s : invalidExamples) {
            System.out.printf("%-15s ==> %s%n", "\"" + s + "\"", isNumber(s));
        }
    }
}

/*
 * Time Complexity: O(N) - Exactly one DFA state transition lookup per character.
 * Space Complexity: O(1) - Constant size transition table and state integer.
 */
