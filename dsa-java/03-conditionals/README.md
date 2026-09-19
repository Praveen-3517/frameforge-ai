# Topic 03: Conditionals (if, if-else, nested if, switch-case)

Welcome to **Topic 03** of the **Java DSA & Interview Preparation** series.
Conditional control structures direct the execution flow of a program based on boolean conditions. Beyond elementary `if` checks, senior engineers and interviewers focus on **switch bytecode execution (`tableswitch` vs `lookupswitch`)**, **modern Java 14+ switch expressions (`->` and `yield`)**, **branch prediction penalties**, and **state-machine design (DFAs)**.

---

## 1. Conditional Constructs Overview

### A. The `if`, `else-if`, and `else` Ladder
- Evaluates conditions from top to bottom.
- Stops at the first condition that evaluates to `true`.
- Always order conditions from **most specific** to **most general** to avoid dead code:
```java
// WRONG: 'score >= 70' catches 90 as well, preventing 'Grade A'
if (score >= 70) grade = 'C';
else if (score >= 90) grade = 'A'; // Dead code!

// CORRECT: Descending specificity
if (score >= 90) grade = 'A';
else if (score >= 70) grade = 'C';
```

---

## 2. Java `switch-case` Deep Dive

### Permissible Types in `switch`:
In Java, a `switch` selector expression can only evaluate to:
- `byte`, `short`, `char`, `int` (and their Wrapper classes: `Byte`, `Short`, `Character`, `Integer`)
- `String` (since Java 7)
- `enum` (since Java 5)

> [!CAUTION]
> Types **NOT allowed** in Java switch statements:
> - `long` (cannot be safely cast to 32-bit jump offsets)
> - `float` and `double` (IEEE 754 precision issues make exact equality unreliable)
> - `boolean` (use `if-else` instead)

---

## 3. JVM Bytecode Internals: `tableswitch` vs `lookupswitch`

The Java compiler converts `switch` statements into one of two distinct bytecode instructions:

1. **`tableswitch` (O(1) Direct Array Index Jump)**:
   - Used when case values are **dense / contiguous** (e.g., cases 1, 2, 3, 4, 5).
   - The JVM builds a direct pointer jump table indexed by `case_val - min_val`.
   - Execution is strictly **O(1)** constant time.

2. **`lookupswitch` (O(log N) Binary Search Jump)**:
   - Used when case values are **sparse / scattered** (e.g., cases 10, 1000, 50000).
   - The JVM creates an ordered table of key-target pairs and executes a **binary search**.
   - Execution is **O(log N)** time.

---

## 4. Modern Java 14+ Switch Expressions (`->` and `yield`)

Modern Java introduces enhanced switch syntax that eliminates accidental fall-through and permits switches as expressions that return values:

```java
// Java 14+ Switch Expression with Arrow Syntax (No fall-through, no 'break' needed)
String dayType = switch (day) {
    case MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY -> "Weekday";
    case SATURDAY, SUNDAY -> "Weekend";
    default -> {
        System.out.println("Invalid day entered");
        yield "Unknown"; // 'yield' returns a value from a multi-line block
    }
};
```

---

## 5. CPU Branch Prediction & Performance

Modern CPUs use hardware branch predictors and speculative execution.
- **Predictable branches** (e.g., loop checks that are true 99.9% of the time) have zero latency overhead.
- **Unpredictable branches** (e.g., random conditions `if (rand() % 2 == 0)`) cause a **pipeline flush** upon misprediction, costing 10 to 20 CPU cycles!
- Where extreme throughput is needed (like high-frequency trading), engineers employ **branchless programming** (using bit shifts, arithmetic masks, or lookup tables).

---

## 6. Directory Structure

- [`easy/`](./easy/): 10 problems on leap year calculation, progressive tax brackets, slab billing, and switch state transitions.
- [`medium/`](./medium/): 10 problems on Roman numerals, Reverse Polish Notation, Game of Life rules, and ATM note distribution.
- [`hard/`](./hard/): 8 problems on DFA number validation, expression operators, basic calculator, text justification, and Lisp expression parsers.
