# Variables, Data Types & Memory Representation in C

> Mastering fundamental C data types, sizes via sizeof, limits.h, IEEE 754 float internals, integer overflow undefined behavior, type promotions, and storage classes.

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
| 1 | **PrimitiveDataTypesDemo** | [`easy/01_PrimitiveDataTypesDemo.c`](./easy/01_PrimitiveDataTypesDemo.c) | Foundational logic, boundary checks |
| 2 | **SwapTwoNumbersWithoutThird** | [`easy/02_SwapTwoNumbersWithoutThird.c`](./easy/02_SwapTwoNumbersWithoutThird.c) | Foundational logic, boundary checks |
| 3 | **ImplicitAndExplicitCasting** | [`easy/03_ImplicitAndExplicitCasting.c`](./easy/03_ImplicitAndExplicitCasting.c) | Foundational logic, boundary checks |
| 4 | **CharToAsciiAndViceVersa** | [`easy/04_CharToAsciiAndViceVersa.c`](./easy/04_CharToAsciiAndViceVersa.c) | Foundational logic, boundary checks |
| 5 | **TemperatureConverter** | [`easy/05_TemperatureConverter.c`](./easy/05_TemperatureConverter.c) | Foundational logic, boundary checks |
| 6 | **SimpleInterestCalculator** | [`easy/06_SimpleInterestCalculator.c`](./easy/06_SimpleInterestCalculator.c) | Foundational logic, boundary checks |
| 7 | **CheckEvenOrOddBitwise** | [`easy/07_CheckEvenOrOddBitwise.c`](./easy/07_CheckEvenOrOddBitwise.c) | Foundational logic, boundary checks |
| 8 | **FindRangeOfPrimitives** | [`easy/08_FindRangeOfPrimitives.c`](./easy/08_FindRangeOfPrimitives.c) | Foundational logic, boundary checks |
| 9 | **DaysToYearsWeeksDays** | [`easy/09_DaysToYearsWeeksDays.c`](./easy/09_DaysToYearsWeeksDays.c) | Foundational logic, boundary checks |
| 10 | **SumOfFirstNNaturalNumbers** | [`easy/10_SumOfFirstNNaturalNumbers.c`](./easy/10_SumOfFirstNNaturalNumbers.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **IntegerCachePitfall** | [`medium/01_IntegerCachePitfall.c`](./medium/01_IntegerCachePitfall.c) | Optimal time/space, pointers, recursion |
| 2 | **DetectIntegerOverflow** | [`medium/02_DetectIntegerOverflow.c`](./medium/02_DetectIntegerOverflow.c) | Optimal time/space, pointers, recursion |
| 3 | **DoublePrecisionIssueAndBigDecimal** | [`medium/03_DoublePrecisionIssueAndBigDecimal.c`](./medium/03_DoublePrecisionIssueAndBigDecimal.c) | Optimal time/space, pointers, recursion |
| 4 | **BinaryToDecimalAndDecimalToBinary** | [`medium/04_BinaryToDecimalAndDecimalToBinary.c`](./medium/04_BinaryToDecimalAndDecimalToBinary.c) | Optimal time/space, pointers, recursion |
| 5 | **CountSetBitsBrianKernighan** | [`medium/05_CountSetBitsBrianKernighan.c`](./medium/05_CountSetBitsBrianKernighan.c) | Optimal time/space, pointers, recursion |
| 6 | **Reverse32BitSignedInteger** | [`medium/06_Reverse32BitSignedInteger.c`](./medium/06_Reverse32BitSignedInteger.c) | Optimal time/space, pointers, recursion |
| 7 | **UnsignedIntComparison** | [`medium/07_UnsignedIntComparison.c`](./medium/07_UnsignedIntComparison.c) | Optimal time/space, pointers, recursion |
| 8 | **FastExponentiation** | [`medium/08_FastExponentiation.c`](./medium/08_FastExponentiation.c) | Optimal time/space, pointers, recursion |
| 9 | **ParseStringToIntegerManual** | [`medium/09_ParseStringToIntegerManual.c`](./medium/09_ParseStringToIntegerManual.c) | Optimal time/space, pointers, recursion |
| 10 | **SquareRootWithoutBuiltin** | [`medium/10_SquareRootWithoutBuiltin.c`](./medium/10_SquareRootWithoutBuiltin.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **DivideTwoIntegersWithoutOperators** | [`hard/01_DivideTwoIntegersWithoutOperators.c`](./hard/01_DivideTwoIntegersWithoutOperators.c) | Complex invariants, state trees, low-level bits |
| 2 | **SingleNumberTwoUniqueElements** | [`hard/02_SingleNumberTwoUniqueElements.c`](./hard/02_SingleNumberTwoUniqueElements.c) | Complex invariants, state trees, low-level bits |
| 3 | **SingleNumberThreeAppearances** | [`hard/03_SingleNumberThreeAppearances.c`](./hard/03_SingleNumberThreeAppearances.c) | Complex invariants, state trees, low-level bits |
| 4 | **IEEE754FloatBitInspector** | [`hard/04_IEEE754FloatBitInspector.c`](./hard/04_IEEE754FloatBitInspector.c) | Complex invariants, state trees, low-level bits |
| 5 | **BigIntegerFactorial** | [`hard/05_BigIntegerFactorial.c`](./hard/05_BigIntegerFactorial.c) | Complex invariants, state trees, low-level bits |
| 6 | **MultiplyTwoLargeStrings** | [`hard/06_MultiplyTwoLargeStrings.c`](./hard/06_MultiplyTwoLargeStrings.c) | Complex invariants, state trees, low-level bits |
| 7 | **AddBinaryStrings** | [`hard/07_AddBinaryStrings.c`](./hard/07_AddBinaryStrings.c) | Complex invariants, state trees, low-level bits |
| 8 | **BitwiseAndOfNumbersRange** | [`hard/08_BitwiseAndOfNumbersRange.c`](./hard/08_BitwiseAndOfNumbersRange.c) | Complex invariants, state trees, low-level bits |

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
