# C Strings, Character Arrays & Memory Safety

> Null-terminated character arrays, pointer arithmetic on strings, safe vs unsafe string.h APIs, KMP search, Rabin-Karp, and buffer overflow defense.

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
| 1 | **StringPoolAndImmutabilityDemo** | [`easy/01_StringPoolAndImmutabilityDemo.c`](./easy/01_StringPoolAndImmutabilityDemo.c) | Foundational logic, boundary checks |
| 2 | **ReverseStringAndWords** | [`easy/02_ReverseStringAndWords.c`](./easy/02_ReverseStringAndWords.c) | Foundational logic, boundary checks |
| 3 | **ValidPalindromeSimple** | [`easy/03_ValidPalindromeSimple.c`](./easy/03_ValidPalindromeSimple.c) | Foundational logic, boundary checks |
| 4 | **ValidAnagramFrequency** | [`easy/04_ValidAnagramFrequency.c`](./easy/04_ValidAnagramFrequency.c) | Foundational logic, boundary checks |
| 5 | **LongestCommonPrefixHorizontal** | [`easy/05_LongestCommonPrefixHorizontal.c`](./easy/05_LongestCommonPrefixHorizontal.c) | Foundational logic, boundary checks |
| 6 | **FirstUniqueCharacterInString** | [`easy/06_FirstUniqueCharacterInString.c`](./easy/06_FirstUniqueCharacterInString.c) | Foundational logic, boundary checks |
| 7 | **IsomorphicStringsMapping** | [`easy/07_IsomorphicStringsMapping.c`](./easy/07_IsomorphicStringsMapping.c) | Foundational logic, boundary checks |
| 8 | **LengthOfLastWord** | [`easy/08_LengthOfLastWord.c`](./easy/08_LengthOfLastWord.c) | Foundational logic, boundary checks |
| 9 | **AddStringsWithoutBigInt** | [`easy/09_AddStringsWithoutBigInt.c`](./easy/09_AddStringsWithoutBigInt.c) | Foundational logic, boundary checks |
| 10 | **DefangingAnIPAddress** | [`easy/10_DefangingAnIPAddress.c`](./easy/10_DefangingAnIPAddress.c) | Foundational logic, boundary checks |

### 🟡 Medium Tier (Interview Core & Optimizations)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **LongestSubstringWithoutRepeating** | [`medium/01_LongestSubstringWithoutRepeating.c`](./medium/01_LongestSubstringWithoutRepeating.c) | Optimal time/space, pointers, recursion |
| 2 | **GroupAnagramsCanonical** | [`medium/02_GroupAnagramsCanonical.c`](./medium/02_GroupAnagramsCanonical.c) | Optimal time/space, pointers, recursion |
| 3 | **LongestPalindromicSubstringExpand** | [`medium/03_LongestPalindromicSubstringExpand.c`](./medium/03_LongestPalindromicSubstringExpand.c) | Optimal time/space, pointers, recursion |
| 4 | **StringToIntegerAtoi** | [`medium/04_StringToIntegerAtoi.c`](./medium/04_StringToIntegerAtoi.c) | Optimal time/space, pointers, recursion |
| 5 | **CompareVersionNumbers** | [`medium/05_CompareVersionNumbers.c`](./medium/05_CompareVersionNumbers.c) | Optimal time/space, pointers, recursion |
| 6 | **CountAndSayRLE** | [`medium/06_CountAndSayRLE.c`](./medium/06_CountAndSayRLE.c) | Optimal time/space, pointers, recursion |
| 7 | **RepeatedDnaSequencesRollingHash** | [`medium/07_RepeatedDnaSequencesRollingHash.c`](./medium/07_RepeatedDnaSequencesRollingHash.c) | Optimal time/space, pointers, recursion |
| 8 | **MultiplyStringsElementary** | [`medium/08_MultiplyStringsElementary.c`](./medium/08_MultiplyStringsElementary.c) | Optimal time/space, pointers, recursion |
| 9 | **SimplifyPathCanonical** | [`medium/09_SimplifyPathCanonical.c`](./medium/09_SimplifyPathCanonical.c) | Optimal time/space, pointers, recursion |
| 10 | **DecodeStringNestedStack** | [`medium/10_DecodeStringNestedStack.c`](./medium/10_DecodeStringNestedStack.c) | Optimal time/space, pointers, recursion |

### 🔴 Hard Tier (Advanced Algorithmic Puzzles & Systems Optimization)
| # | Problem | Source File | Key Concepts |
|---|---------|-------------|--------------|
| 1 | **KMPStringMatchingAlgorithm** | [`hard/01_KMPStringMatchingAlgorithm.c`](./hard/01_KMPStringMatchingAlgorithm.c) | Complex invariants, state trees, low-level bits |
| 2 | **RabinKarpRollingHash** | [`hard/02_RabinKarpRollingHash.c`](./hard/02_RabinKarpRollingHash.c) | Complex invariants, state trees, low-level bits |
| 3 | **MinimumWindowSubstring** | [`hard/03_MinimumWindowSubstring.c`](./hard/03_MinimumWindowSubstring.c) | Complex invariants, state trees, low-level bits |
| 4 | **WildcardMatchingDP** | [`hard/04_WildcardMatchingDP.c`](./hard/04_WildcardMatchingDP.c) | Complex invariants, state trees, low-level bits |
| 5 | **RegularExpressionMatchingDP** | [`hard/05_RegularExpressionMatchingDP.c`](./hard/05_RegularExpressionMatchingDP.c) | Complex invariants, state trees, low-level bits |
| 6 | **ManachersLongestPalindrome** | [`hard/06_ManachersLongestPalindrome.c`](./hard/06_ManachersLongestPalindrome.c) | Complex invariants, state trees, low-level bits |
| 7 | **WordBreakTwoBacktracking** | [`hard/07_WordBreakTwoBacktracking.c`](./hard/07_WordBreakTwoBacktracking.c) | Complex invariants, state trees, low-level bits |
| 8 | **ShortestPalindromeKMP** | [`hard/08_ShortestPalindromeKMP.c`](./hard/08_ShortestPalindromeKMP.c) | Complex invariants, state trees, low-level bits |

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
