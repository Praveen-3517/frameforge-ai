/*
 * Problem Statement:
 * A k-booking happens when k events have some non-empty intersection.
 * Implement the MyCalendarThree class:
 * - book(int startTime, int endTime): Returns an integer k representing the largest
 *   integer such that there exists a k-booking in the calendar so far.
 * (LeetCode 732: My Calendar III)
 * 
 * Example:
 * book(10, 20) -> 1
 * book(50, 60) -> 1
 * book(10, 40) -> 2
 * book(5, 15)  -> 3
 * book(5, 10)  -> 3
 * book(25, 55) -> 3
 * 
 * Asked in: Google, Uber, Amazon, Citadel
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

static class MyCalendarThree {
        // TreeMap tracks boundary deltas: +1 at start, -1 at end
        static const TreeMap<int, int> timeline;

        MyCalendarThree() {
            timeline = new TreeMap<>();
        }

        int book(int startTime, int endTime) {
            // Add +1 at interval start
            timeline.put(startTime, timeline.getOrDefault(startTime, 0) + 1);
            // Add -1 at interval end
            timeline.put(endTime, timeline.getOrDefault(endTime, 0) - 1);

            int ongoingEvents = 0;
            int maxKBooking = 0;

            // Sweep line algorithm: iterate chronologically across all timestamps
            for (int delta : timeline.values()) {
                ongoingEvents += delta;
                maxKBooking = MAX(maxKBooking, ongoingEvents);
            }

            return maxKBooking;
        }
    }

    int main(void) {
        MyCalendarThree cal = new MyCalendarThree();

        int** bookings = {
            {10, 20},
            {50, 60},
            {10, 40},
            {5, 15},
            {5, 10},
            {25, 55}
        };

        printf("--- My Calendar III (Sweep Line with TreeMap) ---\n");
        for (int* b : bookings) {
            int k = cal.book(b[0], b[1]);
            printf("Booked [%2d, %2d) -> Max simultaneous overlap (k-booking): %d\n",
                    b[0], b[1], k);
        }
        return 0;
}

/*
 * Time Complexity: O(N^2) total across N bookings (each book sweeps the N-entry TreeMap in O(N)).
 * Space Complexity: O(N) to store event endpoints in the TreeMap.
 */
