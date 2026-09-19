/**
 * Problem Statement:
 * Given a single character, determine whether it is a:
 * 1. Vowel (A, E, I, O, U, case-insensitive)
 * 2. Consonant
 * 3. Non-alphabetic character (digit, punctuation, symbol)
 * Demonstrate using both traditional `switch` with intentional fall-through and modern switch expressions.
 *
 * Asked in: TCS, Infosys, Accenture, Cognizant
 *
 * Approach:
 * - Character normalization: Convert input character to lowercase using `Character.toLowerCase(ch)`.
 * - First check if character is alphabetic using `Character.isLetter(ch)`.
 * - Switch fall-through:
 *   In traditional switch:
 *   `case 'a': case 'e': case 'i': case 'o': case 'u': return "Vowel";`
 * - In modern switch:
 *   `case 'a', 'e', 'i', 'o', 'u' -> "Vowel";`
 */
class VowelOrConsonant {

    public static String classifyChar(char ch) {
        if (!Character.isLetter(ch)) {
            return "Non-Alphabetic Symbol";
        }

        char lower = Character.toLowerCase(ch);

        return switch (lower) {
            case 'a', 'e', 'i', 'o', 'u' -> "Vowel";
            default -> "Consonant";
        };
    }

    public static void main(String[] args) {
        System.out.println("=== Character Classification: Vowel, Consonant, or Symbol ===");

        char[] testChars = { 'a', 'E', 'z', 'M', '7', '@', ' ', 'u', 'Y' };

        for (char ch : testChars) {
            System.out.printf("Char: '%c' ==> %s%n", ch, classifyChar(ch));
        }
    }
}

/*
 * Time Complexity: O(1) - Single character lookup.
 * Space Complexity: O(1) - Constant stack registers.
 */
