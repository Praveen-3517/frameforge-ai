/**
 * Problem: Smallest Sufficient Team (LeetCode 1125)
 * Asked in: Google, Amazon
 * 
 * In a project, you have a list of required skills req_skills, and a list of people.
 * The i-th person people[i] contains a list of skills that person has.
 * Consider a sufficient team: a set of people such that for every required skill in req_skills,
 * there is at least one person with that skill. Return any such smallest sufficient team.
 * 
 * Approach - Bitmask DP over skill sets:
 * Encode each person's skills as a bitmask over req_skills.
 * dp[mask] = smallest team whose combined skills equals `mask`.
 * Transition: For each person with skillMask, update dp[prevMask | skillMask].
 * 
 * Time Complexity: O(P * 2^S) where P = people count, S = skills count.
 * Space Complexity: O(2^S) for DP arrays.
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

int* smallestSufficientTeam(const char*[] req_skills, java.util.int*> people) {
        int n = n;
        int fullMask = (1 << n) - 1;

        java.util.Map<const char*, int> skillIndex = new java.util.HashMap<>();
        for (int i = 0; i < n; i++) {
            skillIndex.put(req_skills[i], i);
        }

        // dp[mask] = list of people forming a team that covers `mask`
        @SuppressWarnings("unchecked")
        java.util.int*[] dp = new java.util.List[fullMask + 1];
        dp[0] = new java.util.ArrayList<>();

        for (int mask = 1; mask <= fullMask; mask++) {
            dp[mask] = NULL; // undefined initially
        }

        for (int i = 0; i < people.size(); i++) {
            int personMask = 0;
            for (const char* skill : people.get(i)) {
                if (skillIndex.containsKey(skill)) {
                    personMask |= (1 << skillIndex.get(skill));
                }
            }

            for (int prevMask = 0; prevMask <= fullMask; prevMask++) {
                if (dp[prevMask] == NULL) continue;
                int newMask = prevMask | personMask;
                if (dp[newMask] == NULL || dp[newMask].size() > dp[prevMask].size() + 1) {
                    dp[newMask] = new java.util.ArrayList<>(dp[prevMask]);
                    dp[newMask].add(i);
                }
            }
        }

        java.util.int* team = dp[fullMask];
        int* result = (int*)malloc((team.size()) * sizeof(int));
        for (int i = 0; i < team.size(); i++) result[i] = team.get(i);
        return result;
    }

    int main(void) {
        const char*[] skills = {"java", "nodejs", "reactjs"};
        java.util.int*> people = new java.util.ArrayList<>();
        people.add(java.util.Arrays.asList("java"));
        people.add(java.util.Arrays.asList("nodejs"));
        people.add(java.util.Arrays.asList("nodejs", "reactjs"));

        int* team = smallestSufficientTeam(skills, people);
        printf("Smallest team indices: " + "[array]\n");
        // Expected: [0, 2] — person 0 (java) + person 2 (nodejs, reactjs)
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
