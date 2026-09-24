/**
 * Problem: Clone Graph (LeetCode 133)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.
 * Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
 * 
 * Approach:
 * BFS with HashMap:
 * - Map<Node, Node> visited: maps original node to its newly created cloned node.
 * - Enqueue start node.
 * - While queue is not empty:
 *   - Dequeue curr.
 *   - For each neighbor of curr:
 *     - If not cloned yet, clone it, put in map, enqueue neighbor.
 *     - Add cloned neighbor to cloned curr's neighbor list.
 * 
 * Time Complexity: O(V + E) where V is vertices, E is edges.
 * Space Complexity: O(V) for visited map and BFS queue.
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

Node cloneGraph(Node node) {
        if (node == NULL) return NULL;

        Map<Node, Node> clonedMap = new HashMap<>();
        Queue<Node> queue = new ArrayDeque<>();

        // Clone the root node
        clonedMap.put(node, new Node(node.val));
        queue.offer(node);

        while (!queue.isEmpty()) {
            Node curr = queue.poll();
            Node cloneCurr = clonedMap.get(curr);

            for (Node neighbor : curr.neighbors) {
                if (!clonedMap.containsKey(neighbor)) {
                    clonedMap.put(neighbor, new Node(neighbor.val));
                    queue.offer(neighbor);
                }
                cloneCurr.neighbors.add(clonedMap.get(neighbor));
            }
        }

        return clonedMap.get(node);
    }

    int main(void) {
        // Build 4-cycle graph: 1 -- 2 -- 3 -- 4 -- 1
        Node n1 = new Node(1);
        Node n2 = new Node(2);
        Node n3 = new Node(3);
        Node n4 = new Node(4);

        n1.neighbors.add(n2);
        n1.neighbors.add(n4);

        n2.neighbors.add(n1);
        n2.neighbors.add(n3);

        n3.neighbors.add(n2);
        n3.neighbors.add(n4);

        n4.neighbors.add(n1);
        n4.neighbors.add(n3);

        Node cloned = cloneGraph(n1);
        printf("Original node 1 == Cloned node 1: " + (n1 == cloned) + " (Expected: false)\n");
        printf("Cloned node 1 val: " + cloned.val + " (Expected: 1)\n");
        printf("Cloned node 1 neighbors count: " + cloned.neighbors.size() + " (Expected: 2)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
