/*
 * Problem Statement:
 * Demonstrate multiple catch blocks and inheritance hierarchy ordering:
 * - Specific exceptions (subclasses) MUST be caught BEFORE general exceptions (superclasses).
 * - Putting superclass `Exception` first causes compiler error: "unreachable catch block".
 * - Process a pipeline that can throw NumberFormatException, ArithmeticException, or NullPointerException.
 * 
 * Asked in: Oracle, Infosys, Morgan Stanley, Adobe
 */

class MultipleCatchAndPrecedenceOrder {

    public static void parseAndDivide(String textNum, int divisor) {
        try {
            System.out.println("Processing input: \"" + textNum + "\" with divisor " + divisor);
            int value = Integer.parseInt(textNum); // Can throw NumberFormatException
            int result = value / divisor;          // Can throw ArithmeticException
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            // Specific catch 1
            System.err.println("  [Handled NumberFormatException] Invalid integer format: " + e.getMessage());
        } catch (ArithmeticException e) {
            // Specific catch 2
            System.err.println("  [Handled ArithmeticException] Math error: " + e.getMessage());
        } catch (NullPointerException e) {
            // Specific catch 3
            System.err.println("  [Handled NullPointerException] Input was null!");
        } catch (Exception e) {
            // General catch-all fallback must be LAST
            System.err.println("  [Handled General Exception] Unexpected error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Multiple Catch Blocks Demo ---");
        parseAndDivide("42", 2);      // Success: 21
        parseAndDivide("abc", 2);     // Triggers NumberFormatException
        parseAndDivide("42", 0);      // Triggers ArithmeticException
        parseAndDivide(null, 5);      // Triggers NullPointerException
    }
}

/*
 * Time Complexity: O(1) for parsing and error catching.
 * Space Complexity: O(1) stack space.
 */
