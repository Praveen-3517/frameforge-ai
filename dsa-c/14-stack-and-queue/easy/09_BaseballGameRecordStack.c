/*
 * Problem Statement:
 * You are keeping score for a baseball game with strange rules:
 * - Integer x: Record a new score of x.
 * - "+": Record a new score that is the sum of previous two scores.
 * - "D": Record a new score that is double the previous score.
 * - "C": Invalidate and remove the previous score.
 * Return the sum of all the scores on the record after applying all operations.
 * (LeetCode 682: Baseball Game)
 * 
 * Example:
 * Input: ops = ["5","2","C","D","+"]
 * Output: 30
 * 
 * Asked in: Amazon, Bloomberg, Morgan Stanley
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

int calPoints(const char*[] operations) {
        Deque<int> stack = new ArrayDeque<>();

        for (const char* op : operations) {
            switch (op) {
                case "+":
                    int top = stack.pop();
                    int newTop = top + stack.peek();
                    stack.push(top);
                    stack.push(newTop);
                    break;
                case "D":
                    stack.push(2 * stack.peek());
                    break;
                case "C":
                    stack.pop();
                    break;
                default:
                    stack.push(int.parseInt(op));
                    break;
            }
        }

        int total = 0;
        for (int score : stack) total += score;
        return total;
    }

    int main(void) {
        const char*[] ops1 = {"5", "2", "C", "D", "+"};
        printf("Operations: [\"5\",\"2\",\"C\",\"D\",\"+\"] -> Total points: " + calPoints(ops1) + " (Expected: 30)\n");

        const char*[] ops2 = {"5", "-2", "4", "C", "D", "9", "+", "+"};
        printf("Operations 2 -> Total points: " + calPoints(ops2) + " (Expected: 27)\n");
        return 0;
}

/*
 * Time Complexity: O(N) where N is operations count.
 * Space Complexity: O(N) score history stack.
 */
