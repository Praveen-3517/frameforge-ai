/**
 * Problem Statement:
 * In a project, you have a list of required skills `req_skills`, and a list of `people`.
 * The i-th person `people.get(i)` has a list of skills they possess.
 * A sufficient team is a set of people such that every skill in `req_skills` is covered
 * by at least one person.
 * Return any sufficient team of the smallest possible size, represented by people indices.
 * Constraints: req_skills.length <= 16, people.length <= 60.
 * (LeetCode 1125: Smallest Sufficient Team).
 *
 * Asked in: Google, Airbnb, Amazon, Apple
 *
 * Approach:
 * - Bitmask Dynamic Programming:
 *   With `req_skills.length <= 16`, any subset of skills is represented by a 16-bit mask [0, 2^16 - 1].
 *   Target state: `targetMask = (1 << numSkills) - 1` (all skills acquired).
 * - State Definition:
 *   `dp[skillMask]` stores the minimum list of person indices that cover `skillMask`.
 *   Initialize `dp[0] = empty list`.
 * - Transitions:
 *   For each person `i` with bitmask `personMask`:
 *     For each existing `skillMask` in `dp`:
 *       `newSkillMask = skillMask | personMask`
 *       If `dp[newSkillMask]` is empty OR `dp[skillMask].size() + 1 < dp[newSkillMask].size()`:
 *         `dp[newSkillMask] = new list from dp[skillMask] + i`
 * - Final Answer: `dp[targetMask]`.
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

int* smallestSufficientTeam(const char*[] reqSkills, int*> people) {
        int n = n;
        int totalSkillsMask = 1 << n;

        // Map skill name to bit position
        Map<const char*, int> skillToId = new HashMap<>();
        for (int i = 0; i < n; i++) {
            skillToId.put(reqSkills[i], i);
        }

        // Convert each person's skills into a bitmask
        int m = people.size();
        int* personSkillMask = (int*)malloc((m) * sizeof(int));
        for (int i = 0; i < m; i++) {
            int mask = 0;
            for (const char* skill : people.get(i)) {
                if (skillToId.containsKey(skill)) {
                    mask |= (1 << skillToId.get(skill));
                }
            }
            personSkillMask[i] = mask;
        }

        // dp[mask] stores the list of person indices for that skill mask
        @SuppressWarnings("unchecked")
        int*[] dp = new ArrayList[totalSkillsMask];
        dp[0] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            int pMask = personSkillMask[i];
            if (pMask == 0) continue; // Skip person with no relevant skills

            for (int prevMask = 0; prevMask < totalSkillsMask; prevMask++) {
                if (dp[prevMask] == NULL) continue;

                int combinedMask = prevMask | pMask;
                if (dp[combinedMask] == NULL || dp[prevMask].size() + 1 < dp[combinedMask].size()) {
                    int* newTeam = new ArrayList<>(dp[prevMask]);
                    newTeam.add(i);
                    dp[combinedMask] = newTeam;
                }
            }
        }

        int* bestTeamList = dp[totalSkillsMask - 1];
        int* result = (int*)malloc((bestTeamList.size()) * sizeof(int));
        for (int i = 0; i < bestTeamList.size(); i++) {
            result[i] = bestTeamList.get(i);
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 1125: Smallest Sufficient Team (Bitmask DP) ===\n");

        const char*[] reqSkills = { "java", "nodejs", "reactjs" };
        int*> people = new ArrayList<>();
        people.add(Arrays.asList("java"));                    // Person 0
        people.add(Arrays.asList("nodejs"));                  // Person 1
        people.add(Arrays.asList("nodejs", "reactjs"));       // Person 2

        int* team = smallestSufficientTeam(reqSkills, people);
        printf("Required Skills: " + "[array]\n");
        printf("People Skills  : %d\n", people);
        printf("Optimal Team (Person Indices): " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(M * 2^N) where N = number of skills (<= 16) and M = number of people (<= 60).
 * Space Complexity: O(2^N * N) - DP array storing person indices for each skill state.
 */
