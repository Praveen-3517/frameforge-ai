/**
 * Problem: Assign Cookies (LeetCode 455)
 * Asked in: Amazon, Google
 * 
 * Assume you are an awesome parent and want to give your children some cookies.
 * But, you should give each child at most one cookie.
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * If s[j] >= g[i], we can assign cookie j to child i, and child i will be content.
 * Maximize the number of your content children.
 * 
 * Approach:
 * Greedy Two Pointers:
 * 1. Sort children greed array g and cookie size array s ascending.
 * 2. Greedily satisfy the child with the smallest greed factor using the smallest cookie that fits.
 * 
 * Time Complexity: O(N log N + M log M)
 * Space Complexity: O(1) auxiliary space (ignoring sort stack).
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

int findContentChildren(int* g, int* s) {
        Arrays.sort(g);
        Arrays.sort(s);

        int child = 0;
        int cookie = 0;

        while (child < n && cookie < n) {
            if (s[cookie] >= g[child]) {
                child++; // Child satisfied
            }
            cookie++; // Move to next cookie regardless
        }

        return child;
    }

    int main(void) {
        int* g1 = {1, 2, 3};
        int* s1 = {1, 1};
        printf("Content children 1: " + findContentChildren(g1, s1) + " (Expected: 1)\n");

        int* g2 = {1, 2};
        int* s2 = {1, 2, 3};
        printf("Content children 2: " + findContentChildren(g2, s2) + " (Expected: 2)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
