/*
 * Problem Statement:
 * Given an absolute path for a Unix-style file system, which begins with a slash '/',
 * transform this path into its simplified canonical path.
 * In a Unix-style file system:
 * - A period '.' refers to the current directory.
 * - A double period '..' refers to the directory up a level.
 * - Any multiple consecutive slashes '//' are treated as a single slash '/'.
 * (LeetCode 71: Simplify Path)
 * 
 * Example 1:
 * Input: path = "/home/"
 * Output: "/home"
 * 
 * Example 2:
 * Input: path = "/home//foo/"
 * Output: "/home/foo"
 * 
 * Example 3:
 * Input: path = "/home/user/Documents/../Pictures"
 * Output: "/home/user/Pictures"
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Deque;

class SimplifyFilePathUnixStack {

    public static String simplifyPath(String path) {
        Deque<String> stack = new ArrayDeque<>();
        String[] parts = path.split("/");

        for (String part : parts) {
            if (part.isEmpty() || part.equals(".")) {
                continue;
            } else if (part.equals("..")) {
                if (!stack.isEmpty()) {
                    stack.pop();
                }
            } else {
                stack.push(part);
            }
        }

        // Build canonical path from bottom of stack
        StringBuilder canonical = new StringBuilder();
        while (!stack.isEmpty()) {
            canonical.append("/").append(stack.pollLast());
        }

        return canonical.length() == 0 ? "/" : canonical.toString();
    }

    public static void main(String[] args) {
        String[] testPaths = {
            "/home/",
            "/../",
            "/home//foo/",
            "/home/user/Documents/../Pictures",
            "/a/./b/../../c/"
        };

        System.out.println("--- Simplify Canonical UNIX File Path ---");
        for (String p : testPaths) {
            System.out.printf("Raw: %-35s -> Canonical: %s%n", "\"" + p + "\"", simplifyPath(p));
        }
    }
}

/*
 * Time Complexity: O(N) where N is length of path string.
 * Space Complexity: O(N) stack storage for path tokens.
 */
