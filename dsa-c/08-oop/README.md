# Object-Oriented Programming & Structures in C

> Emulating OOP in C using structures, unions, bit-fields, encapsulation, inheritance via composition, and polymorphism via function pointer vtables.

---

## 📌 Architectural Overview & C Systems Principles

In C, data structures and algorithms execute directly against physical memory without JVM bytecode, garbage collection overhead, or object headers. Understanding:
1. **Memory Layout**: Stack (automatic allocation, rapid cache hits) vs Heap (`malloc`/`free`, dynamic sizing).
2. **Pointer Semantics**: Explicit address-of (`&`), dereference (`*`), and pointer arithmetic (`*(ptr + i)`).
3. **Data Alignment & Padding**: Hardware alignment requirements and struct padding for CPU bus efficiency.
4. **Cache Locality**: Contiguous arrays maximizing L1/L2 data cache line utilization.

---

## 🗂️ Problem Directory & Difficulty Breakdown

### 🟢 Easy Tier (Foundational & Core Syntax)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ClassAndObjectBasics** | [`easy/01_ClassAndObjectBasics.c`](./easy/01_ClassAndObjectBasics.c) | Foundational logic, boundary checks |
| 2 | **ConstructorTypesAndChaining** | [`easy/02_ConstructorTypesAndChaining.c`](./easy/02_ConstructorTypesAndChaining.c) | Foundational logic, boundary checks |
| 3 | **EncapsulationWithValidation** | [`easy/03_EncapsulationWithValidation.c`](./easy/03_EncapsulationWithValidation.c) | Foundational logic, boundary checks |
| 4 | **SingleAndMultilevelInheritance** | [`easy/04_SingleAndMultilevelInheritance.c`](./easy/04_SingleAndMultilevelInheritance.c) | Foundational logic, boundary checks |
| 5 | **MethodOverridingAndSuper** | [`easy/05_MethodOverridingAndSuper.c`](./easy/05_MethodOverridingAndSuper.c) | Foundational logic, boundary checks |
| 6 | **StaticKeywordDeepDive** | [`easy/06_StaticKeywordDeepDive.c`](./easy/06_StaticKeywordDeepDive.c) | Foundational logic, boundary checks |
| 7 | **FinalKeywordUseCases** | [`easy/07_FinalKeywordUseCases.c`](./easy/07_FinalKeywordUseCases.c) | Foundational logic, boundary checks |
| 8 | **AbstractClassAnimalHierarchy** | [`easy/08_AbstractClassAnimalHierarchy.c`](./easy/08_AbstractClassAnimalHierarchy.c) | Foundational logic, boundary checks |
| 9 | **InterfaceMultipleInheritance** | [`easy/09_InterfaceMultipleInheritance.c`](./easy/09_InterfaceMultipleInheritance.c) | Foundational logic, boundary checks |
| 10 | **ShallowVsDeepCopy** | [`easy/10_ShallowVsDeepCopy.c`](./easy/10_ShallowVsDeepCopy.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ParkingLotSystemDesign** | [`medium/01_ParkingLotSystemDesign.c`](./medium/01_ParkingLotSystemDesign.c) | Optimal time/space, pointers, recursion |
| 2 | **LRUCacheOOPDesign** | [`medium/02_LRUCacheOOPDesign.c`](./medium/02_LRUCacheOOPDesign.c) | Optimal time/space, pointers, recursion |
| 3 | **BankManagementSystem** | [`medium/03_BankManagementSystem.c`](./medium/03_BankManagementSystem.c) | Optimal time/space, pointers, recursion |
| 4 | **ShapeHierarchyPolymorphism** | [`medium/04_ShapeHierarchyPolymorphism.c`](./medium/04_ShapeHierarchyPolymorphism.c) | Optimal time/space, pointers, recursion |
| 5 | **EmployeePayrollSystem** | [`medium/05_EmployeePayrollSystem.c`](./medium/05_EmployeePayrollSystem.c) | Optimal time/space, pointers, recursion |
| 6 | **OnlineShoppingCartSystem** | [`medium/06_OnlineShoppingCartSystem.c`](./medium/06_OnlineShoppingCartSystem.c) | Optimal time/space, pointers, recursion |
| 7 | **LibraryManagementSystem** | [`medium/07_LibraryManagementSystem.c`](./medium/07_LibraryManagementSystem.c) | Optimal time/space, pointers, recursion |
| 8 | **DeckOfCardsBlackjack** | [`medium/08_DeckOfCardsBlackjack.c`](./medium/08_DeckOfCardsBlackjack.c) | Optimal time/space, pointers, recursion |
| 9 | **CoffeeVendingMachineOOP** | [`medium/09_CoffeeVendingMachineOOP.c`](./medium/09_CoffeeVendingMachineOOP.c) | Optimal time/space, pointers, recursion |
| 10 | **GenericRepositoryPattern** | [`medium/10_GenericRepositoryPattern.c`](./medium/10_GenericRepositoryPattern.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ThreadSafeSingletonPattern** | [`hard/01_ThreadSafeSingletonPattern.c`](./hard/01_ThreadSafeSingletonPattern.c) | Complex invariants, state trees, low-level bits |
| 2 | **PubSubObserverPattern** | [`hard/02_PubSubObserverPattern.c`](./hard/02_PubSubObserverPattern.c) | Complex invariants, state trees, low-level bits |
| 3 | **FactoryAndBuilderDesignPattern** | [`hard/03_FactoryAndBuilderDesignPattern.c`](./hard/03_FactoryAndBuilderDesignPattern.c) | Complex invariants, state trees, low-level bits |
| 4 | **InMemoryFileSystemOOP** | [`hard/04_InMemoryFileSystemOOP.c`](./hard/04_InMemoryFileSystemOOP.c) | Complex invariants, state trees, low-level bits |
| 5 | **TokenBucketRateLimiterOOP** | [`hard/05_TokenBucketRateLimiterOOP.c`](./hard/05_TokenBucketRateLimiterOOP.c) | Complex invariants, state trees, low-level bits |
| 6 | **CompositeAndDecoratorPattern** | [`hard/06_CompositeAndDecoratorPattern.c`](./hard/06_CompositeAndDecoratorPattern.c) | Complex invariants, state trees, low-level bits |
| 7 | **StateDesignPatternVendingMachine** | [`hard/07_StateDesignPatternVendingMachine.c`](./hard/07_StateDesignPatternVendingMachine.c) | Complex invariants, state trees, low-level bits |
| 8 | **CommandAndUndoRedoManager** | [`hard/08_CommandAndUndoRedoManager.c`](./hard/08_CommandAndUndoRedoManager.c) | Complex invariants, state trees, low-level bits |

---

## 🛠️ Compilation & Memory Verification

```bash
# Standard compilation with C11 and strict warnings
gcc -std=c11 -Wall -Wextra -O2 easy/01_ProblemName.c -o solution
./solution

# Memory leak verification with AddressSanitizer
gcc -std=c11 -Wall -Wextra -g -fsanitize=address easy/01_ProblemName.c -o solution
./solution
```
