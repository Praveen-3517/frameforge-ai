import java.util.Arrays;

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
class SmallestSufficientTeamBitmaskDP {

    public static int[] smallestSufficientTeam(String[] req_skills, java.util.List<java.util.List<String>> people) {
        int n = req_skills.length;
        int fullMask = (1 << n) - 1;

        java.util.Map<String, Integer> skillIndex = new java.util.HashMap<>();
        for (int i = 0; i < n; i++) {
            skillIndex.put(req_skills[i], i);
        }

        // dp[mask] = list of people forming a team that covers `mask`
        @SuppressWarnings("unchecked")
        java.util.List<Integer>[] dp = new java.util.List[fullMask + 1];
        dp[0] = new java.util.ArrayList<>();

        for (int mask = 1; mask <= fullMask; mask++) {
            dp[mask] = null; // undefined initially
        }

        for (int i = 0; i < people.size(); i++) {
            int personMask = 0;
            for (String skill : people.get(i)) {
                if (skillIndex.containsKey(skill)) {
                    personMask |= (1 << skillIndex.get(skill));
                }
            }

            for (int prevMask = 0; prevMask <= fullMask; prevMask++) {
                if (dp[prevMask] == null) continue;
                int newMask = prevMask | personMask;
                if (dp[newMask] == null || dp[newMask].size() > dp[prevMask].size() + 1) {
                    dp[newMask] = new java.util.ArrayList<>(dp[prevMask]);
                    dp[newMask].add(i);
                }
            }
        }

        java.util.List<Integer> team = dp[fullMask];
        int[] result = new int[team.size()];
        for (int i = 0; i < team.size(); i++) result[i] = team.get(i);
        return result;
    }

    public static void main(String[] args) {
        String[] skills = {"java", "nodejs", "reactjs"};
        java.util.List<java.util.List<String>> people = new java.util.ArrayList<>();
        people.add(java.util.Arrays.asList("java"));
        people.add(java.util.Arrays.asList("nodejs"));
        people.add(java.util.Arrays.asList("nodejs", "reactjs"));

        int[] team = smallestSufficientTeam(skills, people);
        System.out.println("Smallest team indices: " + Arrays.toString(team));
        // Expected: [0, 2] — person 0 (java) + person 2 (nodejs, reactjs)
    }
}
