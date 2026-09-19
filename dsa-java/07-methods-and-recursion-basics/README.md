# Topic 07: Methods/Functions & Recursion Basics

Welcome to **Topic 07** of the **Java DSA & Interview Preparation** series.
Methods encapsulate executable logic in Java classes, while recursion provides the foundational mechanism for divide-and-conquer algorithms, tree/graph traversals, and dynamic programming. Mastering methods and recursion requires an exact understanding of **Java's Pass-by-Value semantics**, **Call Stack frames**, **StackOverflowError boundaries**, **overloading vs overriding resolution**, and **backtracking tree traversal**.

---

## 1. Java is Strictly "Pass-by-Value"

A classic technical interview question: *"Does Java pass arguments by value or by reference?"*
**Answer**: Java is **100% Pass-by-Value**. There is NO pass-by-reference in Java.

### Proof & Demonstration:
1. **Primitives**: A direct copy of the bit-level value is passed into the method stack frame. Modifying the parameter inside the method has zero effect on the caller's variable.
2. **Object References**: A copy of the **reference pointer (memory address)** is passed by value!
   - Calling mutator methods (e.g. `list.add("item")` or `person.setName("Bob")`) mutates the shared underlying heap object.
   - Reassigning the pointer (e.g. `person = new Person("Charlie")`) merely reassigns the local parameter copy inside that method frame, having **zero effect on the caller's original object**!

```java
public static void swap(Person a, Person b) {
    Person temp = a;
    a = b;
    b = temp;
    // When method exits, a and b in the caller REMAIN UNCHANGED!
}
```

---

## 2. Method Overloading Resolution Order

When multiple overloaded methods match an invocation, the Java compiler selects the **most specific method** using the following precedence hierarchy:

```
1. Exact Primitive Match        (e.g., int -> int)
2. Widening Primitive Conversion (e.g., int -> long -> float -> double)
3. Autoboxing Conversion         (e.g., int -> Integer)
4. Varargs Conversion            (e.g., int... args) [Lowest Priority]
```

---

## 3. Anatomy of Recursion & The JVM Call Stack

Every recursive method invocation pushes a new **Stack Frame** onto the executing Thread's Call Stack.
- **Components of a Stack Frame**: Local variables, method arguments, return address, operand stack.
- **The Two Indispensable Components of Any Recursive Method**:
  1. **Base Case (Termination Guard)**: Halts recursion and prevents infinite depth.
  2. **Recursive Step (Progress Towards Base Case)**: Decrements/divides problem size.

### Why `StackOverflowError` Occurs:
- The default JVM thread stack size (configured via `-Xss`) is typically 1 MB (approx. 5,000 to 10,000 stack frames).
- If recursion exceeds this depth (or lacks a base case), the JVM throws `java.lang.StackOverflowError`.
- **Note on Tail Call Optimization (TCO)**: Unlike languages like Scala or Haskell, standard HotSpot Java compilers do **not** perform automatic TCO. Any deep linear recursion must be converted into an iterative loop in production code.

---

## 4. Directory Structure

- [`easy/`](./easy/): 10 foundational problems proving pass-by-value, overloading rules, varargs, recursive digit sums, and sorted checks.
- [`medium/`](./medium/): 10 algorithmic problems on Tower of Hanoi, fast power $O(\log N)$, subsets, permutations, phone keypad combinations, and Josephus circle elimination.
- [`hard/`](./hard/): 8 advanced problems on N-Queens backtracking, Sudoku solver, K-th symbol in grammar, Palindrome partitioning, and special binary strings.
