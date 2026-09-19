/**
 * Problem Statement:
 * Demonstrate the fundamental Java bitwise operators:
 * 1. Bitwise AND (&), OR (|), XOR (^), NOT (~)
 * 2. Left Shift (<<), Signed Right Shift (>>), Unsigned Right Shift (>>>)
 * 3. Display operands and results in full 32-bit binary representation.
 *
 * Asked in: Amazon, Goldman Sachs, Cisco, Intel
 *
 * Approach:
 * - AND (&): 1 only if both bits are 1. Useful for clearing/masking bits.
 * - OR (|): 1 if at least one bit is 1. Useful for setting bits.
 * - XOR (^): 1 if bits differ. Useful for toggling bits and finding unique elements.
 * - NOT (~): Inverts all bits (~x = -x - 1 in two's complement).
 * - Left Shift (<<): Shifts bits left, fills with 0 on right (multiplication by 2^k).
 * - Signed Right Shift (>>): Shifts bits right, replicates MSB (division by 2^k preserving sign).
 * - Unsigned Right Shift (>>>): Shifts bits right, always fills 0 on MSB.
 */
class BitwiseBasicOperations {

    public static String toBinary32(int n) {
        return String.format("%32s", Integer.toBinaryString(n)).replace(' ', '0');
    }

    public static void printOp(String label, int val) {
        System.out.printf("%-18s: %11d | Binary: %s%n", label, val, toBinary32(val));
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Bitwise Operators Truth Tables & Shift Demo ===");

        int a = 12; // 00001100
        int b = 25; // 00011001

        printOp("Operand a", a);
        printOp("Operand b", b);
        System.out.println("-------------------------------------------------------------------------");
        printOp("a & b (AND)", a & b);
        printOp("a | b (OR)", a | b);
        printOp("a ^ b (XOR)", a ^ b);
        printOp("~a (NOT)", ~a);

        System.out.println("\n----------------- Shift Operators with Negative Numbers -----------------");
        int neg = -16;
        printOp("Operand neg", neg);
        printOp("neg << 2", neg << 2);
        printOp("neg >> 2 (Signed)", neg >> 2);
        printOp("neg >>> 2 (Unsigned)", neg >>> 2);
    }
}

/*
 * Time Complexity: O(1) - Bitwise CPU instruction operations.
 * Space Complexity: O(1) - Constant stack space.
 */
