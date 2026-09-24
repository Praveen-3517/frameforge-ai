/*
 * Problem Statement:
 * Demonstrate NavigableMap operations using `java.util.TreeMap`:
 * - Find nearest matches using:
 *   - `floorKey(k)`: greatest key <= k
 *   - `ceilingKey(k)`: least key >= k
 *   - `lowerKey(k)`: greatest key < k
 *   - `higherKey(k)`: least key > k
 * - Reverse iteration using `descendingMap()`.
 * 
 * Asked in: Goldman Sachs, Morgan Stanley, Google, Citadel
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

int main(void) {
        // Timestamp (milliseconds) -> Event Name
        TreeMap<int, const char*> eventTimeline = new TreeMap<>();
        eventTimeline.put(100, "User Login");
        eventTimeline.put(250, "Added Item to Cart");
        eventTimeline.put(400, "Initiated Checkout");
        eventTimeline.put(600, "Payment Processed");
        eventTimeline.put(900, "Order Confirmation Sent");

        printf("--- TreeMap Navigable Timeline ---\n");
        printf("All events: %d\n", eventTimeline);

        int queryTime = 350;
        printf("\nQuerying nearest events around timestamp " + queryTime + "ms:\n");
        printf("  floorKey (<= 350):   %d -> %d\n", eventTimeline.floorKey(queryTime), eventTimeline.get(eventTimeline.floorKey(queryTime)));
        printf("  ceilingKey (>= 350): %d -> %d\n", eventTimeline.ceilingKey(queryTime), eventTimeline.get(eventTimeline.ceilingKey(queryTime)));
        printf("  lowerKey (< 250):    %d\n", eventTimeline.lowerKey(250));
        printf("  higherKey (> 600):   %d\n", eventTimeline.higherKey(600));

        printf("\n--- Descending Timeline ---\n");
        eventTimeline.descendingMap().forEach((k, v) -> printf("  %3dms : %s\n", k, v));
        return 0;
}

/*
 * Time Complexity: O(log N) for all floorKey, ceilingKey, lowerKey, higherKey searches.
 * Space Complexity: O(N) red-black tree entries.
 */
