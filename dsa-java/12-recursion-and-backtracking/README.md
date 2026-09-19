# Topic 12: Advanced Recursion and Backtracking

Backtracking is a systematic algorithmic technique for solving constraint satisfaction problems by incrementally building candidates toward a solution and abandoning ("backtracking" from) a candidate as soon as it is determined that the candidate cannot lead to a valid solution.

---

## The Backtracking Blueprint

Every backtracking algorithm follows this universal recursive template:

```java
void backtrack(State state, List<Result> results) {
    if (isGoal(state)) {
        results.add(new Result(state)); // Take snapshot of valid configuration
        return;
    }

    for (Choice choice : getChoices(state)) {
        if (isValid(choice, state)) {    // Pruning / Bounding Function
            state.apply(choice);         // 1. Make choice
            backtrack(state, results);   // 2. Explore choice recursively
            state.undo(choice);          // 3. Backtrack (restore state)
        }
    }
}
```

---

## Core Problem Categories

### 1. Generation & Enumeration
- **Subsets**: $2^N$ configurations (include or exclude each element).
- **Permutations**: $N!$ configurations (order matters; track visited choices).
- **Combinations**: $\binom{N}{K}$ configurations (order does not matter; advance index to avoid duplicate combinations).

### 2. Constraint Satisfaction Problems (CSP)
- **N-Queens**: Place $N$ non-attacking queens on an $N \times N$ board.
- **Sudoku Solver**: Fill 9x9 board adhering to row, column, and sub-grid uniqueness.
- **Graph M-Coloring**: Color vertices of a graph such that no two adjacent vertices share the same color.
- **Knight's Tour**: Visit every square of an $N \times N$ chessboard exactly once.

### 3. Grid Search & Pathfinding
- **Rat in a Maze**: Find all paths from start to destination in a blocked grid.
- **Word Search**: Find contiguous characters forming words in a matrix.

---

## Pruning & Optimization Techniques
1. **Symmetry Breaking**: In problems like N-Queens or Knight's Tour, avoid exploring mirrored subtrees.
2. **Early Pruning**: Sort input arrays so branches that exceed limits can be broken (`break`) instead of evaluated.
3. **Bitmasks for Fast State Tracking**: Use bitwise operations to achieve $O(1)$ conflict checks.

---

## Folder Structure
- `easy/`: 10 foundational recursive & backtracking problems.
- `medium/`: 10 classic backtracking challenges (Subsets II, Combination Sum II/III, Rat in a Maze, Partition to K Equal Sum Subsets).
- `hard/`: 8 complex backtracking and NP-hard problems (Sudoku Solver, N-Queens II, Word Search II with Trie, Palindrome Partitioning, Knight's Tour, Hamiltonian Path).
