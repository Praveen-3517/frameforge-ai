import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
class SmallestSufficientTeamBitmaskDP {

    public static int[] smallestSufficientTeam(String[] reqSkills, List<List<String>> people) {
        int n = reqSkills.length;
        int totalSkillsMask = 1 << n;

        // Map skill name to bit position
        Map<String, Integer> skillToId = new HashMap<>();
        for (int i = 0; i < n; i++) {
            skillToId.put(reqSkills[i], i);
        }

        // Convert each person's skills into a bitmask
        int m = people.size();
        int[] personSkillMask = new int[m];
        for (int i = 0; i < m; i++) {
            int mask = 0;
            for (String skill : people.get(i)) {
                if (skillToId.containsKey(skill)) {
                    mask |= (1 << skillToId.get(skill));
                }
            }
            personSkillMask[i] = mask;
        }

        // dp[mask] stores the list of person indices for that skill mask
        @SuppressWarnings("unchecked")
        List<Integer>[] dp = new ArrayList[totalSkillsMask];
        dp[0] = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            int pMask = personSkillMask[i];
            if (pMask == 0) continue; // Skip person with no relevant skills

            for (int prevMask = 0; prevMask < totalSkillsMask; prevMask++) {
                if (dp[prevMask] == null) continue;

                int combinedMask = prevMask | pMask;
                if (dp[combinedMask] == null || dp[prevMask].size() + 1 < dp[combinedMask].size()) {
                    List<Integer> newTeam = new ArrayList<>(dp[prevMask]);
                    newTeam.add(i);
                    dp[combinedMask] = newTeam;
                }
            }
        }

        List<Integer> bestTeamList = dp[totalSkillsMask - 1];
        int[] result = new int[bestTeamList.size()];
        for (int i = 0; i < bestTeamList.size(); i++) {
            result[i] = bestTeamList.get(i);
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 1125: Smallest Sufficient Team (Bitmask DP) ===");

        String[] reqSkills = { "java", "nodejs", "reactjs" };
        List<List<String>> people = new ArrayList<>();
        people.add(Arrays.asList("java"));                    // Person 0
        people.add(Arrays.asList("nodejs"));                  // Person 1
        people.add(Arrays.asList("nodejs", "reactjs"));       // Person 2

        int[] team = smallestSufficientTeam(reqSkills, people);
        System.out.println("Required Skills: " + Arrays.toString(reqSkills));
        System.out.println("People Skills  : " + people);
        System.out.println("Optimal Team (Person Indices): " + Arrays.toString(team));
    }
}

/*
 * Time Complexity: O(M * 2^N) where N = number of skills (<= 16) and M = number of people (<= 60).
 * Space Complexity: O(2^N * N) - DP array storing person indices for each skill state.
 */
