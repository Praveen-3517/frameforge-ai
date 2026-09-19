# Topic 06: Strings

Welcome to **Topic 06** of the **Java DSA & Interview Preparation** series.
In Java, strings are immutable sequence objects backed by byte arrays (`byte[]` in Java 9+ Compact Strings). Mastering strings for technical interviews requires understanding **String Constant Pool (SCP) semantics**, **`String` vs `StringBuilder` vs `StringBuffer`**, **rolling hash algorithms (Rabin-Karp)**, **linear pattern matching (KMP)**, and **O(N) palindrome algorithms (Manacher's Algorithm)**.

---

## 1. Java String Memory & Immutability

### A. String Constant Pool (SCP) in Heap
When a string literal is created:
```java
String s1 = "hello";              // Placed in String Constant Pool in JVM Heap
String s2 = "hello";              // Reuses reference from SCP: (s1 == s2) is TRUE!
String s3 = new String("hello");  // Forces a new Heap object outside SCP: (s1 == s3) is FALSE!
String s4 = s3.intern();          // Returns reference from SCP: (s1 == s4) is TRUE!
```

### B. Why Strings Are Immutable in Java:
1. **Security**: Strings carry sensitive database URLs, network sockets, usernames, and passwords. Immutability prevents tampering.
2. **Thread Safety**: Immutable strings can be shared across multiple threads without synchronization.
3. **Caching & Hashing**: The `hashCode()` of a String is computed lazily and cached permanently (`private int hash`). It will never change, making strings ideal keys for `HashMap` and `HashSet`.
4. **String Constant Pool**: Memory optimization sharing identical string instances across the JVM.

---

## 2. `String` vs `StringBuilder` vs `StringBuffer`

| Feature | `String` | `StringBuilder` | `StringBuffer` |
| :--- | :--- | :--- | :--- |
| **Mutability** | Immutable | Mutable | Mutable |
| **Thread Safety** | Thread-safe | Not thread-safe | Thread-safe (synchronized methods) |
| **Performance** | Slow (allocates on `+`) | Fastest | Slower due to lock overhead |
| **Use-Case** | Constants, Map keys | Local string building/loops | Multi-threaded legacy code |

> [!CAUTION]
> Never concatenate strings inside a loop using the `+` operator:
> ```java
> // DISASTROUS: O(N^2) allocations! Creates a new StringBuilder and String on every iteration
> String res = "";
> for (int i = 0; i < n; i++) res += arr[i];
>
> // OPTIMAL: O(N) amortized
> StringBuilder sb = new StringBuilder(n * 4);
> for (int i = 0; i < n; i++) sb.append(arr[i]);
> ```

---

## 3. High-Frequency String Interview Patterns

1. **Sliding Window**: Minimum Window Substring, Longest Substring Without Repeating Characters.
2. **Frequency Bucketing**: Anagram detection using `int[26]` frequency arrays.
3. **Expand Around Center**: O(N^2) Longest Palindromic Substring with O(1) space.
4. **Knuth-Morris-Pratt (KMP)**: O(N + M) pattern search using the Longest Proper Prefix which is also Suffix (LPS) array.
5. **Rabin-Karp Rolling Hash**: O(N + M) average search using polynomial rolling hashes with modular arithmetic.
6. **Manacher's Algorithm**: O(N) optimal linear time palindrome radius expansion.

---

## 4. Directory Structure

- [`easy/`](./easy/): 10 problems on string pool immutability, reversals, anagrams, common prefix, and Roman conversions.
- [`medium/`](./medium/): 10 problems on sliding window unique substrings, group anagrams, expand-center palindromes, Atoi, and decode string.
- [`hard/`](./hard/): 8 advanced problems on KMP, Rabin-Karp, Minimum Window Substring, Regex Matching, Wildcard DP, and Manacher's algorithm.
