/*
 * Problem Statement:
 * Handle index out-of-bounds exceptions gracefully:
 * 1. ArrayIndexOutOfBoundsException: Accessing array beyond [0, length-1].
 * 2. StringIndexOutOfBoundsException: Accessing string char or substring beyond [0, length-1].
 * Demonstrate both defensive pre-checking and structured catch handling.
 * 
 * Asked in: Capgemini, Accenture, Mindtree, HCL
 */

class ArrayIndexAndStringBoundsExceptions {

    public static int safeArrayAccess(int[] arr, int index, int defaultValue) {
        try {
            return arr[index];
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.printf("[Caught] Array index %d out of bounds for length %d%n", index, arr.length);
            return defaultValue;
        }
    }

    public static char safeCharAt(String str, int index) {
        try {
            return str.charAt(index);
        } catch (StringIndexOutOfBoundsException e) {
            System.err.printf("[Caught] String index %d out of bounds for string '%s'%n", index, str);
            return '\0'; // NUL character
        }
    }

    public static void main(String[] args) {
        int[] numbers = {10, 20, 30, 40, 50};

        System.out.println("--- Array Access ---");
        System.out.println("Element at index 2:  " + safeArrayAccess(numbers, 2, -1));
        System.out.println("Element at index 10: " + safeArrayAccess(numbers, 10, -1));
        System.out.println("Element at index -1: " + safeArrayAccess(numbers, -1, -1));

        System.out.println("\n--- String Access ---");
        String word = "Java";
        System.out.println("Char at 1:  '" + safeCharAt(word, 1) + "'");
        System.out.println("Char at 10: '" + safeCharAt(word, 10) + "'");
    }
}

/*
 * Time Complexity: O(1) for array and string index lookups.
 * Space Complexity: O(1) auxiliary space.
 */
