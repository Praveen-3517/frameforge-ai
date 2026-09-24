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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

void testTrap1ShiftVsAdd() {
        printf("--- Trap 1: Bit Shift (<<) vs Additive (+) ---\n");
        int actual = 1 << 2 + 3;
        int intuitiveAssumption = (1 << 2) + 3;
        int jlsStandard = 1 << (2 + 3);

        printf("Expression : 1 << 2 + 3\n");
        printf("Actual Java Result     : %d\n", actual);
        printf("%d%d%d\n", "Naive Developer Guess  : (1 << 2), 3 = ", intuitiveAssumption);
        printf("%d%d%d\n", "JLS Specification Rule : 1 << (2, 3) = ", jlsStandard);
        printf("Lesson: '+' binds tighter than '<<'! Always parenthesize shifts.\n\n");
    }

    void testTrap2BitwiseVsEquality() {
        printf("--- Trap 2: Bitwise AND (&) vs Equality (==) ---\n");
        int n = 4; // even
        // bool illegal = (n & 1 == 0); // COMPILE ERROR: int & bool
        bool correct = (n & 1) == 0;
        printf("Expression : (n & 1) == 0 for n = 4\n");
        printf("Why 'n & 1 == 0' fails: '==' has precedence 7, '&' has precedence 8.\n");
        printf("Correctly parenthesized: " + correct + "\n\n");
    }

    void testTrap3LogicalAndVsOr() {
        printf("--- Trap 3: Logical AND (&&) vs Logical OR (||) ---\n");
        bool actual = true || false && false;
        bool naive = (true || false) && false;
        bool jls = true || (false && false);

        printf("Expression : true || false && false\n");
        printf("Actual Java Result     : %d\n", actual);
        printf("Naive Left-to-Right    : (true || false) && false = %d\n", naive);
        printf("JLS Precedence Rule    : true || (false && false) = %d\n", jls);
        printf("Lesson: '&&' has higher precedence than '||' (just like * and +).\n\n");
    }

    void testTrap4TernaryAssociativity() {
        printf("--- Trap 4: Nested Ternary Associativity (Right-to-Left) ---\n");
        bool cond1 = false;
        bool cond2 = true;
        const char* res = cond1 ? "A" : cond2 ? "B" : "C";
        printf("Expression : false ? 'A' : true ? 'B' : 'C'\n");
        printf("Result     : " + res + " (Evaluated as false ? 'A' : (true ? 'B' : 'C'))\n\n");
    }

    void testTrap5StringConcatenation() {
        printf("--- Trap 5: const char* '+' vs Numeric '+' ---\n");
        const char* s1 = "Result: " + 10 + 20;
        const char* s2 = "Result: " + (10 + 20);
        printf("\"Result: \%d%d%d\n", 10, 20   ==> ", s1);
        printf("\"Result: \" + (10 + 20) ==> " + s2 + "\n\n");
    }

    int main(void) {
        printf("=== Java Operator Precedence Traps & Evaluation Rules ===\n");
        testTrap1ShiftVsAdd();
        testTrap2BitwiseVsEquality();
        testTrap3LogicalAndVsOr();
        testTrap4TernaryAssociativity();
        testTrap5StringConcatenation();
        return 0;
}

/*
 * Time Complexity: O(1) - Evaluates inline constant expressions.
 * Space Complexity: O(1) - Constant stack frames.
 */
