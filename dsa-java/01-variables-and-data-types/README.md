# Topic 01: Variables & Data Types in Java

> Master guide covering memory representation, primitive types, wrapper classes, overflow pitfalls, and technical interview gotchas.

---

## 📖 1. Introduction: What is a Variable?
In Java, a **variable** is a named memory location used to store data. Java is a **statically-typed** and **strongly-typed** language:
- **Statically-typed**: Every variable must be declared with a data type before it can be used, and the type cannot change at runtime.
- **Strongly-typed**: Type safety is strictly enforced by the compiler (e.g., you cannot assign a string directly to an integer without explicit parsing).

```java
// Declaration & Initialization
int age = 24;
double salary = 85000.50;
boolean isEmployed = true;
```

---

## 💾 2. Java Memory Architecture: Stack vs. Heap
- **Stack Memory**:
  - Stores primitive values directly (`int x = 10;`).
  - Stores reference variables (pointers) that point to objects on the heap.
  - LIFO (Last-In-First-Out) execution; allocation and deallocation occur automatically with function call frames.
  - Extremely fast.
- **Heap Memory**:
  - Stores all Java Objects (e.g., `String`, `Integer`, `int[]`, custom classes).
  - Managed by the Java Garbage Collector (GC).
  - Shared across all threads.

---

## 🔢 3. The 8 Primitive Data Types

| Data Type | Size (Bits) | Size (Bytes) | Range | Default Value | Wrapper Class |
|:----------|:-----------:|:------------:|:------|:-------------:|:-------------:|
| `byte`    | 8           | 1            | $-128$ to $127$ ($-2^7$ to $2^7-1$) | `0` | `Byte` |
| `short`   | 16          | 2            | $-32,768$ to $32,767$ ($-2^{15}$ to $2^{15}-1$) | `0` | `Short` |
| `int`     | 32          | 4            | $-2,147,483,648$ to $2,147,483,647$ ($-2^{31}$ to $2^{31}-1$) | `0` | `Integer` |
| `long`    | 64          | 8            | $-2^{63}$ to $2^{63}-1$ (approx $\pm 9.22 \times 10^{18}$) | `0L` | `Long` |
| `float`   | 32          | 4            | $\approx \pm 1.4 \times 10^{-45}$ to $\pm 3.4 \times 10^{38}$ (6-7 decimal digits precision) | `0.0f` | `Float` |
| `double`  | 64          | 8            | $\approx \pm 4.9 \times 10^{-324}$ to $\pm 1.8 \times 10^{308}$ (15-16 decimal digits precision) | `0.0d` | `Double` |
| `char`    | 16          | 2            | `'\u0000'` (0) to `'\uffff'` (65,535) (Unsigned 16-bit Unicode) | `'\u0000'` | `Character` |
| `boolean` | JVM-dependent | $\approx 1$ | `true` or `false` | `false` | `Boolean` |

> ⚠️ **Key Note on `char`**: In C/C++, `char` is 8-bit ASCII. In Java, `char` is **16-bit Unicode (UTF-16 code unit)** to support international characters and symbols.

---

## 🔄 4. Type Casting: Widening vs. Narrowing

### A. Widening Casting (Implicit / Automatic)
Converting a smaller type to a larger type size. No data loss occurs.
$$\text{byte} \to \text{short} \to \text{int} \to \text{long} \to \text{float} \to \text{double}$$
```java
int myInt = 9;
double myDouble = myInt; // Automatic casting: 9.0
```

### B. Narrowing Casting (Explicit / Manual)
Converting a larger type to a smaller type size. **Can result in data truncation or overflow**.
$$\text{double} \to \text{float} \to \text{long} \to \text{int} \to \text{short} \to \text{byte}$$
```java
double myDouble = 9.78;
int myInt = (int) myDouble; // Manual casting: 9 (0.78 truncated)

int bigVal = 130;
byte b = (byte) bigVal; // Truncates: -126 (due to 8-bit signed overflow)
```

---

## ⚠️ 5. Top Interview Gotchas & Pitfalls

### Gotcha 1: Integer Overflow
Standard integer arithmetic in Java does not throw an exception on overflow; it silently wraps around like a clock.
```java
int max = Integer.MAX_VALUE; // 2147483647
int overflowed = max + 1;    // -2147483648 (Integer.MIN_VALUE)
```
*Solution*: Use `Math.addExact(a, b)` (throws `ArithmeticException`) or promote calculations to `long`.

### Gotcha 2: The Integer Cache (-128 to 127)
Java caches `Integer` objects between `-128` and `127` for memory efficiency.
```java
Integer a = 100;
Integer b = 100;
System.out.println(a == b); // true (same cached reference)

Integer c = 200;
Integer d = 200;
System.out.println(c == d); // FALSE! (two different objects created on heap)
System.out.println(c.equals(d)); // true (value comparison)
```
*Rule*: **Always use `.equals()` to compare wrapper objects, never `==`**.

### Gotcha 3: Floating Point Precision & Financial Calculations
Floating-point numbers in Java use IEEE 754 binary representation. Many decimal fractions cannot be represented exactly in binary.
```java
double a = 0.1;
double b = 0.2;
System.out.println(a + b == 0.3); // FALSE! (0.30000000000000004)
```
*Rule for Fintech / E-commerce*: **Never use `float` or `double` for currency**. Always use `BigDecimal` with the `String` constructor:
```java
BigDecimal a = new BigDecimal("0.1");
BigDecimal b = new BigDecimal("0.2");
BigDecimal sum = a.add(b); // Exactly 0.3
```

---

## 📁 Problems in this Directory

- [`easy/`](./easy/): 10 Foundational problems on primitive sizes, ASCII, swapping, type casting, and range bounds.
- [`medium/`](./medium/): 10 Optimization & interview questions on wrapper caching, overflow detection, fast power, and manual parsing.
- [`hard/`](./hard/): 8 Advanced problems on bitwise division, IEEE 754 inspection, BigInteger math, and multi-state encoding.
