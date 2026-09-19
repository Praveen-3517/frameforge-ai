/**
 * Problem: Disjoint Set Union (DSU / Union-Find) with Path Compression & Union by Rank
 * Asked in: Google, Amazon, Facebook, Microsoft
 * 
 * Implement an optimized Disjoint Set Union (DSU) data structure supporting:
 * - find(x): Finds representative of set containing x with path compression.
 * - union(x, y): Merges sets containing x and y using union by rank.
 * - isConnected(x, y): Returns true if x and y belong to the same connected component.
 * - getComponentCount(): Returns number of distinct connected components.
 * 
 * Time Complexity:
 * - find and union: O(alpha(N)) ~ O(1) amortized, where alpha is inverse Ackermann function.
 * Space Complexity: O(N) for parent and rank arrays.
 */
class DisjointSetUnionFindBasic {

    private final int[] parent;
    private final int[] rank;
    private int components;

    public DisjointSetUnionFindBasic(int n) {
        this.parent = new int[n];
        this.rank = new int[n];
        this.components = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    public int find(int x) {
        // Path compression: flatten the tree structure
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    public boolean union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false; // Already in the same set
        }

        // Union by rank: attach smaller depth tree under root of deeper tree
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        components--;
        return true;
    }

    public boolean isConnected(int x, int y) {
        return find(x) == find(y);
    }

    public int getComponentCount() {
        return components;
    }

    public static void main(String[] args) {
        DisjointSetUnionFindBasic dsu = new DisjointSetUnionFindBasic(5);
        dsu.union(0, 1);
        dsu.union(1, 2);
        dsu.union(3, 4);

        System.out.println("0 and 2 connected: " + dsu.isConnected(0, 2) + " (Expected: true)");
        System.out.println("0 and 3 connected: " + dsu.isConnected(0, 3) + " (Expected: false)");
        System.out.println("Components count: " + dsu.getComponentCount() + " (Expected: 2)");

        dsu.union(2, 3);
        System.out.println("After union(2, 3) - 0 and 4 connected: " + dsu.isConnected(0, 4) + " (Expected: true)");
        System.out.println("Components count: " + dsu.getComponentCount() + " (Expected: 1)");
    }
}
