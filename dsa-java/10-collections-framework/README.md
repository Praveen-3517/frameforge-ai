# Topic 10: Java Collections Framework (JCF)

The Java Collections Framework provides a unified architecture for storing, manipulating, and accessing collections of data efficiently.

---

## The Collections Hierarchy

```
                            Iterable<T>
                                 |
                           Collection<T>
                   /             |              \
               List<T>        Set<T>          Queue<T>
              /       \          |    \           |     \
       ArrayList   LinkedList HashSet TreeSet  ArrayDeque PriorityQueue
                                 |
                           LinkedHashSet
```

*(Note: `Map<K, V>` does not extend `Collection<T>`, but is an integral part of the Framework).*

```
                              Map<K, V>
                       /          |         \
                   HashMap   LinkedHashMap  TreeMap
                      |
              ConcurrentHashMap
```

---

## Core Data Structures & Complexities

| Collection | Underlying Data Structure | Access | Search | Insert | Delete | Ordered? | Sorted? | Nulls? |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **`ArrayList`** | Resizable Array | O(1) | O(N) | O(1)* | O(N) | Yes (Index) | No | Yes |
| **`LinkedList`** | Doubly-Linked List | O(N) | O(N) | O(1) | O(1) | Yes (Index) | No | Yes |
| **`HashSet`** | Hash Table (`HashMap`) | N/A | O(1) | O(1) | O(1) | No | No | 1 Null |
| **`LinkedHashSet`** | Hash Table + Doubly-Linked List | N/A | O(1) | O(1) | O(1) | Yes (Insertion)| No | 1 Null |
| **`TreeSet`** | Red-Black Tree (`TreeMap`) | N/A | O(log N) | O(log N) | O(log N) | Yes (Sorted) | Yes | No |
| **`HashMap`** | Hash Table (Buckets + Tree) | N/A | O(1) | O(1) | O(1) | No | No | 1 K, * V |
| **`LinkedHashMap`** | Hash Table + Doubly-Linked List | N/A | O(1) | O(1) | O(1) | Yes (Insert/Access)| No | 1 K, * V |
| **`TreeMap`** | Red-Black Tree | N/A | O(log N) | O(log N) | O(log N) | Yes (Sorted) | Yes | No K, * V |
| **`PriorityQueue`**| Binary Min-Heap | O(1) peek | O(N) | O(log N) | O(log N) | No | Heap Order | No |
| **`ArrayDeque`** | Circular Resizable Array | O(1) ends | O(N) | O(1) | O(1) | Yes (FIFO/LIFO)| No | No |

*\* Amortized time complexity.*

---

## `Comparable` vs `Comparator`

- **`Comparable<T>`**:
  - Implemented by the class itself: `public int compareTo(T other)`.
  - Defines the "Natural Ordering" (e.g. `String`, `Integer`).
- **`Comparator<T>`**:
  - Separate class or lambda: `(a, b) -> Integer.compare(a.val, b.val)`.
  - Allows multiple sorting strategies for the same object.

---

## `fail-fast` vs `fail-safe` Iterators
- **Fail-Fast**: Throws `ConcurrentModificationException` immediately if collection is structurally modified during iteration (e.g. `ArrayList`, `HashMap`).
- **Fail-Safe / Weakly Consistent**: Operates on a clone or snapshot; never throws `ConcurrentModificationException` (e.g. `CopyOnWriteArrayList`, `ConcurrentHashMap`).

---

## Folder Structure
- `easy/`: 10 foundational collections implementations & operations.
- `medium/`: 10 core algorithmic problems solved using collections (Two Sum, Group Anagrams, Top K Frequent, PriorityQueue).
- `hard/`: 8 advanced data structures & high-frequency interview problems (Median Finder, LFU Cache, All O(1) Structure, Sliding Window Maximum).
