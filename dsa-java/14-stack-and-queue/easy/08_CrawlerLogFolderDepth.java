/*
 * Problem Statement:
 * The Leetcode file system keeps a log each time, some user performs a change folder operation.
 * Operations:
 * - "../" : Move to parent folder (stay at main if already at main).
 * - "./"  : Remain in current folder.
 * - "x/"  : Move to child folder named x.
 * Return the minimum number of operations needed to go back to the main folder after all logs.
 * (LeetCode 1598: Crawler Log Folder)
 * 
 * Example:
 * Input: logs = ["d1/","d2/","../","d21/","./"]
 * Output: 2
 * 
 * Asked in: Amazon, Microsoft, Cisco
 */

class CrawlerLogFolderDepth {

    public static int minOperations(String[] logs) {
        int depth = 0;

        for (String log : logs) {
            if (log.equals("../")) {
                depth = Math.max(0, depth - 1);
            } else if (!log.equals("./")) {
                depth++;
            }
        }

        return depth;
    }

    public static void main(String[] args) {
        String[] logs1 = {"d1/", "d2/", "../", "d21/", "./"};
        System.out.println("Logs: [\"d1/\",\"d2/\",\"../\",\"d21/\",\"./\"] -> Min steps: " + minOperations(logs1));

        String[] logs2 = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
        System.out.println("Logs: [\"d1/\",\"d2/\",\"./\",\"d3/\",\"../\",\"d31/\"] -> Min steps: " + minOperations(logs2));
    }
}

/*
 * Time Complexity: O(N) where N is the number of log entries.
 * Space Complexity: O(1) integer depth counter simulates stack height without heap allocation.
 */
