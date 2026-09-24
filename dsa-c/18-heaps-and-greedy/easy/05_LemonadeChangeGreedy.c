/**
 * Problem: Lemonade Change (LeetCode 860)
 * Asked in: Amazon, Google
 * 
 * At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy
 * from you and order one at a time. Each customer will only buy one lemonade and pay with
 * either a $5, $10, or $20 bill. You must provide the correct change to each customer.
 * Return true if you can provide every customer with the correct change.
 * 
 * Approach:
 * Greedy Change Strategy:
 * Keep track of counts of $5 bills and $10 bills ($20 bills cannot be given as change).
 * - Customer pays $5: fiveCount++
 * - Customer pays $10: needs $5 change -> if fiveCount > 0, fiveCount--, tenCount++ else return false.
 * - Customer pays $20: needs $15 change.
 *   Greedy Choice: Always prefer giving (one $10 + one $5) over (three $5) bills,
 *   because $5 bills are strictly more versatile!
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

bool lemonadeChange(int* bills) {
        int five = 0;
        int ten = 0;

        for (size_t _idx = 0; _idx < sizeof(bills)/sizeof(bills[0]); _idx++) {
        int bill = bills[_idx];
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            } else { // bill == 20
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }

        return true;
    }

    int main(void) {
        int* bills1 = {5, 5, 5, 10, 20};
        printf("Can provide change 1: " + lemonadeChange(bills1) + " (Expected: true)\n");

        int* bills2 = {5, 5, 10, 10, 20};
        printf("Can provide change 2: " + lemonadeChange(bills2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
