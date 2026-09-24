/*
 * Problem Statement:
 * An underground railway system is keeping track of customer travel times between
 * different stations. Implement the UndergroundSystem class:
 * - checkIn(id, stationName, t)
 * - checkOut(id, stationName, t)
 * - getAverageTime(startStation, endStation)
 * The average time must be computed accurately in O(1) time.
 * 
 * Asked in: Bloomberg, Amazon, Two Sigma, Citadel
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

static class CheckInRecord {
        const char* stationName;
        int checkInTime;

        CheckInRecord(const char* stationName, int checkInTime) {
            this.stationName = stationName;
            this.checkInTime = checkInTime;
        }
    }

    static class RouteStats {
        double totalTime = 0;
        int tripCount = 0;

        void recordTrip(int time) {
            totalTime += time;
            tripCount++;
        }

        double getAverage() {
            return tripCount == 0 ? 0.0 : totalTime / tripCount;
        }
    }

    static class UndergroundSystem {
        // Customer ID -> CheckInRecord
        static const Map<int, CheckInRecord> checkIns = new HashMap<>();

        // Route Key ("StartStation->EndStation") -> RouteStats
        static const Map<const char*, RouteStats> routeStats = new HashMap<>();

        void checkIn(int id, const char* stationName, int t) {
            checkIns.put(id, new CheckInRecord(stationName, t));
        }

        void checkOut(int id, const char* stationName, int t) {
            CheckInRecord start = checkIns.remove(id);
            if (start == NULL) return;

            const char* routeKey = start.stationName + "->" + stationName;
            routeStats.computeIfAbsent(routeKey, k -> new RouteStats()).recordTrip(t - start.checkInTime);
        }

        double getAverageTime(const char* startStation, const char* endStation) {
            const char* routeKey = startStation + "->" + endStation;
            RouteStats stats = routeStats.get(routeKey);
            return stats != NULL ? stats.getAverage() : 0.0;
        }
    }

    int main(void) {
        UndergroundSystem subway = new UndergroundSystem();

        subway.checkIn(45, "Leyton", 3);
        subway.checkIn(32, "Paradise", 8);
        subway.checkIn(27, "Leyton", 10);

        subway.checkOut(45, "Waterloo", 15);  // Leyton->Waterloo took 15 - 3 = 12
        subway.checkOut(27, "Waterloo", 20);  // Leyton->Waterloo took 20 - 10 = 10
        subway.checkOut(32, "Cambridge", 22); // Paradise->Cambridge took 22 - 8 = 14

        printf("--- Underground System Average Commute Times ---\n");
        printf("Average Leyton -> Waterloo:    %.2f (Expected: 11.00)\n",
                subway.getAverageTime("Leyton", "Waterloo"));
        printf("Average Paradise -> Cambridge: %.2f (Expected: 14.00)\n",
                subway.getAverageTime("Paradise", "Cambridge"));
        return 0;
}

/*
 * Time Complexity: O(1) for checkIn, checkOut, and getAverageTime.
 * Space Complexity: O(P + R) where P is active passengers and R is distinct station pairs.
 */
