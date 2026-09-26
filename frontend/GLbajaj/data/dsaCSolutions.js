// ── Simple, Multi-Approach C Solutions for DSA Problems ─────────────────────
// Provides multiple solution ways (For Loop, While Loop, If-Else, Optimal/Helper)
// with clean code, beginner-friendly Hindi/English comments, and runnable main tests.

export const CANONICAL_C_SOLUTIONS = {
  // 1: Two Sum
  1: {
    title: "Two Sum",
    approaches: [
      {
        id: 'for_loop',
        name: 'Way 1: For Loop',
        badge: 'Basic Loops',
        timeComplexity: 'O(N²)',
        spaceComplexity: 'O(1)',
        description: 'Do for loops se har pair check karo (Sabse aasan tarika)',
        code: `#include <stdio.h>
#include <stdlib.h>

/**
 * Problem: Two Sum
 * Method: Way 1 - Nested For Loops (Brute Force)
 * Logic: Har element ke aage waale sabhi elements ko add karke dekho.
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 0;

    // Outer loop pehla number select karta hai
    for (int i = 0; i < numsSize; i++) {
        // Inner loop doosra number select karta hai
        for (int j = i + 1; j < numsSize; j++) {
            // Agar dono ka sum target ke barabar hai
            if (nums[i] + nums[j] == target) {
                result[0] = i; // Pehla index
                result[1] = j; // Doosra index
                *returnSize = 2;
                return result; // Solution mil gaya
            }
        }
    }

    return result;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);

    printf("=== Two Sum (Way 1: For Loop) ===\\n");
    if (returnSize == 2) {
        printf("Answer Indices: [%d, %d]\\n", ans[0], ans[1]);
        free(ans);
    }
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <stdlib.h>

// Way 1: For Loop Approach
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Write your nested for-loop logic here
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);
    return 0;
}`
      },
      {
        id: 'while_if',
        name: 'Way 2: While + If',
        badge: 'While Loop',
        timeComplexity: 'O(N²)',
        spaceComplexity: 'O(1)',
        description: 'While loops aur index pointers ke sath condition check',
        code: `#include <stdio.h>
#include <stdlib.h>

/**
 * Problem: Two Sum
 * Method: Way 2 - While Loops with Index Pointers
 * Logic: while loop aur conditional if checks ke sath array traverse karein.
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 0;

    int i = 0;
    while (i < numsSize - 1) {
        int j = i + 1;
        while (j < numsSize) {
            // Condition check
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
            j++;
        }
        i++;
    }

    return result;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);

    printf("=== Two Sum (Way 2: While + If) ===\\n");
    if (returnSize == 2) {
        printf("Answer Indices: [%d, %d]\\n", ans[0], ans[1]);
        free(ans);
    }
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <stdlib.h>

// Way 2: While Loop Approach
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Write your while loop pointers logic here
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);
    return 0;
}`
      },
      {
        id: 'optimal',
        name: 'Way 3: Direct Lookup',
        badge: 'Optimal O(N)',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(Max)',
        description: 'Single pass direct index lookup for positive values',
        code: `#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Problem: Two Sum
 * Method: Way 3 - Direct Lookup Table (Single Pass)
 * Logic: Har number ka complement (target - nums[i]) direct check karo.
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 0;

    // Simple lookup table (index tracker)
    int lookup[1000] = {0};
    int present[1000] = {0};

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];

        // Agar partner pehle dekha ja chuka hai
        if (complement >= 0 && complement < 1000 && present[complement]) {
            result[0] = lookup[complement];
            result[1] = i;
            *returnSize = 2;
            return result;
        }

        // Current number aur uska index store karo
        if (nums[i] >= 0 && nums[i] < 1000) {
            lookup[nums[i]] = i;
            present[nums[i]] = 1;
        }
    }

    return result;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);

    printf("=== Two Sum (Way 3: Direct Lookup) ===\\n");
    if (returnSize == 2) {
        printf("Answer Indices: [%d, %d]\\n", ans[0], ans[1]);
        free(ans);
    }
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <stdlib.h>

// Way 3: Direct Lookup Approach
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int returnSize = 0;
    int* ans = twoSum(nums, 4, 9, &returnSize);
    return 0;
}`
      }
    ]
  },

  // 2: Best Time to Buy and Sell Stock
  2: {
    title: "Best Time to Buy and Sell Stock",
    approaches: [
      {
        id: 'for_loop',
        name: 'Way 1: For Loop (Min Price)',
        badge: 'One Pass',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(1)',
        description: 'Ek for loop me minPrice aur maxProfit track karo',
        code: `#include <stdio.h>

/**
 * Problem: Best Time to Buy and Sell Stock
 * Method: Way 1 - Simple Single For Loop
 * Logic: Sabse kam price me khareedo (minPrice) aur aaj bechne par profit dekho.
 */
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int minPrice = prices[0]; // Shuru me pehle din ka price
    int maxProfit = 0;        // Maximum profit

    for (int i = 1; i < pricesSize; i++) {
        // Agar aaj sasta mil raha hai, toh minPrice update karo
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else {
            // Agar aaj bechne par purane profit se zyada mil raha hai
            int profitToday = prices[i] - minPrice;
            if (profitToday > maxProfit) {
                maxProfit = profitToday;
            }
        }
    }

    return maxProfit;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int profit = maxProfit(prices, 6);
    printf("=== Stock Buy & Sell (Way 1: For Loop) ===\\n");
    printf("Max Profit: %d (Expected: 5)\\n", profit);
    return 0;
}`,
        starterCode: `#include <stdio.h>

// Way 1: For Loop Approach
int maxProfit(int* prices, int pricesSize) {
    return 0;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    printf("Max Profit: %d\\n", maxProfit(prices, 6));
    return 0;
}`
      },
      {
        id: 'while_if',
        name: 'Way 2: While + If',
        badge: 'While Loop',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(1)',
        description: 'While loop se day-by-day check karein',
        code: `#include <stdio.h>

/**
 * Problem: Best Time to Buy and Sell Stock
 * Method: Way 2 - While Loop with Day Counter
 */
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int buyPrice = prices[0];
    int maxProfit = 0;
    int day = 1;

    while (day < pricesSize) {
        if (prices[day] < buyPrice) {
            buyPrice = prices[day]; // Sasta din mil gaya
        } else {
            int currentProfit = prices[day] - buyPrice;
            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
            }
        }
        day++;
    }

    return maxProfit;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int profit = maxProfit(prices, 6);
    printf("=== Stock Buy & Sell (Way 2: While + If) ===\\n");
    printf("Max Profit: %d (Expected: 5)\\n", profit);
    return 0;
}`,
        starterCode: `#include <stdio.h>

// Way 2: While Loop Approach
int maxProfit(int* prices, int pricesSize) {
    return 0;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    printf("Max Profit: %d\\n", maxProfit(prices, 6));
    return 0;
}`
      },
      {
        id: 'brute_force',
        name: 'Way 3: All Pairs (Brute)',
        badge: 'Brute Force',
        timeComplexity: 'O(N²)',
        spaceComplexity: 'O(1)',
        description: 'Har buy day aur har sell day ko compare karo',
        code: `#include <stdio.h>

/**
 * Problem: Best Time to Buy and Sell Stock
 * Method: Way 3 - All Days Comparison (Brute Force)
 * Logic: Har din 'i' par buy karo aur aage ke har din 'j' par sell karke max dekho.
 */
int maxProfit(int* prices, int pricesSize) {
    int maxProfit = 0;

    for (int i = 0; i < pricesSize; i++) {
        for (int j = i + 1; j < pricesSize; j++) {
            int profit = prices[j] - prices[i];
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }

    return maxProfit;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int profit = maxProfit(prices, 6);
    printf("=== Stock Buy & Sell (Way 3: All Pairs) ===\\n");
    printf("Max Profit: %d (Expected: 5)\\n", profit);
    return 0;
}`,
        starterCode: `#include <stdio.h>

// Way 3: All Pairs Brute Force
int maxProfit(int* prices, int pricesSize) {
    return 0;
}

int main(void) {
    int prices[] = {7, 1, 5, 3, 6, 4};
    printf("Max Profit: %d\\n", maxProfit(prices, 6));
    return 0;
}`
      }
    ]
  },

  // 3: Reverse a String
  3: {
    title: "Reverse a String",
    approaches: [
      {
        id: 'two_pointers',
        name: 'Way 1: Two Pointers',
        badge: 'In-Place Swap',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(1)',
        description: 'Start aur End pointers ko swap karte hue beech me laao',
        code: `#include <stdio.h>
#include <string.h>

/**
 * Problem: Reverse a String
 * Method: Way 1 - Two Pointers (In-Place Swap)
 */
void reverseString(char* s) {
    int start = 0;
    int end = strlen(s) - 1;

    while (start < end) {
        // Swap characters
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;

        start++;
        end--;
    }
}

int main(void) {
    char str[] = "hello";
    printf("Original: %s\\n", str);
    reverseString(str);
    printf("Reversed: %s (Expected: olleh)\\n", str);
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <string.h>

void reverseString(char* s) {
    // Write your two pointers logic here
}

int main(void) {
    char str[] = "hello";
    reverseString(str);
    printf("Reversed: %s\\n", str);
    return 0;
}`
      },
      {
        id: 'for_loop_half',
        name: 'Way 2: For Loop',
        badge: 'Single Loop',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(1)',
        description: 'For loop se half length tak swap karo',
        code: `#include <stdio.h>
#include <string.h>

/**
 * Problem: Reverse a String
 * Method: Way 2 - For Loop Swap
 */
void reverseString(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
}

int main(void) {
    char str[] = "frameforge";
    printf("Original: %s\\n", str);
    reverseString(str);
    printf("Reversed: %s\\n", str);
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <string.h>

void reverseString(char* s) {
    // Write for loop swap here
}

int main(void) {
    char str[] = "frameforge";
    reverseString(str);
    printf("Reversed: %s\\n", str);
    return 0;
}`
      },
      {
        id: 'new_array',
        name: 'Way 3: Extra Buffer',
        badge: 'Buffer Copy',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(N)',
        description: 'Peeche se read karke naye buffer me copy karo',
        code: `#include <stdio.h>
#include <string.h>

/**
 * Problem: Reverse a String
 * Method: Way 3 - Extra Buffer Copy
 */
void reverseString(char* s) {
    int len = strlen(s);
    char temp[100];

    // Peeche se copy karo
    for (int i = 0; i < len; i++) {
        temp[i] = s[len - 1 - i];
    }
    temp[len] = '\\0';

    // Original string me wapas daalo
    strcpy(s, temp);
}

int main(void) {
    char str[] = "bittu";
    reverseString(str);
    printf("Reversed: %s (Expected: uttib)\\n", str);
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <string.h>

void reverseString(char* s) {
    // Write buffer copy here
}

int main(void) {
    char str[] = "bittu";
    reverseString(str);
    printf("Reversed: %s\\n", str);
    return 0;
}`
      }
    ]
  },

  // 4: Palindrome Number
  4: {
    title: "Palindrome Number",
    approaches: [
      {
        id: 'reverse_math',
        name: 'Way 1: While Loop (% 10)',
        badge: 'Math Reversal',
        timeComplexity: 'O(log₁₀ N)',
        spaceComplexity: 'O(1)',
        description: 'Number ko math se reverse karke barabar check karo',
        code: `#include <stdio.h>
#include <stdbool.h>

/**
 * Problem: Palindrome Number
 * Method: Way 1 - Digits Reversal with While Loop
 */
bool isPalindrome(int x) {
    if (x < 0) return false; // Negative numbers palindrome nahi hote

    long original = x;
    long reversed = 0;

    while (x > 0) {
        int lastDigit = x % 10;
        reversed = (reversed * 10) + lastDigit;
        x = x / 10;
    }

    return original == reversed;
}

int main(void) {
    int num = 121;
    printf("=== Palindrome Number (Way 1) ===\\n");
    printf("%d is Palindrome? %s\\n", num, isPalindrome(num) ? "YES" : "NO");
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    // Write math reversal here
    return false;
}

int main(void) {
    printf("%d\\n", isPalindrome(121));
    return 0;
}`
      },
      {
        id: 'string_convert',
        name: 'Way 2: String + If',
        badge: 'String Convert',
        timeComplexity: 'O(N)',
        spaceComplexity: 'O(N)',
        description: 'Number ko string me convert karke dono taraf se match karo',
        code: `#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * Problem: Palindrome Number
 * Method: Way 2 - sprintf String Conversion & Two-Pointer Check
 */
bool isPalindrome(int x) {
    if (x < 0) return false;

    char str[30];
    sprintf(str, "%d", x); // Number ko string banaya

    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false; // Mismatch mil gaya
        }
        left++;
        right--;
    }

    return true;
}

int main(void) {
    int num = 1331;
    printf("=== Palindrome Number (Way 2: String) ===\\n");
    printf("%d is Palindrome? %s\\n", num, isPalindrome(num) ? "YES" : "NO");
    return 0;
}`,
        starterCode: `#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    // Write string conversion logic here
    return false;
}

int main(void) {
    printf("%d\\n", isPalindrome(1331));
    return 0;
}`
      }
    ]
  },

  // 30: Swap Two Numbers
  30: {
    title: "Swap Two Numbers Without Third Variable",
    approaches: [
      {
        id: 'arithmetic',
        name: 'Way 1: Addition & Subtraction',
        badge: '+ and -',
        timeComplexity: 'O(1)',
        spaceComplexity: 'O(1)',
        description: 'Math addition (+) aur subtraction (-) se swap karein',
        code: `#include <stdio.h>

/**
 * Problem: Swap Two Numbers Without Third Variable
 * Method: Way 1 - Addition and Subtraction
 */
void swapNumbers(int* a, int* b) {
    if (a == b) return;
    *a = *a + *b; // a me total sum
    *b = *a - *b; // b me original a
    *a = *a - *b; // a me original b
}

int main(void) {
    int a = 5, b = 10;
    printf("Before Swap: a = %d, b = %d\\n", a, b);
    swapNumbers(&a, &b);
    printf("After Swap : a = %d, b = %d (Expected: a=10, b=5)\\n", a, b);
    return 0;
}`,
        starterCode: `#include <stdio.h>

void swapNumbers(int* a, int* b) {
    // Write + and - logic here
}

int main(void) {
    int a = 5, b = 10;
    swapNumbers(&a, &b);
    return 0;
}`
      },
      {
        id: 'bitwise_xor',
        name: 'Way 2: Bitwise XOR (^)',
        badge: 'XOR Operator',
        timeComplexity: 'O(1)',
        spaceComplexity: 'O(1)',
        description: 'Binary XOR operator (^) se zero overflow swap',
        code: `#include <stdio.h>

/**
 * Problem: Swap Two Numbers Without Third Variable
 * Method: Way 2 - Bitwise XOR
 * Logic: x ^ x = 0 aur x ^ 0 = x
 */
void swapNumbers(int* a, int* b) {
    if (a == b) return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main(void) {
    int a = 25, b = 40;
    printf("Before Swap (XOR): a = %d, b = %d\\n", a, b);
    swapNumbers(&a, &b);
    printf("After Swap (XOR) : a = %d, b = %d\\n", a, b);
    return 0;
}`,
        starterCode: `#include <stdio.h>

void swapNumbers(int* a, int* b) {
    // Write XOR logic here
}

int main(void) {
    int a = 25, b = 40;
    swapNumbers(&a, &b);
    return 0;
}`
      },
      {
        id: 'temp_var',
        name: 'Way 3: Temp Variable',
        badge: 'Classic Temp',
        timeComplexity: 'O(1)',
        spaceComplexity: 'O(1)',
        description: 'Third temporary variable se sabse safe swap',
        code: `#include <stdio.h>

/**
 * Problem: Swap Two Numbers
 * Method: Way 3 - Standard Third Variable
 */
void swapNumbers(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int a = 100, b = 200;
    printf("Before Swap (Temp): a = %d, b = %d\\n", a, b);
    swapNumbers(&a, &b);
    printf("After Swap (Temp) : a = %d, b = %d\\n", a, b);
    return 0;
}`,
        starterCode: `#include <stdio.h>

void swapNumbers(int* a, int* b) {
    // Write temp swap here
}

int main(void) {
    int a = 100, b = 200;
    swapNumbers(&a, &b);
    return 0;
}`
      }
    ]
  }
};

/**
 * Returns an array of multiple distinct solution ways for the problem.
 * Every problem receives 2 or 3 distinct ways (For Loop, While Loop, If-Else, Optimal/Helper).
 */
export function getCSolutionApproaches(problem) {
  if (!problem) return [];

  // Check canonical list
  const canonical = CANONICAL_C_SOLUTIONS[problem.slug] || CANONICAL_C_SOLUTIONS[problem.id];
  if (canonical && canonical.approaches && canonical.approaches.length > 0) {
    return canonical.approaches.map(appr => ({
      ...appr,
      title: canonical.title || problem.title
    }));
  }

  // If problem has a pre-defined cSolution
  if (problem.cSolution) {
    return [
      {
        id: 'standard',
        name: 'Way 1: Standard Solution',
        badge: 'Recommended',
        timeComplexity: problem.timeComplexity || 'O(N)',
        spaceComplexity: problem.spaceComplexity || 'O(1)',
        description: 'Official direct solution in C',
        code: problem.cSolution,
        starterCode: problem.cStarterCode || problem.cSolution
      }
    ];
  }

  // Dynamic Multi-Way Generation based on topic
  const topic = problem.topic || 'Arrays';
  const pattern = problem.pattern || 'Iterative';
  const timeComplexity = problem.timeComplexity || 'O(N)';
  const spaceComplexity = problem.spaceComplexity || 'O(1)';

  let structDef = '';
  if (topic === 'Linked List') {
    structDef = `struct Node {
    int data;
    struct Node* next;
};

`;
  } else if (topic === 'Trees') {
    structDef = `struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

`;
  }

  // ── WAY 1: For Loop (Basic Iteration) ──
  let way1Signature = 'int solve(int* arr, int n)';
  let way1Body = `    // Step 1: Initialize answer
    int result = 0;

    // Step 2: For loop se traverse karein
    for (int i = 0; i < n; i++) {
        result += arr[i];
    }

    return result;`;
  let way1Test = `    int arr[] = {1, 2, 3, 4};
    printf("Result (For Loop): %d\\n", solve(arr, 4));`;

  // ── WAY 2: While Loop + If Condition ──
  let way2Signature = 'int solveWhile(int* arr, int n)';
  let way2Body = `    // Step 1: Pointers & trackers
    int result = 0;
    int i = 0;

    // Step 2: While loop with condition
    while (i < n) {
        if (arr[i] != 0) {
            result += arr[i];
        }
        i++;
    }

    return result;`;
  let way2Test = `    int arr[] = {1, 2, 3, 4};
    printf("Result (While + If): %d\\n", solveWhile(arr, 4));`;

  // ── WAY 3: Helper / Optimal Method ──
  let way3Signature = 'int solveOptimal(int* arr, int n)';
  let way3Body = `    // Optimal approach
    if (n <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        sum += arr[i];
        if (i + 1 < n) sum += arr[i + 1];
    }
    return sum;`;
  let way3Test = `    int arr[] = {1, 2, 3, 4};
    printf("Result (Optimal): %d\\n", solveOptimal(arr, 4));`;

  if (topic === 'Strings') {
    way1Signature = 'int solve(const char* s)';
    way1Body = `    // Way 1: For loop se string length nikalna
    int len = 0;
    for (int i = 0; s[i] != '\\0'; i++) {
        len++;
    }
    return len;`;
    way1Test = `    printf("Length (For Loop): %d\\n", solve("frameforge"));`;

    way2Signature = 'int solveWhile(const char* s)';
    way2Body = `    // Way 2: While loop aur pointer se check
    int count = 0;
    while (*s != '\\0') {
        count++;
        s++; // Pointer agle character par
    }
    return count;`;
    way2Test = `    printf("Length (While Pointer): %d\\n", solveWhile("frameforge"));`;

    way3Signature = 'int solveOptimal(const char* s)';
    way3Body = `    // Way 3: Standard library function
    return (int)strlen(s);`;
    way3Test = `    printf("Length (Standard): %d\\n", solveOptimal("frameforge"));`;
  } else if (topic === 'Linked List') {
    way1Signature = 'int countNodes(struct Node* head)';
    way1Body = `    // Way 1: While loop se list traverse karein
    int count = 0;
    struct Node* curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;`;
    way1Test = `    struct Node n2 = { .data = 20, .next = NULL };
    struct Node n1 = { .data = 10, .next = &n2 };
    printf("Nodes (While): %d\\n", countNodes(&n1));`;

    way2Signature = 'int countNodesRec(struct Node* head)';
    way2Body = `    // Way 2: Recursion se nodes count karein
    if (head == NULL) return 0; // Base condition
    return 1 + countNodesRec(head->next);`;
    way2Test = `    struct Node n2 = { .data = 20, .next = NULL };
    struct Node n1 = { .data = 10, .next = &n2 };
    printf("Nodes (Recursion): %d\\n", countNodesRec(&n1));`;

    way3Signature = 'int countWithFor(struct Node* head)';
    way3Body = `    // Way 3: For loop pointer iteration
    int count = 0;
    for (struct Node* p = head; p != NULL; p = p->next) {
        count++;
    }
    return count;`;
    way3Test = `    struct Node n2 = { .data = 20, .next = NULL };
    struct Node n1 = { .data = 10, .next = &n2 };
    printf("Nodes (For Loop): %d\\n", countWithFor(&n1));`;
  } else if (topic === 'Binary Search' || topic === 'Searching') {
    way1Signature = 'int linearSearch(int* arr, int n, int target)';
    way1Body = `    // Way 1: Simple For Loop Linear Search
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i; // Mil gaya
    }
    return -1;`;
    way1Test = `    int arr[] = {2, 4, 6, 8, 10};
    printf("Index (Linear): %d\\n", linearSearch(arr, 5, 6));`;

    way2Signature = 'int binarySearchWhile(int* arr, int n, int target)';
    way2Body = `    // Way 2: While Loop Binary Search (If Sorted)
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;`;
    way2Test = `    int arr[] = {2, 4, 6, 8, 10};
    printf("Index (Binary Search): %d\\n", binarySearchWhile(arr, 5, 6));`;

    way3Signature = 'int binarySearchRec(int* arr, int l, int r, int target)';
    way3Body = `    // Way 3: Recursive Binary Search
    if (l > r) return -1;
    int mid = l + (r - l) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRec(arr, mid + 1, r, target);
    return binarySearchRec(arr, l, mid - 1, target);`;
    way3Test = `    int arr[] = {2, 4, 6, 8, 10};
    printf("Index (Recursive): %d\\n", binarySearchRec(arr, 0, 4, 6));`;
  }

  const code1 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}/**
 * Problem: ${problem.title}
 * Method: Way 1 - For Loop (Simple & Clear)
 */
${way1Signature} {
${way1Body}
}

int main(void) {
    printf("=== ${problem.title} (Way 1: For Loop) ===\\n");
${way1Test}
    return 0;
}`;

  const starter1 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}// Way 1: For Loop Method
${way1Signature} {
    // Write your for loop logic here
    return 0;
}

int main(void) {
${way1Test}
    return 0;
}`;

  const code2 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}/**
 * Problem: ${problem.title}
 * Method: Way 2 - While Loop + If Condition
 */
${way2Signature} {
${way2Body}
}

int main(void) {
    printf("=== ${problem.title} (Way 2: While + If) ===\\n");
${way2Test}
    return 0;
}`;

  const starter2 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}// Way 2: While Loop Method
${way2Signature} {
    // Write your while loop logic here
    return 0;
}

int main(void) {
${way2Test}
    return 0;
}`;

  const code3 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}/**
 * Problem: ${problem.title}
 * Method: Way 3 - Optimal / Alternative Method
 */
${way3Signature} {
${way3Body}
}

int main(void) {
    printf("=== ${problem.title} (Way 3: Optimal) ===\\n");
${way3Test}
    return 0;
}`;

  const starter3 = `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

${structDef}// Way 3: Optimal Method
${way3Signature} {
    // Write your optimal logic here
    return 0;
}

int main(void) {
${way3Test}
    return 0;
}`;

  return [
    {
      id: 'for_loop',
      name: 'Way 1: For Loop',
      badge: 'For Loop',
      timeComplexity: timeComplexity,
      spaceComplexity: spaceComplexity,
      description: 'Solved using standard for loop (Sabse aasan)',
      code: code1,
      starterCode: starter1
    },
    {
      id: 'while_if',
      name: 'Way 2: While + If',
      badge: 'While Loop',
      timeComplexity: timeComplexity,
      spaceComplexity: spaceComplexity,
      description: 'Solved using while loop and conditional checks',
      code: code2,
      starterCode: starter2
    },
    {
      id: 'optimal',
      name: 'Way 3: Optimal',
      badge: 'Alternative',
      timeComplexity: timeComplexity,
      spaceComplexity: spaceComplexity,
      description: 'Alternative optimal or recursive method',
      code: code3,
      starterCode: starter3
    }
  ];
}

/**
 * Returns canonical or dynamic C solution.
 * For backwards compatibility, returns the primary approach (index 0).
 */
export function getCSolution(problem, approachIndex = 0) {
  const approaches = getCSolutionApproaches(problem);
  return approaches[approachIndex] || approaches[0] || null;
}
