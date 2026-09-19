/**
 * Problem: Number of Provinces (LeetCode 547)
 * Asked in: Amazon, Microsoft, Google, Bloomberg
 * 
 * There are n cities. A province is a group of directly or indirectly connected cities.
 * Given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city
 * and the jth city are directly connected, return the total number of provinces.
 * 
 * Approach:
 * Disjoint Set Union (DSU):
 * - Initialize n disjoint sets (components = n).
 * - For each pair (i, j) where isConnected[i][j] == 1:
 *   - Call union(i, j). If successfully merged, decrement components.
 * - Return remaining components count.
 * 
 * Time Complexity: O(N^2 * alpha(N))
 * Space Complexity: O(N) for DSU structures.
 */
class NumberOfProvincesUnionFind {

    static class DSU {
        int[] parent;
        int[] rank;
        int count;

        DSU(int n) {
            parent = new int[n];
            rank = new int[n];
            count = n;
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
                count--;
            }
        }
    }

    public static int findCircleNum(int[][] isConnected) {
        int n = isConnected.length;
        DSU dsu = new DSU(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    dsu.union(i, j);
                }
            }
        }

        return dsu.count;
    }

    public static void main(String[] args) {
        int[][] isConnected1 = {
            {1, 1, 0},
            {1, 1, 0},
            {0, 0, 1}
        };
        System.out.println("Provinces: " + findCircleNum(isConnected1) + " (Expected: 2)");

        int[][] isConnected2 = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };
        System.out.println("Provinces: " + findCircleNum(isConnected2) + " (Expected: 3)");
    }
}
