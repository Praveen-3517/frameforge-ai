# Conditionals, Branching & Decision Control in C

> If-else statements, switch-case jump tables, ternary operators, Duff's device, and structured error handling patterns using goto cleanup.

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
| 1 | **CheckLeapYear** | [`easy/01_CheckLeapYear.c`](./easy/01_CheckLeapYear.c) | Foundational logic, boundary checks |
| 2 | **GradeCalculatorSwitch** | [`easy/02_GradeCalculatorSwitch.c`](./easy/02_GradeCalculatorSwitch.c) | Foundational logic, boundary checks |
| 3 | **VowelOrConsonant** | [`easy/03_VowelOrConsonant.c`](./easy/03_VowelOrConsonant.c) | Foundational logic, boundary checks |
| 4 | **QuadrantOfCoordinate** | [`easy/04_QuadrantOfCoordinate.c`](./easy/04_QuadrantOfCoordinate.c) | Foundational logic, boundary checks |
| 5 | **TriangleValidityAndType** | [`easy/05_TriangleValidityAndType.c`](./easy/05_TriangleValidityAndType.c) | Foundational logic, boundary checks |
| 6 | **SimpleCalculatorSwitch** | [`easy/06_SimpleCalculatorSwitch.c`](./easy/06_SimpleCalculatorSwitch.c) | Foundational logic, boundary checks |
| 7 | **DaysInMonthCalculator** | [`easy/07_DaysInMonthCalculator.c`](./easy/07_DaysInMonthCalculator.c) | Foundational logic, boundary checks |
| 8 | **TrafficLightStateSwitch** | [`easy/08_TrafficLightStateSwitch.c`](./easy/08_TrafficLightStateSwitch.c) | Foundational logic, boundary checks |
| 9 | **TaxBracketCalculator** | [`easy/09_TaxBracketCalculator.c`](./easy/09_TaxBracketCalculator.c) | Foundational logic, boundary checks |
| 10 | **ElectricityBillSlabRate** | [`easy/10_ElectricityBillSlabRate.c`](./easy/10_ElectricityBillSlabRate.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **RockPaperScissorsExtended** | [`medium/01_RockPaperScissorsExtended.c`](./medium/01_RockPaperScissorsExtended.c) | Optimal time/space, pointers, recursion |
| 2 | **RomanToInteger** | [`medium/02_RomanToInteger.c`](./medium/02_RomanToInteger.c) | Optimal time/space, pointers, recursion |
| 3 | **IntegerToRoman** | [`medium/03_IntegerToRoman.c`](./medium/03_IntegerToRoman.c) | Optimal time/space, pointers, recursion |
| 4 | **ValidParenthesesSimpleSwitch** | [`medium/04_ValidParenthesesSimpleSwitch.c`](./medium/04_ValidParenthesesSimpleSwitch.c) | Optimal time/space, pointers, recursion |
| 5 | **NextPermutationConditionals** | [`medium/05_NextPermutationConditionals.c`](./medium/05_NextPermutationConditionals.c) | Optimal time/space, pointers, recursion |
| 6 | **TimeInWordsClock** | [`medium/06_TimeInWordsClock.c`](./medium/06_TimeInWordsClock.c) | Optimal time/space, pointers, recursion |
| 7 | **FindClosestValidDate** | [`medium/07_FindClosestValidDate.c`](./medium/07_FindClosestValidDate.c) | Optimal time/space, pointers, recursion |
| 8 | **ATMDispenserGreedy** | [`medium/08_ATMDispenserGreedy.c`](./medium/08_ATMDispenserGreedy.c) | Optimal time/space, pointers, recursion |
| 9 | **EvaluateReversePolishNotation** | [`medium/09_EvaluateReversePolishNotation.c`](./medium/09_EvaluateReversePolishNotation.c) | Optimal time/space, pointers, recursion |
| 10 | **GameOfLifeTransitionRules** | [`medium/10_GameOfLifeTransitionRules.c`](./medium/10_GameOfLifeTransitionRules.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ValidNumberRegexState** | [`hard/01_ValidNumberRegexState.c`](./hard/01_ValidNumberRegexState.c) | Complex invariants, state trees, low-level bits |
| 2 | **BasicCalculatorWithParentheses** | [`hard/02_BasicCalculatorWithParentheses.c`](./hard/02_BasicCalculatorWithParentheses.c) | Complex invariants, state trees, low-level bits |
| 3 | **ExpressionAddOperators** | [`hard/03_ExpressionAddOperators.c`](./hard/03_ExpressionAddOperators.c) | Complex invariants, state trees, low-level bits |
| 4 | **TextJustificationConditionals** | [`hard/04_TextJustificationConditionals.c`](./hard/04_TextJustificationConditionals.c) | Complex invariants, state trees, low-level bits |
| 5 | **ParseLispExpression** | [`hard/05_ParseLispExpression.c`](./hard/05_ParseLispExpression.c) | Complex invariants, state trees, low-level bits |
| 6 | **OptimalAccountBalancing** | [`hard/06_OptimalAccountBalancing.c`](./hard/06_OptimalAccountBalancing.c) | Complex invariants, state trees, low-level bits |
| 7 | **IntegerToEnglishWords** | [`hard/07_IntegerToEnglishWords.c`](./hard/07_IntegerToEnglishWords.c) | Complex invariants, state trees, low-level bits |
| 8 | **ShortestPathWithObstaclesElimination** | [`hard/08_ShortestPathWithObstaclesElimination.c`](./hard/08_ShortestPathWithObstaclesElimination.c) | Complex invariants, state trees, low-level bits |

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
