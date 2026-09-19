/**
 * Problem Statement:
 * Implement a simple command-line calculator that takes two operands `a` and `b`
 * and an operator character (+, -, *, /, %, ^ for power) and returns the evaluated result.
 * Safely guard against division and modulo by zero using conditionals.
 *
 * Asked in: TCS, Wipro, Capgemini, Accenture
 *
 * Approach:
 * - Use modern switch expression with yield/arrow syntax.
 * - Operator cases:
 *   '+' -> a + b
 *   '-' -> a - b
 *   '*' -> a * b
 *   '/' -> guard against b == 0, then a / b
 *   '%' -> guard against b == 0, then a % b
 *   '^' -> Math.pow(a, b)
 *   default -> throw IllegalArgumentException
 */
class SimpleCalculatorSwitch {

    public static double calculate(double a, double b, char op) {
        return switch (op) {
            case '+' -> a + b;
            case '-' -> a - b;
            case '*' -> a * b;
            case '/' -> {
                if (b == 0.0) {
                    throw new ArithmeticException("Division by zero is undefined.");
                }
                yield a / b;
            }
            case '%' -> {
                if (b == 0.0) {
                    throw new ArithmeticException("Modulo by zero is undefined.");
                }
                yield a % b;
            }
            case '^' -> Math.pow(a, b);
            default  -> throw new IllegalArgumentException("Unsupported operator: '" + op + "'");
        };
    }

    public static void main(String[] args) {
        System.out.println("=== Modern Java Switch-Based Arithmetic Calculator ===");

        Object[][] testCalculations = {
            { 10.0, 4.0, '+' },
            { 15.5, 3.5, '-' },
            { 6.0, 7.0, '*' },
            { 22.0, 7.0, '/' },
            { 17.0, 5.0, '%' },
            { 2.0, 8.0, '^' },
            { 10.0, 0.0, '/' } // Division by zero test
        };

        for (Object[] row : testCalculations) {
            double a = (double) row[0];
            double b = (double) row[1];
            char op = (char) row[2];

            try {
                double result = calculate(a, b, op);
                System.out.printf("%.1f %c %.1f = %.4f%n", a, op, b, result);
            } catch (Exception e) {
                System.out.printf("%.1f %c %.1f ==> Exception Caught: %s%n", a, op, b, e.getMessage());
            }
        }
    }
}

/*
 * Time Complexity: O(1) - Constant branch evaluation.
 * Space Complexity: O(1) - Stack variables only.
 */
