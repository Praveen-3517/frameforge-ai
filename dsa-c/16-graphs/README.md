# Graph Algorithms & Network Traversal in C

> Adjacency matrices and adjacency lists, BFS, DFS, Dijkstra's shortest path, Bellman-Ford, Disjoint Set Union (Union-Find), and Kruskal's MST.

---

## 📌 Architectural Overview & C Systems Principles

In C, data structures and algorithms execute directly against physical memory without JVM bytecode, garbage collection overhead, or object headers. Understanding:
1. **Memory Layout**: Stack (automatic allocation, rapid cache hits) vs Heap (`malloc`/`free`, dynamic sizing).
2. **Pointer Semantics**: Explicit address-of (`&`), dereference (`*`), and pointer arithmetic (`*(ptr + i)`).
3. **Data Alignment & Padding**: Hardware alignment requirements and struct padding for CPU bus efficiency.
4. **Cache Locality**: Contiguous arrays maximizing L1/L2 data cache line utilization.

---

## 🗂️ Problem Directory & Difficulty Breakdown

### 🟢 Easy Tier (Foundational & Core Syntax)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **GraphAdjacencyListRepresentation** | [`easy/01_GraphAdjacencyListRepresentation.c`](./easy/01_GraphAdjacencyListRepresentation.c) | Foundational logic, boundary checks |
| 2 | **FindIfPathExistsInGraph** | [`easy/02_FindIfPathExistsInGraph.c`](./easy/02_FindIfPathExistsInGraph.c) | Foundational logic, boundary checks |
| 3 | **FloodFillAlgorithm** | [`easy/03_FloodFillAlgorithm.c`](./easy/03_FloodFillAlgorithm.c) | Foundational logic, boundary checks |
| 4 | **NumberOfIslandsBFS** | [`easy/04_NumberOfIslandsBFS.c`](./easy/04_NumberOfIslandsBFS.c) | Foundational logic, boundary checks |
| 5 | **MaxAreaOfIslandDFS** | [`easy/05_MaxAreaOfIslandDFS.c`](./easy/05_MaxAreaOfIslandDFS.c) | Foundational logic, boundary checks |
| 6 | **FindCenterOfStarGraph** | [`easy/06_FindCenterOfStarGraph.c`](./easy/06_FindCenterOfStarGraph.c) | Foundational logic, boundary checks |
| 7 | **FindJudgeInTown** | [`easy/07_FindJudgeInTown.c`](./easy/07_FindJudgeInTown.c) | Foundational logic, boundary checks |
| 8 | **DisjointSetUnionFindBasic** | [`easy/08_DisjointSetUnionFindBasic.c`](./easy/08_DisjointSetUnionFindBasic.c) | Foundational logic, boundary checks |
| 9 | **CloneGraphBFS** | [`easy/09_CloneGraphBFS.c`](./easy/09_CloneGraphBFS.c) | Foundational logic, boundary checks |
| 10 | **IslandPerimeter** | [`easy/10_IslandPerimeter.c`](./easy/10_IslandPerimeter.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **CourseScheduleCycleDetectionKahn** | [`medium/01_CourseScheduleCycleDetectionKahn.c`](./medium/01_CourseScheduleCycleDetectionKahn.c) | Optimal time/space, pointers, recursion |
| 2 | **CourseScheduleTwoTopologicalOrder** | [`medium/02_CourseScheduleTwoTopologicalOrder.c`](./medium/02_CourseScheduleTwoTopologicalOrder.c) | Optimal time/space, pointers, recursion |
| 3 | **NumberOfProvincesUnionFind** | [`medium/03_NumberOfProvincesUnionFind.c`](./medium/03_NumberOfProvincesUnionFind.c) | Optimal time/space, pointers, recursion |
| 4 | **RottingOrangesMultiSourceBFS** | [`medium/04_RottingOrangesMultiSourceBFS.c`](./medium/04_RottingOrangesMultiSourceBFS.c) | Optimal time/space, pointers, recursion |
| 5 | **DijkstraShortestPathAlgorithm** | [`medium/05_DijkstraShortestPathAlgorithm.c`](./medium/05_DijkstraShortestPathAlgorithm.c) | Optimal time/space, pointers, recursion |
| 6 | **SurroundedRegionsDFS** | [`medium/06_SurroundedRegionsDFS.c`](./medium/06_SurroundedRegionsDFS.c) | Optimal time/space, pointers, recursion |
| 7 | **PacificAtlanticWaterFlow** | [`medium/07_PacificAtlanticWaterFlow.c`](./medium/07_PacificAtlanticWaterFlow.c) | Optimal time/space, pointers, recursion |
| 8 | **WordLadderShortestTransformation** | [`medium/08_WordLadderShortestTransformation.c`](./medium/08_WordLadderShortestTransformation.c) | Optimal time/space, pointers, recursion |
| 9 | **CheapestFlightsWithinKStops** | [`medium/09_CheapestFlightsWithinKStops.c`](./medium/09_CheapestFlightsWithinKStops.c) | Optimal time/space, pointers, recursion |
| 10 | **RedundantConnectionUnionFind** | [`medium/10_RedundantConnectionUnionFind.c`](./medium/10_RedundantConnectionUnionFind.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **CriticalConnectionsBridgesTarjan** | [`hard/01_CriticalConnectionsBridgesTarjan.c`](./hard/01_CriticalConnectionsBridgesTarjan.c) | Complex invariants, state trees, low-level bits |
| 2 | **AlienDictionaryTopologicalSort** | [`hard/02_AlienDictionaryTopologicalSort.c`](./hard/02_AlienDictionaryTopologicalSort.c) | Complex invariants, state trees, low-level bits |
| 3 | **WordLadderTwoAllShortestPaths** | [`hard/03_WordLadderTwoAllShortestPaths.c`](./hard/03_WordLadderTwoAllShortestPaths.c) | Complex invariants, state trees, low-level bits |
| 4 | **KruskalMinimumSpanningTree** | [`hard/04_KruskalMinimumSpanningTree.c`](./hard/04_KruskalMinimumSpanningTree.c) | Complex invariants, state trees, low-level bits |
| 5 | **PrimMinimumSpanningTree** | [`hard/05_PrimMinimumSpanningTree.c`](./hard/05_PrimMinimumSpanningTree.c) | Complex invariants, state trees, low-level bits |
| 6 | **BellmanFordNegativeCycleDetection** | [`hard/06_BellmanFordNegativeCycleDetection.c`](./hard/06_BellmanFordNegativeCycleDetection.c) | Complex invariants, state trees, low-level bits |
| 7 | **FloydWarshallAllPairsShortestPath** | [`hard/07_FloydWarshallAllPairsShortestPath.c`](./hard/07_FloydWarshallAllPairsShortestPath.c) | Complex invariants, state trees, low-level bits |
| 8 | **StronglyConnectedComponentsKosaraju** | [`hard/08_StronglyConnectedComponentsKosaraju.c`](./hard/08_StronglyConnectedComponentsKosaraju.c) | Complex invariants, state trees, low-level bits |

---

## 🛠️ Compilation & Memory Verification

```bash
# Standard compilation with C11 and strict warnings
gcc -std=c11 -Wall -Wextra -O2 easy/01_ProblemName.c -o solution
./solution

# Memory leak verification with AddressSanitizer
gcc -std=c11 -Wall -Wextra -g -fsanitize=address easy/01_ProblemName.c -o solution
./solution
```
