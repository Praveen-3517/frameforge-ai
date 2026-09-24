# Error Handling, Memory Safety & Resilience in C

> Robust error handling in C: return codes, errno, setjmp/longjmp, structured goto cleanups, memory leak detection, and boundary validation.

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
| 1 | **ArithmeticAndNullPointerHandling** | [`easy/01_ArithmeticAndNullPointerHandling.c`](./easy/01_ArithmeticAndNullPointerHandling.c) | Foundational logic, boundary checks |
| 2 | **ArrayIndexAndStringBoundsExceptions** | [`easy/02_ArrayIndexAndStringBoundsExceptions.c`](./easy/02_ArrayIndexAndStringBoundsExceptions.c) | Foundational logic, boundary checks |
| 3 | **FinallyBlockExecutionRules** | [`easy/03_FinallyBlockExecutionRules.c`](./easy/03_FinallyBlockExecutionRules.c) | Foundational logic, boundary checks |
| 4 | **MultipleCatchAndPrecedenceOrder** | [`easy/04_MultipleCatchAndPrecedenceOrder.c`](./easy/04_MultipleCatchAndPrecedenceOrder.c) | Foundational logic, boundary checks |
| 5 | **Java7MultiCatchSyntax** | [`easy/05_Java7MultiCatchSyntax.c`](./easy/05_Java7MultiCatchSyntax.c) | Foundational logic, boundary checks |
| 6 | **TryWithResourcesAutoCloseable** | [`easy/06_TryWithResourcesAutoCloseable.c`](./easy/06_TryWithResourcesAutoCloseable.c) | Foundational logic, boundary checks |
| 7 | **ThrowVsThrowsDifference** | [`easy/07_ThrowVsThrowsDifference.c`](./easy/07_ThrowVsThrowsDifference.c) | Foundational logic, boundary checks |
| 8 | **CustomCheckedException** | [`easy/08_CustomCheckedException.c`](./easy/08_CustomCheckedException.c) | Foundational logic, boundary checks |
| 9 | **CustomUncheckedException** | [`easy/09_CustomUncheckedException.c`](./easy/09_CustomUncheckedException.c) | Foundational logic, boundary checks |
| 10 | **ExceptionChainingAndRootCause** | [`easy/10_ExceptionChainingAndRootCause.c`](./easy/10_ExceptionChainingAndRootCause.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **RobustConfigFileParser** | [`medium/01_RobustConfigFileParser.c`](./medium/01_RobustConfigFileParser.c) | Optimal time/space, pointers, recursion |
| 2 | **DatabaseConnectionPoolResilience** | [`medium/02_DatabaseConnectionPoolResilience.c`](./medium/02_DatabaseConnectionPoolResilience.c) | Optimal time/space, pointers, recursion |
| 3 | **TransactionRollbackOnException** | [`medium/03_TransactionRollbackOnException.c`](./medium/03_TransactionRollbackOnException.c) | Optimal time/space, pointers, recursion |
| 4 | **CsvDataValidatorWithSummaryReport** | [`medium/04_CsvDataValidatorWithSummaryReport.c`](./medium/04_CsvDataValidatorWithSummaryReport.c) | Optimal time/space, pointers, recursion |
| 5 | **CustomExceptionHierarchy** | [`medium/05_CustomExceptionHierarchy.c`](./medium/05_CustomExceptionHierarchy.c) | Optimal time/space, pointers, recursion |
| 6 | **SafeResourceLeakPrevention** | [`medium/06_SafeResourceLeakPrevention.c`](./medium/06_SafeResourceLeakPrevention.c) | Optimal time/space, pointers, recursion |
| 7 | **ApiPayloadValidationPipeline** | [`medium/07_ApiPayloadValidationPipeline.c`](./medium/07_ApiPayloadValidationPipeline.c) | Optimal time/space, pointers, recursion |
| 8 | **GracefulDegradationFallback** | [`medium/08_GracefulDegradationFallback.c`](./medium/08_GracefulDegradationFallback.c) | Optimal time/space, pointers, recursion |
| 9 | **UncheckedExceptionPropagationThread** | [`medium/09_UncheckedExceptionPropagationThread.c`](./medium/09_UncheckedExceptionPropagationThread.c) | Optimal time/space, pointers, recursion |
| 10 | **BatchTaskExecutionErrorAccumulator** | [`medium/10_BatchTaskExecutionErrorAccumulator.c`](./medium/10_BatchTaskExecutionErrorAccumulator.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **ExponentialBackoffRetryExecutor** | [`hard/01_ExponentialBackoffRetryExecutor.c`](./hard/01_ExponentialBackoffRetryExecutor.c) | Complex invariants, state trees, low-level bits |
| 2 | **CircuitBreakerStatePattern** | [`hard/02_CircuitBreakerStatePattern.c`](./hard/02_CircuitBreakerStatePattern.c) | Complex invariants, state trees, low-level bits |
| 3 | **DistributedSagaCompensationCoordinator** | [`hard/03_DistributedSagaCompensationCoordinator.c`](./hard/03_DistributedSagaCompensationCoordinator.c) | Complex invariants, state trees, low-level bits |
| 4 | **ThreadSafeDeadlockDetection** | [`hard/04_ThreadSafeDeadlockDetection.c`](./hard/04_ThreadSafeDeadlockDetection.c) | Complex invariants, state trees, low-level bits |
| 5 | **RateLimitExceededHandlerWithHeaders** | [`hard/05_RateLimitExceededHandlerWithHeaders.c`](./hard/05_RateLimitExceededHandlerWithHeaders.c) | Complex invariants, state trees, low-level bits |
| 6 | **CascadingFailureBulkheadIsolation** | [`hard/06_CascadingFailureBulkheadIsolation.c`](./hard/06_CascadingFailureBulkheadIsolation.c) | Complex invariants, state trees, low-level bits |
| 7 | **SafeDynamicClassLoadingExceptionHandler** | [`hard/07_SafeDynamicClassLoadingExceptionHandler.c`](./hard/07_SafeDynamicClassLoadingExceptionHandler.c) | Complex invariants, state trees, low-level bits |
| 8 | **MemoryLeakOutOfMemoryDiagnostics** | [`hard/08_MemoryLeakOutOfMemoryDiagnostics.c`](./hard/08_MemoryLeakOutOfMemoryDiagnostics.c) | Complex invariants, state trees, low-level bits |

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
