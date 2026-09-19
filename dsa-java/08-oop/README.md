# Topic 08: Object-Oriented Programming (OOP) in Java

Object-Oriented Programming (OOP) is a programming paradigm based on the concept of "objects", which contain data (fields/attributes) and code (methods/behaviors). Java is designed from the ground up around OOP principles.

---

## Key Concepts

### 1. Classes and Objects
- **Class**: A blueprint or template from which objects are instantiated.
- **Object**: An instance of a class with state and behavior allocated on the heap.
- **Constructors**: Special methods called during object instantiation (`new`). Supports default, parameterized, and copy constructors. Constructor chaining using `this(...)` and `super(...)`.

### 2. The Four Pillars of OOP
1. **Encapsulation**:
   - Bundling data and methods that operate on that data within a single unit.
   - Restricting direct access using access modifiers (`private`, default, `protected`, `public`).
   - Providing controlled access via getters and setters with validation.

2. **Inheritance**:
   - Reusability mechanism where child class derives fields and methods from parent class (`extends`).
   - Java supports single class inheritance and multiple interface implementation (`implements`).
   - Prevents inheritance with the `final` keyword on classes.

3. **Polymorphism**:
   - **Compile-time (Static)**: Method Overloading (same method name, different signatures).
   - **Runtime (Dynamic)**: Method Overriding (`@Override`, virtual method invocation via dynamic dispatch).

4. **Abstraction**:
   - Hiding complex implementation details and exposing only the essential interface.
   - Implemented via **Abstract Classes** (`abstract class`) and **Interfaces** (`interface`).

---

## Abstract Classes vs. Interfaces

| Feature | Abstract Class | Interface |
| :--- | :--- | :--- |
| **Inheritance** | Single (`extends`) | Multiple (`implements`) |
| **Variables** | Can have instance variables, constants, mutable state | Only `public static final` constants |
| **Methods** | Abstract, concrete, final, static | Abstract, `default`, `static`, `private` (Java 9+) |
| **Constructors**| Has constructors (called via `super()`) | No constructors |
| **Speed** | Faster dynamic method lookup | Slight interface table dispatch overhead |
| **Use Case** | Is-a relationship with shared state/code | Can-do / capability contract across unrelated classes |

---

## Important Keywords
- **`this`**: Reference to the current object instance.
- **`super`**: Reference to parent class instance/constructor.
- **`static`**: Belongs to the class rather than individual instances (static variables, static methods, static blocks).
- **`final`**: Constant variable, non-overridable method, or non-inheritable class.

---

## SOLID Principles in Java
- **S**ingle Responsibility Principle: A class should have only one reason to change.
- **O**pen/Closed Principle: Open for extension, closed for modification.
- **L**iskov Substitution Principle: Subtypes must be substitutable for their base types.
- **I**nterface Segregation Principle: Many client-specific interfaces are better than one general-purpose interface.
- **D**ependency Inversion Principle: Depend upon abstractions, not concretions.

---

## Folder Structure
- `easy/`: 10 foundational OOP problems (Classes, Constructors, Encapsulation, Inheritance, Overriding).
- `medium/`: 10 design & architectural problems (Parking Lot, LRU Cache OOP, Banking, Shape Hierarchy).
- `hard/`: 8 complex design patterns and system design implementations (Thread-safe Singleton, Pub-Sub, In-Memory File System).
