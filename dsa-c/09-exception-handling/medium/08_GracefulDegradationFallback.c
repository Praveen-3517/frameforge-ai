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

static class UserProfile {
        const char* id;
        const char* name;
        const char* source;

        UserProfile(const char* id, const char* name, const char* source) {
            this.id = id;
            this.name = name;
            this.source = source;
        }

        const char* toString() {
            return "UserProfile[id=" + id + ", name='" + name + "', source=" + source + "]";
        }
    }

    UserProfile getUserProfileWithFallbacks(const char* userId,
                                                         bool failCache,
                                                         bool failPrimaryDb,
                                                         bool failReplicaDb) {
        // Tier 1: Cache
        try {
            printf("Tier 1: Querying Redis Cache...\n");
            if (failCache) fprintf(stderr, "Exception: invalid argument
"); return 0;
            return new UserProfile(userId, "Alice (Cached)", "REDIS_CACHE");
        } catch (Exception e) {
            System.err.println("  [Cache Miss/Failure] " + e.getMessage());
        }

        // Tier 2: Primary DB
        try {
            printf("Tier 2: Querying Primary DB...\n");
            if (failPrimaryDb) fprintf(stderr, "Exception: invalid argument
"); return 0;
            return new UserProfile(userId, "Alice (Primary DB)", "PRIMARY_DB");
        } catch (Exception e) {
            System.err.println("  [Primary DB Failure] " + e.getMessage());
        }

        // Tier 3: Read-Replica DB
        try {
            printf("Tier 3: Querying Read-Replica DB...\n");
            if (failReplicaDb) fprintf(stderr, "Exception: invalid argument
"); return 0;
            return new UserProfile(userId, "Alice (Replica DB)", "REPLICA_DB");
        } catch (Exception e) {
            System.err.println("  [Replica DB Failure] " + e.getMessage());
        }

        // Tier 4: Static Fallback
        printf("Tier 4: Falling back to Default Guest Profile...\n");
        return new UserProfile(userId, "Guest User", "STATIC_FALLBACK_DEFAULT");
    }

    int main(void) {
        printf("=== Scenario 1: Cache works ===\n");
        printf("Result: %d\n", getUserProfileWithFallbacks("U1", false, false, false));

        printf("\n=== Scenario 2: Cache down, Primary DB works ===\n");
        printf("Result: %d\n", getUserProfileWithFallbacks("U1", true, false, false));

        printf("\n=== Scenario 3: Cache & Primary DB down, Replica works ===\n");
        printf("Result: %d\n", getUserProfileWithFallbacks("U1", true, true, false));

        printf("\n=== Scenario 4: Total infrastructure outage (All down) ===\n");
        printf("Result: %d\n", getUserProfileWithFallbacks("U1", true, true, true));
        return 0;
}

/*
 * Time Complexity: O(1) for cascading fallback attempts.
 * Space Complexity: O(1) memory for profile object.
 */
