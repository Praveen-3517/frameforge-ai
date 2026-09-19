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

import java.util.HashMap;
import java.util.Map;

class DesignUndergroundSystem {

    static class CheckInRecord {
        String stationName;
        int checkInTime;

        CheckInRecord(String stationName, int checkInTime) {
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
        private final Map<Integer, CheckInRecord> checkIns = new HashMap<>();

        // Route Key ("StartStation->EndStation") -> RouteStats
        private final Map<String, RouteStats> routeStats = new HashMap<>();

        public void checkIn(int id, String stationName, int t) {
            checkIns.put(id, new CheckInRecord(stationName, t));
        }

        public void checkOut(int id, String stationName, int t) {
            CheckInRecord start = checkIns.remove(id);
            if (start == null) return;

            String routeKey = start.stationName + "->" + stationName;
            routeStats.computeIfAbsent(routeKey, k -> new RouteStats()).recordTrip(t - start.checkInTime);
        }

        public double getAverageTime(String startStation, String endStation) {
            String routeKey = startStation + "->" + endStation;
            RouteStats stats = routeStats.get(routeKey);
            return stats != null ? stats.getAverage() : 0.0;
        }
    }

    public static void main(String[] args) {
        UndergroundSystem subway = new UndergroundSystem();

        subway.checkIn(45, "Leyton", 3);
        subway.checkIn(32, "Paradise", 8);
        subway.checkIn(27, "Leyton", 10);

        subway.checkOut(45, "Waterloo", 15);  // Leyton->Waterloo took 15 - 3 = 12
        subway.checkOut(27, "Waterloo", 20);  // Leyton->Waterloo took 20 - 10 = 10
        subway.checkOut(32, "Cambridge", 22); // Paradise->Cambridge took 22 - 8 = 14

        System.out.println("--- Underground System Average Commute Times ---");
        System.out.printf("Average Leyton -> Waterloo:    %.2f (Expected: 11.00)%n",
                subway.getAverageTime("Leyton", "Waterloo"));
        System.out.printf("Average Paradise -> Cambridge: %.2f (Expected: 14.00)%n",
                subway.getAverageTime("Paradise", "Cambridge"));
    }
}

/*
 * Time Complexity: O(1) for checkIn, checkOut, and getAverageTime.
 * Space Complexity: O(P + R) where P is active passengers and R is distinct station pairs.
 */
