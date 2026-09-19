# Topic 04: Loops (for, while, do-while, nested loops, break/continue)

Welcome to **Topic 04** of the **Java DSA & Interview Preparation** series.
Loops are the fundamental mechanism for repetition, sequence processing, and iterative algorithms. Beyond standard syntax, technical interviews at leading tech companies evaluate an engineer's mastery of **labeled break/continue**, **loop invariants**, **cyclic sort loops**, **monotonic stack/queue loops**, and **preventing floating-point termination bugs**.

---

## 1. Loop Constructs Overview

### A. The Standard `for` Loop
```java
for (initialization; terminationCondition; updateStatement) {
    // Loop body
}
```
- Multiple loop counters can be initialized and updated simultaneously:
  `for (int i = 0, j = n - 1; i < j; i++, j--) { ... }`
- Omitting condition creates an intentional infinite loop: `for (;;) { ... }`.

### B. The `while` Loop
- Pre-condition loop: checks condition **before** entering the loop body.
- Best used when the number of iterations is not known in advance (e.g., Euclidean GCD, digit extraction `while (n != 0)`).

### C. The `do-while` Loop
- Post-condition loop: executes the body **at least once** before evaluating condition:
```java
do {
    process();
} while (hasMoreWork());
```

### D. Enhanced `for-each` Loop
- Syntactic sugar introduced in Java 5 for traversing arrays and classes implementing `Iterable<T>`.
- Uses an internal `Iterator<T>` under the hood. Cannot be used to modify the collection structure (throws `ConcurrentModificationException`).

---

## 2. Labeled `break` and `continue`

Java does **not** feature a `goto` statement. Instead, Java provides **labeled breaks and continues** to escape or advance deeply nested loops:

```java
outerLoop:
for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
        if (matrix[r][c] == target) {
            found = true;
            break outerLoop; // Exits BOTH inner and outer loops immediately!
        }
    }
}
```

---

## 3. Critical Interview Gotchas & Performance

### A. Floating-Point Loop Counter Trap
```java
// DANGEROUS INFINITE LOOP!
// Due to IEEE 754 precision, 0.1f cannot be represented exactly.
// f will never be exactly equal to 1.0f!
for (float f = 0.0f; f != 1.0f; f += 0.1f) {
    // Hangs forever!
}
```

### B. Invariant Hoisting in Loop Termination
In performance-critical code:
```java
// BAD: recomputes size() or length() on every iteration
for (int i = 0; i < list.size(); i++) { ... }

// GOOD: Hoist invariant expression
for (int i = 0, len = list.size(); i < len; i++) { ... }
```

### C. Cyclic Sort Loop Pattern
For arrays containing numbers in range `1` to `N` or `0` to `N`:
A simple `while (i < n)` loop that swaps `nums[i]` to its target index `nums[nums[i] - 1]` can sort the array in **O(N)** time and **O(1)** space without extra arrays!

---

## 4. Directory Roadmap

- [`easy/`](./easy/): 10 foundational problems on geometric pattern generation, digit reversal, GCD, Armstrong numbers, and labeled loops.
- [`medium/`](./medium/): 10 core algorithmic problems on 2D Spiral Matrix traversal, in-place 90° matrix rotation, Pascal's triangle, and Floyd's cycle detection.
- [`hard/`](./hard/): 8 advanced FAANG interview problems on Trapping Rain Water, N-Queens backtracking, Largest Rectangle in Histogram, Sliding Window Maximum, and Cyclic Sort.
