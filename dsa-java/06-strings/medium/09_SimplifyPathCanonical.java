import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem Statement:
 * Given an absolute path for a Unix-style file system, which begins with a slash '/',
 * transform this path into its simplified canonical path.
 * Unix Path Rules:
 *   - A single period '.' refers to the current directory (ignore).
 *   - A double period '..' refers to the parent directory (pop previous folder).
 *   - Multiple consecutive slashes '//' are treated as a single slash '/'.
 *   - Any other format of periods (e.g. '...') is treated as a valid directory/file name.
 * Canonical path format:
 *   - Must start with a single '/'.
 *   - Directories must be separated by exactly one '/'.
 *   - Must NOT end with a trailing '/', unless it is the root directory.
 * (LeetCode 71: Simplify Path).
 *
 * Example:
 * "/home/"            -> "/home"
 * "/../"              -> "/"
 * "/home//foo/"       -> "/home/foo"
 * "/a/./b/../../c/"   -> "/c"
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Deque Stack Token Processing:
 *   Split the path by slash delimiter: `path.split("/")`.
 *   Maintain `Deque<String> stack`:
 *   - If token is empty `""` or `"."`: do nothing (stay in current directory).
 *   - If token is `".."`: if stack is not empty, pop the top directory `stack.pollLast()`.
 *   - Any other valid directory name: push onto stack `stack.addLast(token)`.
 *   Join all directory tokens from stack separated by `'/'`.
 */
class SimplifyPathCanonical {

    public static String simplifyPath(String path) {
        if (path == null || path.isEmpty()) return "/";

        Deque<String> stack = new ArrayDeque<>();
        String[] tokens = path.split("/");

        for (String token : tokens) {
            if (token.isEmpty() || token.equals(".")) {
                continue;
            } else if (token.equals("..")) {
                if (!stack.isEmpty()) {
                    stack.pollLast();
                }
            } else {
                stack.addLast(token);
            }
        }

        if (stack.isEmpty()) {
            return "/";
        }

        StringBuilder sb = new StringBuilder();
        for (String dir : stack) {
            sb.append("/").append(dir);
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 71: Simplify Unix File Path (Stack) ===");

        String[] testPaths = {
            "/home/",
            "/../",
            "/home//foo/",
            "/a/./b/../../c/",
            "/a/../../b/../c//.//",
            "/a//b////c/d//././/.."
        };

        for (String p : testPaths) {
            System.out.printf("Original: %-25s ==> Canonical: \"%s\"%n",
                    "\"" + p + "\"", simplifyPath(p));
        }
    }
}

/*
 * Time Complexity: O(N) - Splits and processes each path component once.
 * Space Complexity: O(N) - Deque storing directory segments.
 */
