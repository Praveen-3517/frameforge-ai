import java.util.Arrays;

/**
 * Problem: Assign Cookies (LeetCode 455)
 * Asked in: Amazon, Google
 * 
 * Assume you are an awesome parent and want to give your children some cookies.
 * But, you should give each child at most one cookie.
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * If s[j] >= g[i], we can assign cookie j to child i, and child i will be content.
 * Maximize the number of your content children.
 * 
 * Approach:
 * Greedy Two Pointers:
 * 1. Sort children greed array g and cookie size array s ascending.
 * 2. Greedily satisfy the child with the smallest greed factor using the smallest cookie that fits.
 * 
 * Time Complexity: O(N log N + M log M)
 * Space Complexity: O(1) auxiliary space (ignoring sort stack).
 */
class AssignCookiesGreedy {

    public static int findContentChildren(int[] g, int[] s) {
        Arrays.sort(g);
        Arrays.sort(s);

        int child = 0;
        int cookie = 0;

        while (child < g.length && cookie < s.length) {
            if (s[cookie] >= g[child]) {
                child++; // Child satisfied
            }
            cookie++; // Move to next cookie regardless
        }

        return child;
    }

    public static void main(String[] args) {
        int[] g1 = {1, 2, 3};
        int[] s1 = {1, 1};
        System.out.println("Content children 1: " + findContentChildren(g1, s1) + " (Expected: 1)");

        int[] g2 = {1, 2};
        int[] s2 = {1, 2, 3};
        System.out.println("Content children 2: " + findContentChildren(g2, s2) + " (Expected: 2)");
    }
}
