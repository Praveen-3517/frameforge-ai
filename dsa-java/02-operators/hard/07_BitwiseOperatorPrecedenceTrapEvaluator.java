/**
 * Problem Statement:
 * Analyze, demonstrate, and evaluate the top 6 legendary Java operator precedence traps
 * that trip up candidates in technical interviews.
 * Implement an automated precedence verification suite that compares common developer assumptions
 * against the actual Java Language Specification (JLS) evaluation rules.
 *
 * Asked in: Oracle, Microsoft, Systems Architect & Core Java Engineering Rounds
 *
 * The 6 Classic Traps:
 * 1. Shift vs Additive:
 *    `1 << 2 + 3` evaluates as `1 << (2 + 3) = 32`, NOT `(1 << 2) + 3 = 7`!
 * 2. Bitwise AND vs Equality:
 *    `if (n & 1 == 0)` fails to compile because `==` has higher precedence than `&`.
 *    The compiler interprets it as `n & (1 == 0)` (int & boolean), which is illegal!
 *    Correct: `(n & 1) == 0`.
 * 3. Logical AND (&&) vs Logical OR (||):
 *    `true || false && false` evaluates as `true || (false && false) = true`,
 *    NOT `(true || false) && false = false`, because `&&` has higher precedence than `||`!
 * 4. Ternary Right-to-Left Associativity:
 *    `a ? b : c ? d : e` associates as `a ? b : (c ? d : e)`.
 * 5. String Concatenation vs Arithmetic Addition:
 *    `"Sum: " + 10 + 20` produces `"Sum: 1020"`, NOT `"Sum: 30"`,
 *    because `+` evaluates strictly Left-to-Right when types are identical.
 * 6. Assignment Compound Evaluation Order:
 *    `a += b += c` evaluates right-to-left.
 */
class BitwiseOperatorPrecedenceTrapEvaluator {

    public static void testTrap1ShiftVsAdd() {
        System.out.println("--- Trap 1: Bit Shift (<<) vs Additive (+) ---");
        int actual = 1 << 2 + 3;
        int intuitiveAssumption = (1 << 2) + 3;
        int jlsStandard = 1 << (2 + 3);

        System.out.println("Expression : 1 << 2 + 3");
        System.out.println("Actual Java Result     : " + actual);
        System.out.println("Naive Developer Guess  : (1 << 2) + 3 = " + intuitiveAssumption);
        System.out.println("JLS Specification Rule : 1 << (2 + 3) = " + jlsStandard);
        System.out.println("Lesson: '+' binds tighter than '<<'! Always parenthesize shifts.\n");
    }

    public static void testTrap2BitwiseVsEquality() {
        System.out.println("--- Trap 2: Bitwise AND (&) vs Equality (==) ---");
        int n = 4; // even
        // boolean illegal = (n & 1 == 0); // COMPILE ERROR: int & boolean
        boolean correct = (n & 1) == 0;
        System.out.println("Expression : (n & 1) == 0 for n = 4");
        System.out.println("Why 'n & 1 == 0' fails: '==' has precedence 7, '&' has precedence 8.");
        System.out.println("Correctly parenthesized: " + correct + "\n");
    }

    public static void testTrap3LogicalAndVsOr() {
        System.out.println("--- Trap 3: Logical AND (&&) vs Logical OR (||) ---");
        boolean actual = true || false && false;
        boolean naive = (true || false) && false;
        boolean jls = true || (false && false);

        System.out.println("Expression : true || false && false");
        System.out.println("Actual Java Result     : " + actual);
        System.out.println("Naive Left-to-Right    : (true || false) && false = " + naive);
        System.out.println("JLS Precedence Rule    : true || (false && false) = " + jls);
        System.out.println("Lesson: '&&' has higher precedence than '||' (just like * and +).\n");
    }

    public static void testTrap4TernaryAssociativity() {
        System.out.println("--- Trap 4: Nested Ternary Associativity (Right-to-Left) ---");
        boolean cond1 = false;
        boolean cond2 = true;
        String res = cond1 ? "A" : cond2 ? "B" : "C";
        System.out.println("Expression : false ? 'A' : true ? 'B' : 'C'");
        System.out.println("Result     : " + res + " (Evaluated as false ? 'A' : (true ? 'B' : 'C'))\n");
    }

    public static void testTrap5StringConcatenation() {
        System.out.println("--- Trap 5: String '+' vs Numeric '+' ---");
        String s1 = "Result: " + 10 + 20;
        String s2 = "Result: " + (10 + 20);
        System.out.println("\"Result: \" + 10 + 20   ==> " + s1);
        System.out.println("\"Result: \" + (10 + 20) ==> " + s2 + "\n");
    }

    public static void main(String[] args) {
        System.out.println("=== Java Operator Precedence Traps & Evaluation Rules ===");
        testTrap1ShiftVsAdd();
        testTrap2BitwiseVsEquality();
        testTrap3LogicalAndVsOr();
        testTrap4TernaryAssociativity();
        testTrap5StringConcatenation();
    }
}

/*
 * Time Complexity: O(1) - Evaluates inline constant expressions.
 * Space Complexity: O(1) - Constant stack frames.
 */
