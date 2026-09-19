import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Queue;

/**
 * Problem: Course Schedule II (LeetCode 210)
 * Asked in: Amazon, Google, Microsoft, Facebook, Apple
 * 
 * Return the ordering of courses you should take to finish all courses.
 * If there are multiple valid orders, return any of them.
 * If it is impossible to finish all courses, return an empty array.
 * 
 * Approach:
 * Kahn's Algorithm (Topological Sort BFS):
 * Record each node in an array `order` as it is popped with inDegree 0.
 * If total popped equals numCourses, return `order`; else return empty array `int[0]`.
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */
class CourseScheduleTwoTopologicalOrder {

    public static int[] findOrder(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adj = new ArrayList<>(numCourses);
        for (int i = 0; i < numCourses; i++) {
            adj.add(new ArrayList<>());
        }

        int[] inDegree = new int[numCourses];
        for (int[] pre : prerequisites) {
            adj.get(pre[1]).add(pre[0]);
            inDegree[pre[0]]++;
        }

        Queue<Integer> queue = new ArrayDeque<>();
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }

        int[] order = new int[numCourses];
        int idx = 0;

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            order[idx++] = curr;

            for (int neighbor : adj.get(curr)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return idx == numCourses ? order : new int[0];
    }

    public static void main(String[] args) {
        int[][] pre = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
        int[] order = findOrder(4, pre);
        System.out.println("Course order: " + Arrays.toString(order));
        // Valid order: [0, 1, 2, 3] or [0, 2, 1, 3]
    }
}
