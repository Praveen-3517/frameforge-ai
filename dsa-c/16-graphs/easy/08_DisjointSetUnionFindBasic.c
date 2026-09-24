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

static const int* parent;
    static const int* rank;
    static int components;

    DisjointSetUnionFindBasic(int n) {
        this.parent = (int*)malloc((n) * sizeof(int));
        this.rank = (int*)malloc((n) * sizeof(int));
        this.components = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        // Path compression: flatten the tree structure
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool union(int x, int y) {
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

    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponentCount() {
        return components;
    }

    int main(void) {
        DisjointSetUnionFindBasic dsu = new DisjointSetUnionFindBasic(5);
        dsu.union(0, 1);
        dsu.union(1, 2);
        dsu.union(3, 4);

        printf("0 and 2 connected: " + dsu.isConnected(0, 2) + " (Expected: true)\n");
        printf("0 and 3 connected: " + dsu.isConnected(0, 3) + " (Expected: false)\n");
        printf("Components count: " + dsu.getComponentCount() + " (Expected: 2)\n");

        dsu.union(2, 3);
        printf("After union(2, 3) - 0 and 4 connected: " + dsu.isConnected(0, 4) + " (Expected: true)\n");
        printf("Components count: " + dsu.getComponentCount() + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */
