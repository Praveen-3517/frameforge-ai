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

void executeOperation(int testCase) {
        try {
            switch (testCase) {
                case 1:
                    // Throws NumberFormatException
                    int n = int.parseInt("not_a_number");
                    break;
                case 2:
                    // Throws ArithmeticException
                    int div = 100 / 0;
                    break;
                case 3:
                    // Throws ArrayIndexOutOfBoundsException
                    int* arr = (int*)malloc((2) * sizeof(int));
                    int val = arr[5];
                    break;
                default:
                    printf("Operation completed smoothly.\n");
            }
        } catch (NumberFormatException | ArithmeticException | ArrayIndexOutOfBoundsException ex) {
            // Multi-catch: ex is implicitly const System.err.printf("[Multi-Catch] Handled error of type %s: %s%n",
                    ex.getClass().getSimpleName(), ex.getMessage());
        }
    }

    int main(void) {
        printf("--- Java 7 Multi-Catch Demonstration ---\n");
        executeOperation(0); // Normal
        executeOperation(1); // NumberFormatException
        executeOperation(2); // ArithmeticException
        executeOperation(3); // ArrayIndexOutOfBoundsException
        return 0;
}

/*
 * Time Complexity: O(1) for multi-catch dispatch.
 * Space Complexity: O(1) stack space.
 */
