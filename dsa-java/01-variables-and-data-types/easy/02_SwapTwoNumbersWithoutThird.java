/**
 * Problem Statement:
 * Swap two numerical variables without using any temporary third variable.
 * Demonstrate two standard approaches:
 * 1. Arithmetic Addition & Subtraction (caution: overflow risks)
 * 2. Bitwise XOR Operator (immune to arithmetic overflow)
 *
 * Asked in: TCS, Cognizant, Wipro, Infosys
 *
 * Approach:
 * Method 1 (Arithmetic):
 *   a = a + b
 *   b = a - b   // (a + b) - b = a
 *   a = a - b   // (a + b) - a = b
 *
 * Method 2 (Bitwise XOR):
 *   a = a ^ b
 *   b = a ^ b   // (a ^ b) ^ b = a
 *   a = a ^ b   // (a ^ b) ^ a = b
 *
 * XOR is preferred because it avoids integer overflow when numbers are large.
 */
class SwapTwoNumbersWithoutThird {

    public static void swapUsingArithmetic(int a, int b) {
        System.out.println("Before Arithmetic Swap: a = " + a + ", b = " + b);
        a = a + b;
        b = a - b;
        a = a - b;
        System.out.println("After Arithmetic Swap:  a = " + a + ", b = " + b);
    }

    public static void swapUsingXor(int a, int b) {
        System.out.println("Before XOR Swap:        a = " + a + ", b = " + b);
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        System.out.println("After XOR Swap:         a = " + a + ", b = " + b);
    }

    public static void main(String[] args) {
        System.out.println("=== Test Case 1: Standard Positive Numbers ===");
        swapUsingArithmetic(15, 25);
        System.out.println();
        swapUsingXor(15, 25);

        System.out.println("\n=== Test Case 2: Negative Numbers ===");
        swapUsingArithmetic(-10, 40);
        System.out.println();
        swapUsingXor(-10, 40);

        System.out.println("\n=== Test Case 3: Large Integers (Testing Overflow Safety of XOR) ===");
        int x = Integer.MAX_VALUE - 5;
        int y = Integer.MAX_VALUE - 10;
        // Arithmetic swap might trigger silent two's complement wrap-around, but XOR operates strictly bitwise
        swapUsingXor(x, y);
    }
}

/*
 * Time Complexity: O(1) - Constant time 3-operation assignment sequence.
 * Space Complexity: O(1) - In-place manipulation with zero extra memory allocated.
 */
