# Topic 05: Arrays (1D and 2D)

Welcome to **Topic 05** of the **Java DSA & Interview Preparation** series.
Arrays are contiguous memory data structures that store a fixed number of elements of a single type. In Java, **arrays are first-class objects** stored in the Heap. Mastering arrays in Java requires understanding **JVM memory layouts**, **jagged arrays**, **memory copying via JNI `System.arraycopy`**, and high-frequency algorithmic patterns (**Kadane's**, **Boyer-Moore Voting**, **Dutch National Flag**, and **Prefix Sums**).

---

## 1. Java Array Memory Layout

### A. 1D Array Layout in JVM Heap
```
int[] arr = new int[4];
```
- In Java, an array is an **object**. It has an object header (Mark Word + Klass Word, typically 12-16 bytes) plus a 4-byte `length` field.
- The actual primitive elements (`int`) are packed contiguously in heap memory immediately following the header.
- Elements are initialized to their type defaults: `0` for numbers, `false` for booleans, `null` for objects.

### B. 2D Arrays are "Arrays of Arrays" (Not Flat Contiguous Blocks!)
Unlike C/C++ where `int matrix[3][4]` is a single contiguous row-major memory slab, in Java:
```java
int[][] matrix = new int[3][4];
```
- `matrix` is a 1D reference array of length 3 on the heap.
- Each slot points to an independently allocated 1D array of 4 integers!
- This architecture enables **Jagged Arrays** (arrays where rows have differing lengths):
```java
int[][] jagged = new int[3][];
jagged[0] = new int[2];
jagged[1] = new int[5];
jagged[2] = new int[3];
```

---

## 2. Array Copying Mechanisms & Performance

| Method | Mechanism | Deep vs Shallow | Performance |
| :--- | :--- | :--- | :--- |
| `System.arraycopy()` | JNI C++ `memmove`/`memcpy` | Shallow | Fastest (Native CPU SIMD) |
| `Arrays.copyOf()` | Calls `System.arraycopy` internally | Shallow | Fast & convenient |
| `arr.clone()` | Java Object clone method | Shallow | Fast for 1D primitives |
| Manual `for` loop | Java bytecode iterations | Custom | Slowest |

> [!IMPORTANT]
> All built-in Java copy utilities perform a **shallow copy**. If copying an array of objects (e.g. `StringBuilder[]` or `int[][]`), only the memory references are copied, not the underlying objects!

---

## 3. Essential Array Interview Patterns

1. **Two Pointers**: Reverse in-place, Two Sum on sorted array, Remove Duplicates.
2. **Sliding Window**: Subarrays of fixed size $K$ or dynamic size with monotonic properties.
3. **Prefix Sum + HashMap**: Finding number of subarrays summing to $K$ in $O(N)$ time.
4. **Kadane's Algorithm**: Finding the maximum subarray sum in $O(N)$ time with $O(1)$ space.
5. **Boyer-Moore Voting**: Identifying the majority element ($> N/2$) in $O(N)$ time and $O(1)$ space.
6. **Dutch National Flag (3-Way Partitioning)**: Sorting an array of 0s, 1s, and 2s in a single pass.
7. **Cyclic Sort**: Placing numbers $1 \le x \le N$ at index $x - 1$ in $O(N)$ time and $O(1)$ space.

---

## 4. Directory Structure

- [`easy/`](./easy/): 10 problems on linear/binary search, min/max tournament, in-place reversal, running sum, and jagged arrays.
- [`medium/`](./medium/): 10 problems on Kadane's algorithm, Dutch National Flag, Boyer-Moore, Prefix Sum with K, and 90° rotation.
- [`hard/`](./hard/): 8 advanced FAANG problems on Median of Two Sorted Arrays, Rain Water, Histogram Area, and Subarrays with K Distinct Integers.
