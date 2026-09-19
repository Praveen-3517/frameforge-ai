/**
 * Problem: Find the Town Judge (LeetCode 997)
 * Asked in: Amazon, Microsoft, Bloomberg
 * 
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these
 * people is secretly the town judge. If the town judge exists:
 * 1. The town judge trusts nobody.
 * 2. Everybody (except for the town judge) trusts the town judge.
 * 3. There is exactly one person that satisfies properties 1 and 2.
 * Given trust[i] = [a, b], return the label of the town judge if they exist, or -1.
 * 
 * Approach:
 * Directed Graph In-Degree & Out-Degree:
 * - If person `a` trusts `b`, `a` has out-degree + 1, and `b` has in-degree + 1.
 * - Net trust score: score[person] = inDegree - outDegree.
 * - The judge must be trusted by n - 1 people (inDegree = n - 1) and trust 0 people (outDegree = 0).
 * - Therefore, judge's net score must be exactly n - 1.
 * 
 * Time Complexity: O(V + E) where V = n and E = trust.length.
 * Space Complexity: O(n) for the score array.
 */
class FindJudgeInTown {

    public static int findJudge(int n, int[][] trust) {
        int[] score = new int[n + 1];

        for (int[] relation : trust) {
            score[relation[0]]--; // out-degree decreases score
            score[relation[1]]++; // in-degree increases score
        }

        for (int i = 1; i <= n; i++) {
            if (score[i] == n - 1) {
                return i;
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        int[][] trust1 = {{1, 2}};
        System.out.println("Judge: " + findJudge(2, trust1) + " (Expected: 2)");

        int[][] trust2 = {{1, 3}, {2, 3}};
        System.out.println("Judge: " + findJudge(3, trust2) + " (Expected: 3)");

        int[][] trust3 = {{1, 3}, {2, 3}, {3, 1}};
        System.out.println("Judge: " + findJudge(3, trust3) + " (Expected: -1)");
    }
}
