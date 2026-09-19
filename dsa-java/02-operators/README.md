# Topic 02: Operators (Arithmetic, Relational, Logical, Bitwise, Assignment)

Welcome to **Topic 02** of the **Java DSA & Interview Preparation** master series.
Operators are the foundational constructs that manipulate variables and values in Java. Mastering Java operators requires understanding not only basic arithmetic, but also **two's complement bit manipulation**, **short-circuit logic**, **strict evaluation ordering**, and subtle **implicit casting traps**.

---

## 1. Operator Categories Overview

| Category | Operators | Description | Associativity |
| :--- | :--- | :--- | :--- |
| **Unary** | `++`, `--`, `+`, `-`, `~`, `!`, `(type)` | Pre/post increment/decrement, bitwise complement, logical NOT, cast | Right-to-Left |
| **Arithmetic** | `*`, `/`, `%`, `+`, `-` | Multiplicative & additive mathematical operations | Left-to-Right |
| **Shift** | `<<`, `>>`, `>>>` | Signed left shift, signed right shift, unsigned right shift | Left-to-Right |
| **Relational** | `<`, `<=`, `>`, `>=`, `instanceof` | Comparison between operands | Left-to-Right |
| **Equality** | `==`, `!=` | Value equality for primitives, reference identity for objects | Left-to-Right |
| **Bitwise AND** | `&` | Bitwise AND / Non-short-circuit boolean AND | Left-to-Right |
| **Bitwise XOR** | `^` | Bitwise exclusive OR | Left-to-Right |
| **Bitwise OR** | `\|` | Bitwise inclusive OR / Non-short-circuit boolean OR | Left-to-Right |
| **Logical AND** | `&&` | Short-circuit boolean AND | Left-to-Right |
| **Logical OR** | `\|\|` | Short-circuit boolean OR | Left-to-Right |
| **Ternary** | `? :` | Conditional inline expression | Right-to-Left |
| **Assignment** | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `^=`, `\|=`, `<<=`, `>>=`, `>>>=` | Assign with optional compound operation | Right-to-Left |

---

## 2. Java Operator Precedence (Highest to Lowest)

Remember the classic operator precedence bug:
```java
int result = 1 << 2 + 3; 
// Evaluates as: 1 << (2 + 3) = 1 << 5 = 32
// NOT as: (1 << 2) + 3 = 4 + 3 = 7
```

```
1. Postfix:           expr++, expr--
2. Unary:             ++expr, --expr, +expr, -expr, ~expr, !expr
3. Multiplicative:    *, /, %
4. Additive:          +, -
5. Shift:             <<, >>, >>>
6. Relational:        <, >, <=, >=, instanceof
7. Equality:          ==, !=
8. Bitwise AND:       &
9. Bitwise XOR:       ^
10. Bitwise OR:       |
11. Logical AND:      &&
12. Logical OR:       ||
13. Ternary:          ? :
14. Assignment:       =, +=, -=, *=, /=, %=, &=, ^=, |=, <<=, >>=, >>>=
```

---

## 3. Critical Interview Gotchas & Traps

### A. Compound Assignment Implicit Casting Trap
In standard assignment, mixing types without explicit cast causes a compilation error. However, compound assignments **automatically insert an implicit cast**:
```java
short s = 5;
// s = s + 5; // COMPILE ERROR: Type mismatch cannot convert from int to short

s += 5;       // COMPILES CLEANLY! Equivalent to: s = (short)(s + 5);

byte b = 127;
b += 1;       // COMPILES! b overflows to -128 without any warning!
```

### B. Post-Increment Evaluation Trap (`x = x++`)
In Java, operand evaluation occurs strictly from left to right:
```java
int x = 5;
x = x++; 
System.out.println(x); // PRINTS 5, NOT 6!
// Step 1: Temporary variable saves original x (5).
// Step 2: x is incremented to 6.
// Step 3: Assignment writes original saved value (5) back to x!
```

### C. Modulo with Negative Operands
Java calculates `%` as: `a % b = a - (b * (a / b))`. The sign of the result **always matches the sign of the dividend `a`**:
```java
 7 %  3 ==  1
-7 %  3 == -1  // Dividend is negative!
 7 % -3 ==  1  // Divisor sign is ignored in result!
-7 % -3 == -1
```
> [!TIP]
> For standard mathematical modulo (always non-negative), use `Math.floorMod(a, b)`:
> `Math.floorMod(-7, 3) == 2`.

### D. Short-Circuit Evaluation (`&&` vs `&`, `||` vs `|`)
- `&&` and `||` stop evaluating as soon as the outcome is determined.
- `&` and `|` evaluate **both sides unconditionally** when used on booleans:
```java
String s = null;
if (s != null && s.length() > 0) { ... } // SAFE: short-circuits on null

if (s != null & s.length() > 0) { ... }  // THROWS NullPointerException!
```

### E. Signed (`>>`) vs Unsigned (`>>>`) Right Shift
- `>>` (Arithmetic Shift): Preserves sign bit (replicates MSB 1 for negative, 0 for positive).
- `>>>` (Logical Shift): Always shifts in 0s at the MSB, treating the number as unsigned.
```java
-8 >> 2   == -2
-8 >>> 2  == 1073741822  // 00111111 11111111 11111111 11111110
```

---

## 4. Problem Directory Roadmap

- [`easy/`](./easy/): 10 core interview problems on arithmetic, logical short-circuit, pre/post increment, compound casting, and foundational bitwise checks.
- [`medium/`](./medium/): 10 algorithmic problems implementing arithmetic without math operators, bitwise reversals, Hamming distance, and powers of four.
- [`hard/`](./hard/): 8 advanced FAANG interview problems on power sets, Trie XOR maximization, submask enumeration, missing numbers, and bitmask dynamic programming.
