/**
 * Problem Statement:
 * Given a valid (IPv4) IP address, return a defanged version of that IP address.
 * A defanged IP address replaces every period "." with "[.]".
 * (LeetCode 1108: Defanging an IP Address).
 *
 * Example:
 * address = "1.1.1.1"         -> "1[.]1[.]1[.]1"
 * address = "255.100.50.0"     -> "255[.]100[.]50[.]0"
 *
 * Asked in: Amazon, Cisco, TCS, Infosys
 *
 * Approach:
 * - StringBuilder Character Traversal (O(N) Time, O(N) Space):
 *   Avoid `address.replaceAll("\\.", "[.]")` regex overhead, which compiles an internal regex pattern.
 *   Directly traverse `address.charAt(i)`:
 *   - If `ch == '.'`: append `"[.]"`
 *   - Else: append `ch`
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

const char* defangIPaddr(const char* address) {
        StringBuilder sb = new StringBuilder(((int)strlen(address)) + 6); // Exactly 3 periods replaced by 3 chars each (+6)

        for (int i = 0; i < ((int)strlen(address)); i++) {
            char ch = address[i];
            if (ch == '.') {
                sb.append("[.]");
            } else {
                sb.append(ch);
            }
        }

        return sb.toString();
    }

    int main(void) {
        printf("=== LeetCode 1108: Defanging an IP Address (StringBuilder) ===\n");

        const char*[] testIPs = { "1.1.1.1", "255.100.50.0", "192.168.1.1", "10.0.0.1" };

        for (const char* ip : testIPs) {
            printf("IP: %-15s ==> Defanged: %s\n", ip, defangIPaddr(ip));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass across characters.
 * Space Complexity: O(N) - Pre-allocated StringBuilder.
 */
