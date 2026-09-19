# Topic 13: Linked List Data Structures

A Linked List is a linear data structure where elements are not stored at contiguous memory locations. Instead, each element (called a Node) contains data and one or more pointers/references to adjacent nodes.

---

## Types of Linked Lists

1. **Singly Linked List**: Each node points to the next node (`next`). The last node points to `null`.
2. **Doubly Linked List**: Each node has two pointers: one to the next node (`next`) and one to the previous node (`prev`). Allows bidirectional traversal.
3. **Circular Linked List**: The last node's `next` pointer points back to the head node instead of `null`.

---

## Core Operations & Complexities

| Operation | Array / ArrayList | Singly Linked List | Doubly Linked List |
| :--- | :--- | :--- | :--- |
| **Insert at Head** | O(N) | **O(1)** | **O(1)** |
| **Insert at Tail** | O(1) amortized | O(1) with tail ptr | **O(1)** with tail ptr |
| **Insert at Middle** | O(N) | O(N) traversal + O(1) link | O(N) traversal + O(1) link |
| **Delete at Head** | O(N) | **O(1)** | **O(1)** |
| **Delete at Tail** | O(1) | O(N) (needs predecessor) | **O(1)** with tail ptr |
| **Access by Index** | **O(1)** | O(N) | O(N) |
| **Search Element** | O(N) or O(log N) | O(N) | O(N) |

---

## Essential Patterns & Techniques

### 1. Sentinel / Dummy Head Node
Avoid edge-case checks for empty lists or modifying the head node:
```java
ListNode dummy = new ListNode(0);
dummy.next = head;
// perform operations using dummy...
return dummy.next;
```

### 2. Fast & Slow Pointer (Floyd's Tortoise and Hare)
- **Finding Midpoint**: Advance slow by 1, fast by 2. When fast reaches end, slow is at the middle.
- **Cycle Detection**: If slow and fast meet, a cycle exists.
- **Cycle Start**: Reset slow to head; advance both by 1 step until they collide at the loop entry.

### 3. In-Place Reversal Pattern
```java
ListNode prev = null, curr = head;
while (curr != null) {
    ListNode next = curr.next;
    curr.next = prev;
    prev = curr;
    curr = next;
}
return prev; // new head
```

---

## Folder Structure
- `easy/`: 10 foundational linked list problems (Design Singly/Doubly List, Reverse, Merge Two Sorted, Middle Node, Delete Node).
- `medium/`: 10 classic interview problems (Add Two Numbers, Reorder List, Odd Even List, Copy List with Random Pointer, Remove N-th Node from End).
- `hard/`: 8 complex linked list algorithms (Reverse Nodes in k-Group, Merge K Sorted Lists, LRU Cache Linked List, Flatten Multilevel Doubly List).
