# Topic 19: Bit Manipulation (Bitwise Tricks, Bitmasks, Kernighan's, & Bitmask DP)

## 1. Overview & Binary Representations

Computers represent all integers in base-2 binary format.
- In Java, `int` is a **32-bit signed two's complement** integer, with range $[-2^{31}, 2^{31}-1]$.
- Negative numbers are stored in **Two's Complement**:
  $$-X = \sim X + 1$$

---

## 2. Fundamental Bitwise Operators

| Operator | Syntax | Description | Example |
| :--- | :--- | :--- | :--- |
| **AND** | `a & b` | 1 only if both bits are 1 | `1101 & 1011 = 1001` |
| **OR** | `a \| b` | 1 if either bit is 1 | `1101 \| 0010 = 1111` |
| **XOR** | `a ^ b` | 1 if bits differ ($1 \oplus 1 = 0, 0 \oplus 0 = 0$) | `1101 ^ 1001 = 0100` |
| **NOT** | `~a` | Inverts every bit (1 -> 0, 0 -> 1) | `~0 = -1` |
| **Left Shift** | `a << k` | Shifts bits left by $k$ (multiplies by $2^k$) | `3 << 2 = 12` |
| **Arithmetic Right Shift** | `a >> k` | Shifts bits right, preserving sign bit | `-8 >> 1 = -4` |
| **Logical Right Shift** | `a >>> k` | Shifts bits right, filling high bits with 0 | `-1 >>> 1 = 2147483647` |

---

## 3. Essential Bit Manipulation Tricks & Idioms

1. **Check $k$-th bit (0-indexed)**: `(n & (1 << k)) != 0`
2. **Set $k$-th bit**: `n |= (1 << k)`
3. **Clear $k$-th bit**: `n &= ~(1 << k)`
4. **Toggle $k$-th bit**: `n ^= (1 << k)`
5. **Brian Kernighan's Algorithm (Clear lowest set bit)**: `n = n & (n - 1)`
6. **Isolate lowest set bit**: `lowestBit = n & (-n)`
7. **Check Power of 2**: `n > 0 && (n & (n - 1)) == 0`
8. **In-place Swap**: `a ^= b; b ^= a; a ^= b;`
9. **XOR Cancellation Property**: $X \oplus X = 0$ and $X \oplus 0 = X$.
10. **Iterate all submasks of a bitmask $M$**:
    ```java
    for (int sub = M; sub > 0; sub = (sub - 1) & M) {
        // processes every valid submask
    }
    ```

---

## 4. Directory Structure

```
19-bit-manipulation/
├── README.md
├── easy/
│   ├── 01_SingleNumberXOR.java
│   ├── 02_NumberOfOneBitsKernighan.java
│   ├── 03_PowerOfTwoBitCheck.java
│   ├── 04_CountingBitsBitmask.java
│   ├── 05_ReverseBits32BitInteger.java
│   ├── 06_MissingNumberXOR.java
│   ├── 07_AddBinaryStrings.java
│   ├── 08_HammingDistanceBits.java
│   ├── 09_BinaryNumberWithAlternatingBits.java
│   └── 10_PowerOfFourBitwise.java
├── medium/
│   ├── 01_SubsetsBitmaskGeneration.java
│   ├── 02_SingleNumberTwoEveryElementThreeTimes.java
│   ├── 03_SingleNumberThreeTwoUniqueElements.java
│   ├── 04_BitwiseANDOfNumbersRange.java
│   ├── 05_DivideTwoIntegersBitShift.java
│   ├── 06_SumOfTwoIntegersWithoutPlusMinus.java
│   ├── 07_MaximumXOROfTwoNumbersInArray.java
│   ├── 08_TotalHammingDistanceAllPairs.java
│   ├── 09_GrayCodeSequenceGeneration.java
│   └── 10_RepeatedDNASequencesBitmask.java
└── hard/
    ├── 01_TravelingSalesmanBitmaskDP.java
    ├── 02_NumberOfValidWordsForEveryPuzzle.java
    ├── 03_MaximumScoreWordsFormedByLetters.java
    ├── 04_SmallestSufficientTeamBitmaskDP.java
    ├── 05_ShortestPathVisitingAllNodesBitmaskBFS.java
    ├── 06_MaximumStudentsTakingExamBitmaskDP.java
    ├── 07_FindLongestAwesomeSubstringBitmask.java
    └── 08_NQueensBitmaskBacktracking.java
```
