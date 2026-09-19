# Topic 14: Stack and Queue Data Structures

Stacks and Queues are fundamental linear data structures governed by disciplined access constraints.

---

## 1. Stack (LIFO: Last-In, First-Out)
- **Concept**: Elements can only be inserted (`push`) and removed (`pop`) from the top of the stack.
- **Implementations**:
  - `ArrayDeque`: Recommended modern Java standard for stacks (faster than legacy `java.util.Stack`).
  - Custom Array or Singly Linked List.
- **Common Applications**: Function call stacks, expression evaluation, parenthesis validation, backtracking history (Undo/Redo), browser back/forward history.

---

## 2. Queue (FIFO: First-In, First-Out)
- **Concept**: Elements are inserted at the back (`offer`/`enqueue`) and removed from the front (`poll`/`dequeue`).
- **Implementations**:
  - `ArrayDeque`: High-performance circular array queue.
  - `LinkedList`: Node-based queue.
- **Common Applications**: Breadth-First Search (BFS), task scheduling, print spoolers, web server request buffers.

---

## 3. The Monotonic Stack Pattern
A **Monotonic Stack** maintains elements in strictly increasing or decreasing order.
When a new element arrives that violates the monotonic invariant, elements are popped from the stack until the invariant is restored.

- **Monotonic Decreasing Stack**: Useful for finding the **Next Greater Element** to the right or left.
- **Monotonic Increasing Stack**: Useful for finding the **Next Smaller Element** (e.g. Largest Rectangle in Histogram, Trapping Rain Water).

---

## Folder Structure
- `easy/`: 10 foundational Stack & Queue problems (Custom Array Stack/Queue, Min Stack, Queue using Stacks, Stack using Queues).
- `medium/`: 10 core algorithmic problems (Next Greater Element, Daily Temperatures, Evaluate Reverse Polish Notation, Design Circular Queue, Asteroid Collision).
- `hard/`: 8 advanced monotonic stack/queue challenges (Largest Rectangle in Histogram, Maximal Rectangle, Trapping Rain Water, Sliding Window Maximum, Basic Calculator).
