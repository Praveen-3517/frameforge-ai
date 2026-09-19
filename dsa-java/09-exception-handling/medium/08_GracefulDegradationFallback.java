/*
 * Problem Statement:
 * Implement a Resilient Multi-Tier Fallback Pattern (Graceful Degradation):
 * - Tier 1: Try high-speed in-memory cache.
 * - Tier 2: If cache misses or errors out, query primary SQL database.
 * - Tier 3: If primary DB fails (e.g., connection refused), query read-replica database.
 * - Tier 4: If all systems are down, return a stale cached or static fallback default.
 * - Prevent complete system outage by never allowing backend failures to crash the user experience.
 * 
 * Asked in: Netflix, Amazon, Twitter/X, Uber
 */

class GracefulDegradationFallback {

    static class UserProfile {
        String id;
        String name;
        String source;

        UserProfile(String id, String name, String source) {
            this.id = id;
            this.name = name;
            this.source = source;
        }

        @Override
        public String toString() {
            return "UserProfile[id=" + id + ", name='" + name + "', source=" + source + "]";
        }
    }

    public static UserProfile getUserProfileWithFallbacks(String userId,
                                                         boolean failCache,
                                                         boolean failPrimaryDb,
                                                         boolean failReplicaDb) {
        // Tier 1: Cache
        try {
            System.out.println("Tier 1: Querying Redis Cache...");
            if (failCache) throw new RuntimeException("Redis cluster unreachable");
            return new UserProfile(userId, "Alice (Cached)", "REDIS_CACHE");
        } catch (Exception e) {
            System.err.println("  [Cache Miss/Failure] " + e.getMessage());
        }

        // Tier 2: Primary DB
        try {
            System.out.println("Tier 2: Querying Primary DB...");
            if (failPrimaryDb) throw new RuntimeException("Primary DB connection pool exhausted");
            return new UserProfile(userId, "Alice (Primary DB)", "PRIMARY_DB");
        } catch (Exception e) {
            System.err.println("  [Primary DB Failure] " + e.getMessage());
        }

        // Tier 3: Read-Replica DB
        try {
            System.out.println("Tier 3: Querying Read-Replica DB...");
            if (failReplicaDb) throw new RuntimeException("Replica DB read timeout");
            return new UserProfile(userId, "Alice (Replica DB)", "REPLICA_DB");
        } catch (Exception e) {
            System.err.println("  [Replica DB Failure] " + e.getMessage());
        }

        // Tier 4: Static Fallback
        System.out.println("Tier 4: Falling back to Default Guest Profile...");
        return new UserProfile(userId, "Guest User", "STATIC_FALLBACK_DEFAULT");
    }

    public static void main(String[] args) {
        System.out.println("=== Scenario 1: Cache works ===");
        System.out.println("Result: " + getUserProfileWithFallbacks("U1", false, false, false));

        System.out.println("\n=== Scenario 2: Cache down, Primary DB works ===");
        System.out.println("Result: " + getUserProfileWithFallbacks("U1", true, false, false));

        System.out.println("\n=== Scenario 3: Cache & Primary DB down, Replica works ===");
        System.out.println("Result: " + getUserProfileWithFallbacks("U1", true, true, false));

        System.out.println("\n=== Scenario 4: Total infrastructure outage (All down) ===");
        System.out.println("Result: " + getUserProfileWithFallbacks("U1", true, true, true));
    }
}

/*
 * Time Complexity: O(1) for cascading fallback attempts.
 * Space Complexity: O(1) memory for profile object.
 */
