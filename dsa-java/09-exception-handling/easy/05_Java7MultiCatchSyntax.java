/*
 * Problem Statement:
 * Demonstrate Java 7 Multi-Catch syntax (`catch (TypeA | TypeB ex)`):
 * - Eliminates code duplication when multiple unrelated exceptions require identical handling.
 * - Key Rule: The multi-catch variable `ex` is implicitly `final` and cannot be reassigned.
 * - Subclasses and superclasses cannot be combined in the same multi-catch pipe
 *   (e.g., `catch (FileNotFoundException | IOException e)` is a compiler error).
 * 
 * Asked in: Oracle, Amazon, IBM, Mindtree
 */

class Java7MultiCatchSyntax {

    public static void executeOperation(int testCase) {
        try {
            switch (testCase) {
                case 1:
                    // Throws NumberFormatException
                    int n = Integer.parseInt("not_a_number");
                    break;
                case 2:
                    // Throws ArithmeticException
                    int div = 100 / 0;
                    break;
                case 3:
                    // Throws ArrayIndexOutOfBoundsException
                    int[] arr = new int[2];
                    int val = arr[5];
                    break;
                default:
                    System.out.println("Operation completed smoothly.");
            }
        } catch (NumberFormatException | ArithmeticException | ArrayIndexOutOfBoundsException ex) {
            // Multi-catch: ex is implicitly final
            System.err.printf("[Multi-Catch] Handled error of type %s: %s%n",
                    ex.getClass().getSimpleName(), ex.getMessage());
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Java 7 Multi-Catch Demonstration ---");
        executeOperation(0); // Normal
        executeOperation(1); // NumberFormatException
        executeOperation(2); // ArithmeticException
        executeOperation(3); // ArrayIndexOutOfBoundsException
    }
}

/*
 * Time Complexity: O(1) for multi-catch dispatch.
 * Space Complexity: O(1) stack space.
 */
