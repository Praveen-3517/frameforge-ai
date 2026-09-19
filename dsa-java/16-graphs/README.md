# Topic 16: Graphs (BFS, DFS, Dijkstra, Bellman-Ford, MST, Topological Sort, SCC)

## 1. Overview & Fundamentals

A **Graph** $G = (V, E)$ consists of a finite set of vertices (nodes) $V$ and a collection of edges (arcs) $E$ connecting pairs of vertices.

### Graph Types:
- **Directed Graph (Digraph)**: Edges have orientation ($u \to v$).
- **Undirected Graph**: Edges are bidirectional ($u \leftrightarrow v$).
- **Weighted Graph**: Edges have associated numerical costs/weights.
- **DAG (Directed Acyclic Graph)**: Directed graph with no directed cycles; forms the foundation of Topological Sort and Dynamic Programming.

---

## 2. Graph Representations

| Representation | Space Complexity | Add Edge | Check if Edge $(u, v)$ Exists | Iterate Neighbors of $u$ |
| :--- | :--- | :--- | :--- | :--- |
| **Adjacency Matrix** | $O(V^2)$ | $O(1)$ | $O(1)$ | $O(V)$ |
| **Adjacency List** | $O(V + E)$ | $O(1)$ | $O(\text{deg}(u))$ | $O(\text{deg}(u))$ |
| **Edge List** | $O(E)$ | $O(1)$ | $O(E)$ | $O(E)$ |

*(Adjacency List is preferred for sparse graphs where $E \ll V^2$)*

---

## 3. Fundamental Graph Algorithms

### 1. Breadth-First Search (BFS)
- Traverses layer-by-layer using a FIFO queue.
- Finds **shortest path in unweighted graphs** in $O(V + E)$.

### 2. Depth-First Search (DFS)
- Explores deep along each branch before backtracking using recursion or stack.
- Used for connected components, topological sorting, bridge detection, and cycle finding.

### 3. Topological Sort (DAGs only)
- **Kahn's Algorithm (BFS)**: Calculates in-degrees; enqueues 0 in-degree nodes. If processed count $< V$, graph contains a cycle!
- **DFS Post-Order Reverse**: Push finished nodes onto a stack.

### 4. Shortest Path Algorithms
- **Dijkstra's Algorithm**: Greedy with Min-Heap for non-negative edge weights. Time: $O((V + E) \log V)$.
- **Bellman-Ford Algorithm**: Dynamic programming relaxing all $E$ edges $V - 1$ times. Handles negative edge weights and detects negative cycles in $O(V \cdot E)$.
- **Floyd-Warshall Algorithm**: All-pairs shortest path dynamic programming in $O(V^3)$.

### 5. Minimum Spanning Tree (MST)
- **Kruskal's Algorithm**: Sorts edges by weight and greedily unifies components using Disjoint Set Union (DSU) in $O(E \log E)$.
- **Prim's Algorithm**: Starts from a source vertex and grows the MST using a Min-Heap in $O((V + E) \log V)$.

### 6. Advanced Graph Theory
- **Tarjan's Algorithm for Bridges**: Uses discovery times `tin[u]` and lowest reachable ancestor `low[u]`. An edge $(u, v)$ is a bridge if `low[v] > tin[u]`.
- **Kosaraju's Algorithm for SCCs**: 2-pass DFS (first pass builds finish order, second pass traverses reversed graph).

---

## 4. Directory Structure

```
16-graphs/
├── README.md
├── easy/
│   ├── 01_GraphAdjacencyListRepresentation.java
│   ├── 02_FindIfPathExistsInGraph.java
│   ├── 03_FloodFillAlgorithm.java
│   ├── 04_NumberOfIslandsBFS.java
│   ├── 05_MaxAreaOfIslandDFS.java
│   ├── 06_FindCenterOfStarGraph.java
│   ├── 07_FindJudgeInTown.java
│   ├── 08_DisjointSetUnionFindBasic.java
│   ├── 09_CloneGraphBFS.java
│   └── 10_IslandPerimeter.java
├── medium/
│   ├── 01_CourseScheduleCycleDetectionKahn.java
│   ├── 02_CourseScheduleTwoTopologicalOrder.java
│   ├── 03_NumberOfProvincesUnionFind.java
│   ├── 04_RottingOrangesMultiSourceBFS.java
│   ├── 05_DijkstraShortestPathAlgorithm.java
│   ├── 06_SurroundedRegionsDFS.java
│   ├── 07_PacificAtlanticWaterFlow.java
│   ├── 08_WordLadderShortestTransformation.java
│   ├── 09_CheapestFlightsWithinKStops.java
│   └── 10_RedundantConnectionUnionFind.java
└── hard/
    ├── 01_CriticalConnectionsBridgesTarjan.java
    ├── 02_AlienDictionaryTopologicalSort.java
    ├── 03_WordLadderTwoAllShortestPaths.java
    ├── 04_KruskalMinimumSpanningTree.java
    ├── 05_PrimMinimumSpanningTree.java
    ├── 06_BellmanFordNegativeCycleDetection.java
    ├── 07_FloydWarshallAllPairsShortestPath.java
    └── 08_StronglyConnectedComponentsKosaraju.java
```
