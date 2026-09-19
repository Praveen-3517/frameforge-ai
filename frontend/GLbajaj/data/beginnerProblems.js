//  Beginner Programming Fundamentals Dataset (64 Curated Problems)
//  Topics: Conditionals (29), Operators (14), Loops (21)
//  Absolute zero-intimidation starting point for students before data structures

export const BEGINNER_PROBLEMS = [
  {
    "id": 1,
    "slug": "check-even-or-odd",
    "title": "Check if a Number is Even or Odd",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, determine whether it is **Even** or **Odd**.\n\nA number is even if it is divisible by 2 with no remainder (`n % 2 == 0`), otherwise it is odd.",
    "examples": [
      {
        "input": "n = 4",
        "output": "\"Even\"",
        "explanation": "4 divided by 2 leaves remainder 0, so it is Even."
      },
      {
        "input": "n = 7",
        "output": "\"Odd\"",
        "explanation": "7 divided by 2 leaves remainder 1, so it is Odd."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹",
      "Time Limit: 1.0s"
    ],
    "starterCode": "def solution(n):\n    # Return \"Even\" if n is even, else \"Odd\"\n    pass\n\n# Test\nprint(solution(4))  # Expected: Even",
    "testCases": [
      {
        "input": "(4,)",
        "expected": "'Even'"
      },
      {
        "input": "(7,)",
        "expected": "'Odd'"
      }
    ],
    "hints": [
      "Use the modulus operator `%` to find remainder when divided by 2.",
      "If `n % 2 == 0`, return 'Even', else return 'Odd'."
    ],
    "approach": "Check if `n % 2 == 0`. If remainder is 0, the number is even; otherwise, it is odd.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkEvenOrOdd(int n) {\n        // Write your solution here\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"4 is: \" + sol.checkEvenOrOdd(4)); // Even\n        System.out.println(\"7 is: \" + sol.checkEvenOrOdd(7)); // Odd\n    }\n}",
    "javaSolution": "class Solution {\n    // Method to check even or odd using modulus operator %\n    public String checkEvenOrOdd(int n) {\n        if (n % 2 == 0) {\n            return \"Even\";\n        } else {\n            return \"Odd\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"4 is: \" + sol.checkEvenOrOdd(4)); // Even\n        System.out.println(\"7 is: \" + sol.checkEvenOrOdd(7)); // Odd\n        System.out.println(\"0 is: \" + sol.checkEvenOrOdd(0)); // Even\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n % 2 == 0:\n        return \"Even\"\n    else:\n        return \"Odd\"\n\n# Test\nprint(solution(4))  # Even\nprint(solution(7))  # Odd",
    "intuitionEn": "Any integer divided by 2 leaves a remainder of either 0 (even) or 1 (odd). The modulus operator `%` directly gives this remainder in constant time.",
    "intuitionHi": "Kisi bhi number ko 2 se divide karne par agar remainder (sheshfal) 0 bachta hai to wo Even hota hai, warna Odd. Modulus `%` operator se ye turant pata chal jata hai.",
    "stepsEn": [
      "Check condition `n % 2 == 0`.",
      "If true, return 'Even'.",
      "Else return 'Odd'."
    ],
    "stepsHi": [
      "Condition check karein: `n % 2 == 0`.",
      "Agar haan, to 'Even' return karein.",
      "Warna 'Odd' return karein."
    ]
  },
  {
    "id": 2,
    "slug": "greatest-of-two-numbers",
    "title": "Find the Greatest of Two Numbers",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given two integers `a` and `b`, find and return the larger (maximum) of the two numbers.",
    "examples": [
      {
        "input": "a = 15, b = 25",
        "output": "25",
        "explanation": "25 is greater than 15."
      },
      {
        "input": "a = -5, b = -10",
        "output": "-5",
        "explanation": "-5 is greater than -10."
      }
    ],
    "constraints": [
      "-10⁹ ≤ a, b ≤ 10⁹",
      "Time Limit: 1.0s"
    ],
    "starterCode": "def solution(a, b):\n    # Return the larger of a and b\n    pass\n\n# Test\nprint(solution(15, 25))  # Expected: 25",
    "testCases": [
      {
        "input": "(15, 25)",
        "expected": "25"
      },
      {
        "input": "(100, 50)",
        "expected": "100"
      }
    ],
    "hints": [
      "Use a simple `if (a > b)` condition.",
      "Return `a` if it's greater, otherwise return `b`."
    ],
    "approach": "Compare `a` and `b` using relational operator `>`. Return `a` if `a > b` else `b`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int greatestOfTwo(int a, int b) {\n        // Write your solution here\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Max of (15, 25): \" + sol.greatestOfTwo(15, 25)); // 25\n    }\n}",
    "javaSolution": "class Solution {\n    // Returns the maximum of two numbers\n    public int greatestOfTwo(int a, int b) {\n        if (a > b) {\n            return a;\n        } else {\n            return b;\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Max of (15, 25): \" + sol.greatestOfTwo(15, 25));   // 25\n        System.out.println(\"Max of (-5, -10): \" + sol.greatestOfTwo(-5, -10)); // -5\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    if a > b:\n        return a\n    else:\n        return b\n\n# Test\nprint(solution(15, 25))  # 25",
    "intuitionEn": "Relational operator `>` compares values directly. If `a` is strictly greater than `b`, `a` is the answer, else `b` is.",
    "intuitionHi": "Do numbers ki tulna karne ke liye `>` operator lagayein. Agar `a > b` sach hai to `a` bada hai, warna `b` bada hai.",
    "stepsEn": [
      "Check `if a > b`.",
      "Return `a` if true.",
      "Otherwise return `b`."
    ],
    "stepsHi": [
      "Check karein `if a > b`.",
      "Agar sach hai to `a` return karein.",
      "Nahi to `b` return karein."
    ]
  },
  {
    "id": 3,
    "slug": "greatest-of-three-numbers",
    "title": "Find the Greatest of Three Numbers",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "nested if",
    "phase": 1,
    "description": "Given three integers `a`, `b`, and `c`, find and return the maximum of the three numbers using conditional statements.",
    "examples": [
      {
        "input": "a = 10, b = 25, c = 18",
        "output": "25",
        "explanation": "25 is larger than both 10 and 18."
      }
    ],
    "constraints": [
      "-10⁹ ≤ a, b, c ≤ 10⁹"
    ],
    "starterCode": "def solution(a, b, c):\n    # Return the largest of three numbers\n    pass\n\n# Test\nprint(solution(10, 25, 18))  # Expected: 25",
    "testCases": [
      {
        "input": "(10, 25, 18)",
        "expected": "25"
      },
      {
        "input": "(30, 20, 10)",
        "expected": "30"
      }
    ],
    "hints": [
      "Use logical AND `&&` to check if `a >= b && a >= c`.",
      "If not, check if `b >= c`."
    ],
    "approach": "If `a >= b` and `a >= c`, then `a` is max. Else if `b >= c`, then `b` is max. Otherwise `c` is max.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int greatestOfThree(int a, int b, int c) {\n        // Write your solution here\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Greatest: \" + sol.greatestOfThree(10, 25, 18)); // 25\n    }\n}",
    "javaSolution": "class Solution {\n    // Finds the maximum among three numbers using if-else if\n    public int greatestOfThree(int a, int b, int c) {\n        if (a >= b && a >= c) {\n            return a;\n        } else if (b >= a && b >= c) {\n            return b;\n        } else {\n            return c;\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Greatest (10, 25, 18): \" + sol.greatestOfThree(10, 25, 18)); // 25\n        System.out.println(\"Greatest (50, 20, 30): \" + sol.greatestOfThree(50, 20, 30)); // 50\n    }\n}",
    "pythonSolution": "def solution(a, b, c):\n    if a >= b and a >= c:\n        return a\n    elif b >= a and b >= c:\n        return b\n    else:\n        return c\n\n# Test\nprint(solution(10, 25, 18))  # 25",
    "intuitionEn": "By checking each candidate against both other numbers using `&&` (logical AND), we identify the maximum in a single pass of conditions.",
    "intuitionHi": "Teen numbers me se bada nikalne ke liye `&&` (AND) operator se check karein ki kya pehla number baaki dono se bada ya barabar hai.",
    "stepsEn": [
      "If `a >= b && a >= c`, return `a`.",
      "Else if `b >= c`, return `b`.",
      "Else return `c`."
    ],
    "stepsHi": [
      "Agar `a >= b` aur `a >= c` dono sach hain, to `a` bada hai.",
      "Warna agar `b >= c` hai, to `b` bada hai.",
      "Anyaatha `c` bada hai."
    ]
  },
  {
    "id": 4,
    "slug": "voting-eligibility-check",
    "title": "Check if a Person is Eligible to Vote (Age >= 18)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given the age of a person as an integer `age`, determine whether the person is eligible to vote. A person is eligible to vote if their age is 18 or older (`age >= 18`).",
    "examples": [
      {
        "input": "age = 20",
        "output": "true",
        "explanation": "20 is >= 18, so eligible."
      },
      {
        "input": "age = 16",
        "output": "false",
        "explanation": "16 is < 18, so not eligible."
      }
    ],
    "constraints": [
      "0 ≤ age ≤ 150"
    ],
    "starterCode": "def solution(age):\n    # Return True if age >= 18, else False\n    pass\n\n# Test\nprint(solution(20))  # Expected: True",
    "testCases": [
      {
        "input": "(20,)",
        "expected": "True"
      },
      {
        "input": "(16,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check if `age >= 18`."
    ],
    "approach": "Return `age >= 18` directly as a boolean result.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isEligibleToVote(int age) {\n        // Write your solution here\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Age 20 eligible? \" + sol.isEligibleToVote(20)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    // Checks voting eligibility\n    public boolean isEligibleToVote(int age) {\n        return age >= 18;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Age 20 eligible? \" + sol.isEligibleToVote(20)); // true\n        System.out.println(\"Age 16 eligible? \" + sol.isEligibleToVote(16)); // false\n        System.out.println(\"Age 18 eligible? \" + sol.isEligibleToVote(18)); // true\n    }\n}",
    "pythonSolution": "def solution(age):\n    return age >= 18\n\n# Test\nprint(solution(20))  # True\nprint(solution(16))  # False",
    "intuitionEn": "A boolean expression `age >= 18` evaluates directly to true or false without needing verbose if-else blocks.",
    "intuitionHi": "Seedha `age >= 18` expression ko evaluate karein. Yeh apne aap true ya false return kar deta hai.",
    "stepsEn": [
      "Evaluate `age >= 18`.",
      "Return the boolean outcome."
    ],
    "stepsHi": [
      "Check karein: `age >= 18`.",
      "Result return karein."
    ]
  },
  {
    "id": 5,
    "slug": "leap-year-checker",
    "title": "Check if a Year is a Leap Year",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a year as an integer `year`, determine whether it is a **Leap Year**.\n\nA year is a leap year if:\n1. It is divisible by 4 AND not divisible by 100, OR\n2. It is divisible by 400.\n\n(`(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)`).",
    "examples": [
      {
        "input": "year = 2024",
        "output": "true",
        "explanation": "2024 is divisible by 4 and not by 100, so it's a leap year."
      },
      {
        "input": "year = 1900",
        "output": "false",
        "explanation": "1900 is divisible by 100 but not by 400, so NOT a leap year."
      }
    ],
    "constraints": [
      "1 ≤ year ≤ 9999"
    ],
    "starterCode": "def solution(year):\n    # Return True if year is leap year, else False\n    pass\n\n# Test\nprint(solution(2024))  # Expected: True",
    "testCases": [
      {
        "input": "(2024,)",
        "expected": "True"
      },
      {
        "input": "(1900,)",
        "expected": "False"
      },
      {
        "input": "(2000,)",
        "expected": "True"
      }
    ],
    "hints": [
      "Leap year rule: (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)."
    ],
    "approach": "Combine century check (`% 400 == 0`) and standard check (`% 4 == 0 && % 100 != 0`).",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isLeapYear(int year) {\n        // Write your solution here\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"2024 is leap? \" + sol.isLeapYear(2024)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    // Leap year rules: divisible by 400 OR (divisible by 4 and not 100)\n    public boolean isLeapYear(int year) {\n        if (year % 400 == 0) {\n            return true;\n        }\n        if (year % 100 == 0) {\n            return false;\n        }\n        return year % 4 == 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"2024: \" + sol.isLeapYear(2024)); // true\n        System.out.println(\"1900: \" + sol.isLeapYear(1900)); // false\n        System.out.println(\"2000: \" + sol.isLeapYear(2000)); // true\n    }\n}",
    "pythonSolution": "def solution(year):\n    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)\n\n# Test\nprint(solution(2024))  # True\nprint(solution(1900))  # False",
    "intuitionEn": "The Gregorian calendar inserts a leap day every 4 years, skips it every 100 years, but re-inserts it every 400 years to align with Earth's orbit.",
    "intuitionHi": "Calendar rule: Agar year 400 se divide hota hai to pakka leap year hai. Warna agar 4 se divide hota hai aur 100 se nahi, tab leap year hai.",
    "stepsEn": [
      "Check `year % 400 == 0` → true.",
      "Check `year % 100 == 0` → false.",
      "Check `year % 4 == 0` → true."
    ],
    "stepsHi": [
      "Check karein agar 400 se divisible hai.",
      "Agar 100 se divisible hai to false.",
      "Agar 4 se divisible hai to true."
    ]
  },
  {
    "id": 6,
    "slug": "vowel-or-consonant",
    "title": "Check if a Character is a Vowel or Consonant",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a single alphabet character `ch`, check whether it is a **Vowel** (`a, e, i, o, u`, case-insensitive) or a **Consonant**.",
    "examples": [
      {
        "input": "ch = 'a'",
        "output": "\"Vowel\"",
        "explanation": "'a' is a vowel."
      },
      {
        "input": "ch = 'z'",
        "output": "\"Consonant\"",
        "explanation": "'z' is a consonant."
      }
    ],
    "constraints": [
      "ch is an English letter (a-z or A-Z)"
    ],
    "starterCode": "def solution(ch):\n    # Return \"Vowel\" or \"Consonant\"\n    pass\n\n# Test\nprint(solution('a'))  # Expected: Vowel",
    "testCases": [
      {
        "input": "('a',)",
        "expected": "'Vowel'"
      },
      {
        "input": "('B',)",
        "expected": "'Consonant'"
      }
    ],
    "hints": [
      "Convert to lowercase first using `Character.toLowerCase(ch)`.",
      "Check if character is in 'a', 'e', 'i', 'o', 'u'."
    ],
    "approach": "Convert character to lowercase. Check if it matches 'a', 'e', 'i', 'o', or 'u'.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkVowelOrConsonant(char ch) {\n        // Write your solution here\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'a' is: \" + sol.checkVowelOrConsonant('a')); // Vowel\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkVowelOrConsonant(char ch) {\n        char lower = Character.toLowerCase(ch);\n        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {\n            return \"Vowel\";\n        } else {\n            return \"Consonant\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'a' is: \" + sol.checkVowelOrConsonant('a')); // Vowel\n        System.out.println(\"'B' is: \" + sol.checkVowelOrConsonant('B')); // Consonant\n        System.out.println(\"'E' is: \" + sol.checkVowelOrConsonant('E')); // Vowel\n    }\n}",
    "pythonSolution": "def solution(ch):\n    if ch.lower() in ['a', 'e', 'i', 'o', 'u']:\n        return \"Vowel\"\n    return \"Consonant\"\n\n# Test\nprint(solution('a'))  # Vowel\nprint(solution('z'))  # Consonant",
    "intuitionEn": "English has 5 vowels: A, E, I, O, U. Any other letter is a consonant.",
    "intuitionHi": "English me sirf 5 vowels hote hain: a, e, i, o, u. Baaki sab consonants kehlate hain.",
    "stepsEn": [
      "Lowercase the character.",
      "Check equality against a, e, i, o, u.",
      "Return accordingly."
    ],
    "stepsHi": [
      "Letter ko lowercase karein.",
      "a, e, i, o, u se compare karein.",
      "Result return karein."
    ]
  },
  {
    "id": 7,
    "slug": "divisible-by-3-and-5",
    "title": "Check if a Number is Divisible by Both 3 and 5",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if `n` is divisible by both 3 and 5 (i.e. divisible by 15), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 15",
        "output": "true",
        "explanation": "15 % 3 == 0 and 15 % 5 == 0."
      },
      {
        "input": "n = 9",
        "output": "false",
        "explanation": "9 is divisible by 3 but not by 5."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if divisible by both 3 and 5\n    pass\n\n# Test\nprint(solution(15))  # Expected: True",
    "testCases": [
      {
        "input": "(15,)",
        "expected": "True"
      },
      {
        "input": "(9,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check both `n % 3 == 0` and `n % 5 == 0` with `&&`."
    ],
    "approach": "Check if `n % 3 == 0 && n % 5 == 0` (or `n % 15 == 0`).",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isDivisibleBy3And5(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"15: \" + sol.isDivisibleBy3And5(15)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isDivisibleBy3And5(int n) {\n        return (n % 3 == 0) && (n % 5 == 0);\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"15: \" + sol.isDivisibleBy3And5(15)); // true\n        System.out.println(\"9:  \" + sol.isDivisibleBy3And5(9));  // false\n        System.out.println(\"30: \" + sol.isDivisibleBy3And5(30)); // true\n    }\n}",
    "pythonSolution": "def solution(n):\n    return n % 3 == 0 and n % 5 == 0\n\n# Test\nprint(solution(15))  # True\nprint(solution(9))   # False",
    "intuitionEn": "Since 3 and 5 are coprime, any number divisible by both is also divisible by 15.",
    "intuitionHi": "Agar koi number 3 aur 5 dono se divide hota hai, to modulus dono me 0 aana chahiye.",
    "stepsEn": [
      "Check `n % 3 == 0`.",
      "Check `n % 5 == 0`.",
      "Combine with AND."
    ],
    "stepsHi": [
      "3 se remainder check karein.",
      "5 se remainder check karein.",
      "Dono 0 hone par true return karein."
    ]
  },
  {
    "id": 8,
    "slug": "grade-calculator",
    "title": "Grade Calculator using if-else (A/B/C/D/F)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given student marks as an integer `marks` (0 to 100), assign a grade:\n- 90 to 100: 'A'\n- 80 to 89: 'B'\n- 70 to 79: 'C'\n- 60 to 69: 'D'\n- Below 60: 'F'",
    "examples": [
      {
        "input": "marks = 85",
        "output": "'B'",
        "explanation": "85 falls in the 80-89 range."
      },
      {
        "input": "marks = 55",
        "output": "'F'",
        "explanation": "55 is below 60."
      }
    ],
    "constraints": [
      "0 ≤ marks ≤ 100"
    ],
    "starterCode": "def solution(marks):\n    # Return grade character 'A', 'B', 'C', 'D', or 'F'\n    pass\n\n# Test\nprint(solution(85))  # Expected: B",
    "testCases": [
      {
        "input": "(85,)",
        "expected": "'B'"
      },
      {
        "input": "(95,)",
        "expected": "'A'"
      }
    ],
    "hints": [
      "Use chained `if - else if` from highest to lowest."
    ],
    "approach": "Compare marks starting from 90 down to 60.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public char calculateGrade(int marks) {\n        return 'F';\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Marks 85: \" + sol.calculateGrade(85)); // B\n    }\n}",
    "javaSolution": "class Solution {\n    public char calculateGrade(int marks) {\n        if (marks >= 90) {\n            return 'A';\n        } else if (marks >= 80) {\n            return 'B';\n        } else if (marks >= 70) {\n            return 'C';\n        } else if (marks >= 60) {\n            return 'D';\n        } else {\n            return 'F';\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Marks 95: \" + sol.calculateGrade(95)); // A\n        System.out.println(\"Marks 85: \" + sol.calculateGrade(85)); // B\n        System.out.println(\"Marks 50: \" + sol.calculateGrade(50)); // F\n    }\n}",
    "pythonSolution": "def solution(marks):\n    if marks >= 90:\n        return 'A'\n    elif marks >= 80:\n        return 'B'\n    elif marks >= 70:\n        return 'C'\n    elif marks >= 60:\n        return 'D'\n    else:\n        return 'F'\n\n# Test\nprint(solution(85))  # B",
    "intuitionEn": "By checking ranges in descending order (`>= 90`, `>= 80`, etc.), each condition implicitly bounds both top and bottom.",
    "intuitionHi": "Bade number se shuru karke `else if` lagane se beech ka range apne aap manage ho jata hai.",
    "stepsEn": [
      "Check `>= 90` -> 'A'",
      "Else if `>= 80` -> 'B'",
      "Else if `>= 70` -> 'C'",
      "Else if `>= 60` -> 'D'",
      "Else -> 'F'"
    ],
    "stepsHi": [
      "Marks >= 90 par 'A'",
      "Marks >= 80 par 'B'",
      "Marks >= 70 par 'C'",
      "Marks >= 60 par 'D'",
      "Anyaatha 'F'"
    ]
  },
  {
    "id": 9,
    "slug": "valid-triangle-by-angles",
    "title": "Check if a Triangle is Valid Given Three Angles",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given three angles of a triangle `a`, `b`, and `c`, determine if they form a valid triangle.\n\nA triangle is valid if all angles are positive (`> 0`) AND their sum equals 180 degrees (`a + b + c == 180`).",
    "examples": [
      {
        "input": "a = 60, b = 60, c = 60",
        "output": "true",
        "explanation": "Sum is 180 and all angles are positive."
      },
      {
        "input": "a = 90, b = 90, c = 10",
        "output": "false",
        "explanation": "Sum is 190, so invalid."
      }
    ],
    "constraints": [
      "0 ≤ a, b, c ≤ 360"
    ],
    "starterCode": "def solution(a, b, c):\n    # Return True if a + b + c == 180 and all > 0\n    pass\n\n# Test\nprint(solution(60, 60, 60))  # Expected: True",
    "testCases": [
      {
        "input": "(60, 60, 60)",
        "expected": "True"
      },
      {
        "input": "(90, 90, 10)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check `a > 0 && b > 0 && c > 0` and `a + b + c == 180`."
    ],
    "approach": "Validate that each angle > 0 and their sum is strictly 180.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isValidTriangle(int a, int b, int c) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"60, 60, 60: \" + sol.isValidTriangle(60, 60, 60)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isValidTriangle(int a, int b, int c) {\n        return (a > 0 && b > 0 && c > 0) && (a + b + c == 180);\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"60, 60, 60: \" + sol.isValidTriangle(60, 60, 60)); // true\n        System.out.println(\"90, 90, 10: \" + sol.isValidTriangle(90, 90, 10)); // false\n    }\n}",
    "pythonSolution": "def solution(a, b, c):\n    return (a > 0 and b > 0 and c > 0) and (a + b + c == 180)\n\n# Test\nprint(solution(60, 60, 60))  # True",
    "intuitionEn": "By geometry rules, the sum of internal angles of a triangle in Euclidean plane is always 180 degrees, and each angle must be positive.",
    "intuitionHi": "Geometry ka niyam hai ki triangle ke teeno angles ka jod hamesha 180 hona chahiye aur koi angle 0 ya negative nahi hona chahiye.",
    "stepsEn": [
      "Check angles positive.",
      "Check sum equals 180."
    ],
    "stepsHi": [
      "Sabhi angles > 0 check karein.",
      "Sum 180 ke barabar check karein."
    ]
  },
  {
    "id": 10,
    "slug": "simple-calculator-switch",
    "title": "Simple Calculator using switch-case (+, -, *, /)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "switch-case",
    "phase": 1,
    "description": "Given two integers `a` and `b`, and a character `op` representing an operator (`'+'`, `'-'`, `'*'`, `'/'`), perform the corresponding arithmetic operation using a switch-case statement.\n\nFor division, assume integer division (`a / b`) and `b != 0`.",
    "examples": [
      {
        "input": "a = 10, b = 5, op = '+'",
        "output": "15",
        "explanation": "10 + 5 = 15."
      },
      {
        "input": "a = 10, b = 2, op = '/'",
        "output": "5",
        "explanation": "10 / 2 = 5."
      }
    ],
    "constraints": [
      "-10⁴ ≤ a, b ≤ 10⁴",
      "b != 0 when op is '/'"
    ],
    "starterCode": "def solution(a, b, op):\n    # Return result of operation\n    pass\n\n# Test\nprint(solution(10, 5, '+'))  # Expected: 15",
    "testCases": [
      {
        "input": "(10, 5, '+')",
        "expected": "15"
      },
      {
        "input": "(10, 2, '/')",
        "expected": "5"
      }
    ],
    "hints": [
      "Use switch(op) with cases for '+', '-', '*', '/'."
    ],
    "approach": "Use a switch statement matching `op` and return the arithmetic result.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int calculate(int a, int b, char op) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"10 + 5 = \" + sol.calculate(10, 5, '+')); // 15\n    }\n}",
    "javaSolution": "class Solution {\n    // Calculator implementation using switch-case\n    public int calculate(int a, int b, char op) {\n        switch (op) {\n            case '+':\n                return a + b;\n            case '-':\n                return a - b;\n            case '*':\n                return a * b;\n            case '/':\n                return a / b;\n            default:\n                return 0;\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"10 + 5 = \" + sol.calculate(10, 5, '+')); // 15\n        System.out.println(\"10 - 3 = \" + sol.calculate(10, 3, '-')); // 7\n        System.out.println(\"6 * 7  = \" + sol.calculate(6, 7, '*'));  // 42\n        System.out.println(\"20 / 4 = \" + sol.calculate(20, 4, '/')); // 5\n    }\n}",
    "pythonSolution": "def solution(a, b, op):\n    if op == '+':\n        return a + b\n    elif op == '-':\n        return a - b\n    elif op == '*':\n        return a * b\n    elif op == '/':\n        return a // b\n    return 0\n\n# Test\nprint(solution(10, 5, '+'))  # 15",
    "intuitionEn": "Switch statements match exact discrete values cleanly with jump-table efficiency.",
    "intuitionHi": "Switch statement operator ke character ko match karta hai aur sahi calculation return karta hai.",
    "stepsEn": [
      "Switch on `op`.",
      "For `+` return `a + b`.",
      "For `-` return `a - b`.",
      "For `*` return `a * b`.",
      "For `/` return `a / b`."
    ],
    "stepsHi": [
      "Operator `op` par switch lagayein.",
      "Har case me sahi calculation return karein."
    ]
  },
  {
    "id": 11,
    "slug": "single-or-multi-digit",
    "title": "Check if a Number is Single-Digit or Multi-Digit",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, return `\"Single Digit\"` if it consists of a single digit (from -9 to 9), otherwise return `\"Multi Digit\"`.",
    "examples": [
      {
        "input": "n = 7",
        "output": "\"Single Digit\"",
        "explanation": "7 is between -9 and 9."
      },
      {
        "input": "n = 42",
        "output": "\"Multi Digit\"",
        "explanation": "42 has two digits."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return \"Single Digit\" or \"Multi Digit\"\n    pass\n\n# Test\nprint(solution(7))  # Expected: Single Digit",
    "testCases": [
      {
        "input": "(7,)",
        "expected": "'Single Digit'"
      },
      {
        "input": "(42,)",
        "expected": "'Multi Digit'"
      }
    ],
    "hints": [
      "Check if `n >= -9 && n <= 9`."
    ],
    "approach": "Check if the absolute value `Math.abs(n) <= 9` or `-9 <= n <= 9`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkDigits(int n) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"7: \" + sol.checkDigits(7)); // Single Digit\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkDigits(int n) {\n        if (n >= -9 && n <= 9) {\n            return \"Single Digit\";\n        } else {\n            return \"Multi Digit\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"7  : \" + sol.checkDigits(7));  // Single Digit\n        System.out.println(\"42 : \" + sol.checkDigits(42)); // Multi Digit\n        System.out.println(\"-5 : \" + sol.checkDigits(-5)); // Single Digit\n    }\n}",
    "pythonSolution": "def solution(n):\n    return \"Single Digit\" if -9 <= n <= 9 else \"Multi Digit\"\n\n# Test\nprint(solution(7))   # Single Digit\nprint(solution(42))  # Multi Digit",
    "intuitionEn": "Numbers from -9 to 9 have only 1 digit. Beyond this range they have 2 or more digits.",
    "intuitionHi": "-9 se 9 ke beech ke saare numbers single digit hote hain. Baaki sab multi digit hote hain.",
    "stepsEn": [
      "Check `n >= -9 && n <= 9`.",
      "Return 'Single Digit' if true, else 'Multi Digit'."
    ],
    "stepsHi": [
      "Check karein `-9 <= n <= 9`.",
      "Sahi label return karein."
    ]
  },
  {
    "id": 12,
    "slug": "smallest-of-three-numbers",
    "title": "Find the Smallest of Three Numbers",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given three integers `a`, `b`, and `c`, find and return the minimum (smallest) of the three numbers.",
    "examples": [
      {
        "input": "a = 20, b = 5, c = 12",
        "output": "5",
        "explanation": "5 is smaller than both 20 and 12."
      }
    ],
    "constraints": [
      "-10⁹ ≤ a, b, c ≤ 10⁹"
    ],
    "starterCode": "def solution(a, b, c):\n    # Return smallest of three\n    pass\n\n# Test\nprint(solution(20, 5, 12))  # Expected: 5",
    "testCases": [
      {
        "input": "(20, 5, 12)",
        "expected": "5"
      },
      {
        "input": "(1, 2, 3)",
        "expected": "1"
      }
    ],
    "hints": [
      "Use `if (a <= b && a <= c)`."
    ],
    "approach": "Compare with logical AND to find the minimum.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int smallestOfThree(int a, int b, int c) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.smallestOfThree(20, 5, 12)); // 5\n    }\n}",
    "javaSolution": "class Solution {\n    public int smallestOfThree(int a, int b, int c) {\n        if (a <= b && a <= c) {\n            return a;\n        } else if (b <= a && b <= c) {\n            return b;\n        } else {\n            return c;\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Smallest (20, 5, 12): \" + sol.smallestOfThree(20, 5, 12)); // 5\n    }\n}",
    "pythonSolution": "def solution(a, b, c):\n    if a <= b and a <= c:\n        return a\n    elif b <= a and b <= c:\n        return b\n    else:\n        return c\n\n# Test\nprint(solution(20, 5, 12))  # 5",
    "intuitionEn": "Similar to finding maximum, we check whether `a` is smaller than both `b` and `c`.",
    "intuitionHi": "Sabse chhota number nikalne ke liye dekhein ki kya `a` baaki dono se chhota hai.",
    "stepsEn": [
      "Compare `a` with `b` and `c`.",
      "Return smallest."
    ],
    "stepsHi": [
      "Sabhi pairs ko compare karein.",
      "Sabse chhota return karein."
    ]
  },
  {
    "id": 13,
    "slug": "check-uppercase-or-lowercase",
    "title": "Check if a Character is Uppercase or Lowercase",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a character `ch`, return `\"Uppercase\"` if it is an uppercase letter ('A'-'Z'), `\"Lowercase\"` if lowercase ('a'-'z'), and `\"Not a Letter\"` otherwise.",
    "examples": [
      {
        "input": "ch = 'G'",
        "output": "\"Uppercase\"",
        "explanation": "'G' is between 'A' and 'Z'."
      },
      {
        "input": "ch = 'm'",
        "output": "\"Lowercase\"",
        "explanation": "'m' is between 'a' and 'z'."
      }
    ],
    "constraints": [
      "ch is any valid ASCII character"
    ],
    "starterCode": "def solution(ch):\n    # Return \"Uppercase\", \"Lowercase\", or \"Not a Letter\"\n    pass\n\n# Test\nprint(solution('G'))  # Expected: Uppercase",
    "testCases": [
      {
        "input": "('G',)",
        "expected": "'Uppercase'"
      },
      {
        "input": "('m',)",
        "expected": "'Lowercase'"
      }
    ],
    "hints": [
      "Check `ch >= 'A' && ch <= 'Z'`, and `ch >= 'a' && ch <= 'z'`."
    ],
    "approach": "Check ASCII ranges: uppercase 65-90, lowercase 97-122.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkCase(char ch) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'G': \" + sol.checkCase('G')); // Uppercase\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkCase(char ch) {\n        if (ch >= 'A' && ch <= 'Z') {\n            return \"Uppercase\";\n        } else if (ch >= 'a' && ch <= 'z') {\n            return \"Lowercase\";\n        } else {\n            return \"Not a Letter\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'G': \" + sol.checkCase('G')); // Uppercase\n        System.out.println(\"'m': \" + sol.checkCase('m')); // Lowercase\n        System.out.println(\"'#': \" + sol.checkCase('#')); // Not a Letter\n    }\n}",
    "pythonSolution": "def solution(ch):\n    if 'A' <= ch <= 'Z':\n        return \"Uppercase\"\n    elif 'a' <= ch <= 'z':\n        return \"Lowercase\"\n    else:\n        return \"Not a Letter\"\n\n# Test\nprint(solution('G'))  # Uppercase\nprint(solution('m'))  # Lowercase",
    "intuitionEn": "Characters in programming languages are stored as ASCII numbers, so range comparison `'A' <= ch <= 'Z'` works directly.",
    "intuitionHi": "Programming me characters ASCII values hote hain. Isliye `'A' <= ch <= 'Z'` seedha range match karta hai.",
    "stepsEn": [
      "Check uppercase range.",
      "Check lowercase range.",
      "Otherwise not a letter."
    ],
    "stepsHi": [
      "Uppercase check karein.",
      "Lowercase check karein.",
      "Warna Not a letter return karein."
    ]
  },
  {
    "id": 14,
    "slug": "multiple-of-10",
    "title": "Check if a Number is a Multiple of 10",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if `n` is a multiple of 10 (its last digit is 0, i.e. `n % 10 == 0`), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 50",
        "output": "true",
        "explanation": "50 is 10 * 5."
      },
      {
        "input": "n = 37",
        "output": "false",
        "explanation": "37 does not end in 0."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if n % 10 == 0, else False\n    pass\n\n# Test\nprint(solution(50))  # Expected: True",
    "testCases": [
      {
        "input": "(50,)",
        "expected": "True"
      },
      {
        "input": "(37,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check if `n % 10 == 0`."
    ],
    "approach": "Return `n % 10 == 0`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isMultipleOf10(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"50: \" + sol.isMultipleOf10(50)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isMultipleOf10(int n) {\n        return n % 10 == 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"50: \" + sol.isMultipleOf10(50)); // true\n        System.out.println(\"37: \" + sol.isMultipleOf10(37)); // false\n    }\n}",
    "pythonSolution": "def solution(n):\n    return n % 10 == 0\n\n# Test\nprint(solution(50))  # True\nprint(solution(37))  # False",
    "intuitionEn": "Multiples of 10 always end with digit 0. Taking modulo 10 gives the last digit.",
    "intuitionHi": "10 ke har multiple ka aakhiri digit 0 hota hai. Modulo 10 se ye check ho jata hai.",
    "stepsEn": [
      "Calculate `n % 10`.",
      "Compare with 0."
    ],
    "stepsHi": [
      "`n % 10 == 0` check karein."
    ]
  },
  {
    "id": 15,
    "slug": "day-of-week-switch",
    "title": "Determine the Day of the Week using switch-case (1-7)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "switch-case",
    "phase": 1,
    "description": "Given an integer `day` (1 to 7), return the name of the corresponding day of the week using a switch-case statement:\n1: \"Monday\", 2: \"Tuesday\", 3: \"Wednesday\", 4: \"Thursday\", 5: \"Friday\", 6: \"Saturday\", 7: \"Sunday\".\nFor any other number, return `\"Invalid Day\"`.",
    "examples": [
      {
        "input": "day = 1",
        "output": "\"Monday\"",
        "explanation": "1 corresponds to Monday."
      },
      {
        "input": "day = 5",
        "output": "\"Friday\"",
        "explanation": "5 corresponds to Friday."
      }
    ],
    "constraints": [
      "day is an integer"
    ],
    "starterCode": "def solution(day):\n    # Return day name\n    pass\n\n# Test\nprint(solution(1))  # Expected: Monday",
    "testCases": [
      {
        "input": "(1,)",
        "expected": "'Monday'"
      },
      {
        "input": "(5,)",
        "expected": "'Friday'"
      }
    ],
    "hints": [
      "Use `switch (day)` with cases 1 to 7."
    ],
    "approach": "Map integers 1-7 to day names using switch.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String getDayOfWeek(int day) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Day 1: \" + sol.getDayOfWeek(1)); // Monday\n    }\n}",
    "javaSolution": "class Solution {\n    public String getDayOfWeek(int day) {\n        switch (day) {\n            case 1: return \"Monday\";\n            case 2: return \"Tuesday\";\n            case 3: return \"Wednesday\";\n            case 4: return \"Thursday\";\n            case 5: return \"Friday\";\n            case 6: return \"Saturday\";\n            case 7: return \"Sunday\";\n            default: return \"Invalid Day\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Day 1: \" + sol.getDayOfWeek(1)); // Monday\n        System.out.println(\"Day 5: \" + sol.getDayOfWeek(5)); // Friday\n    }\n}",
    "pythonSolution": "def solution(day):\n    days = {1: \"Monday\", 2: \"Tuesday\", 3: \"Wednesday\", 4: \"Thursday\", 5: \"Friday\", 6: \"Saturday\", 7: \"Sunday\"}\n    return days.get(day, \"Invalid Day\")\n\n# Test\nprint(solution(1))  # Monday\nprint(solution(5))  # Friday",
    "intuitionEn": "A switch-case statement maps integer codes to human-readable strings directly.",
    "intuitionHi": "Switch case se har number (1 se 7) ko din ke naam me map kar diya jata hai.",
    "stepsEn": [
      "Switch on day.",
      "Return corresponding string."
    ],
    "stepsHi": [
      "Day par switch chalayein.",
      "Sahi din return karein."
    ]
  },
  {
    "id": 16,
    "slug": "empty-string-check",
    "title": "Check if a String is Empty or Not",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a string `s`, return `true` if it is empty (length is 0), otherwise return `false`.",
    "examples": [
      {
        "input": "s = \"\"",
        "output": "true",
        "explanation": "Length of empty string is 0."
      },
      {
        "input": "s = \"Hello\"",
        "output": "false",
        "explanation": "String has characters."
      }
    ],
    "constraints": [
      "s is a string"
    ],
    "starterCode": "def solution(s):\n    # Return True if s is empty, else False\n    pass\n\n# Test\nprint(solution(\"\"))  # Expected: True",
    "testCases": [
      {
        "input": "('',)",
        "expected": "True"
      },
      {
        "input": "('Hello',)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check `s.length() == 0` or `s.isEmpty()` in Java, `len(s) == 0` in Python."
    ],
    "approach": "Check if string length is 0.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isEmptyString(String s) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isEmptyString(\"\")); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isEmptyString(String s) {\n        return s == null || s.isEmpty();\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Empty string: \" + sol.isEmptyString(\"\"));      // true\n        System.out.println(\"'Hello': \" + sol.isEmptyString(\"Hello\"));     // false\n    }\n}",
    "pythonSolution": "def solution(s):\n    return len(s) == 0\n\n# Test\nprint(solution(\"\"))       # True\nprint(solution(\"Hello\"))  # False",
    "intuitionEn": "An empty string has zero characters. Checking `length == 0` handles this immediately.",
    "intuitionHi": "Khali string ki lambai hamesha 0 hoti hai.",
    "stepsEn": [
      "Check `s.length() == 0`."
    ],
    "stepsHi": [
      "String length check karein."
    ]
  },
  {
    "id": 17,
    "slug": "vowel-checker-switch",
    "title": "Check if an Alphabet is a Vowel using switch-case",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "switch-case",
    "phase": 1,
    "description": "Given a character `ch`, use a **switch-case** statement to return `true` if it is a vowel (`'a'`, `'e'`, `'i'`, `'o'`, `'u'`, case-insensitive), else return `false`.",
    "examples": [
      {
        "input": "ch = 'e'",
        "output": "true",
        "explanation": "'e' is a vowel."
      },
      {
        "input": "ch = 'k'",
        "output": "false",
        "explanation": "'k' is a consonant."
      }
    ],
    "constraints": [
      "ch is an English letter"
    ],
    "starterCode": "def solution(ch):\n    # Return True if vowel else False\n    pass\n\n# Test\nprint(solution('e'))  # Expected: True",
    "testCases": [
      {
        "input": "('e',)",
        "expected": "True"
      },
      {
        "input": "('k',)",
        "expected": "False"
      }
    ],
    "hints": [
      "Use multiple cases falling through: `case 'a': case 'e': ... return true;`."
    ],
    "approach": "Group vowel cases in switch statement.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isVowel(char ch) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'e': \" + sol.isVowel('e')); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isVowel(char ch) {\n        switch (Character.toLowerCase(ch)) {\n            case 'a':\n            case 'e':\n            case 'i':\n            case 'o':\n            case 'u':\n                return true;\n            default:\n                return false;\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'e': \" + sol.isVowel('e')); // true\n        System.out.println(\"'k': \" + sol.isVowel('k')); // false\n    }\n}",
    "pythonSolution": "def solution(ch):\n    return ch.lower() in {'a', 'e', 'i', 'o', 'u'}\n\n# Test\nprint(solution('e'))  # True",
    "intuitionEn": "Switch-case allows fall-through, letting all 5 vowel letters share a single `return true` statement.",
    "intuitionHi": "Switch case me multiple cases ko ek saath jod kar ek hi return diya ja sakta hai.",
    "stepsEn": [
      "Lowercase character.",
      "Match cases 'a', 'e', 'i', 'o', 'u'.",
      "Return true on match."
    ],
    "stepsHi": [
      "Character lowercase karein.",
      "Vowel cases par true return karein."
    ]
  },
  {
    "id": 18,
    "slug": "between-1-and-100",
    "title": "Check if a Number Lies Between 1 and 100",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if `n` is inclusive between 1 and 100 (`1 <= n <= 100`), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 50",
        "output": "true",
        "explanation": "50 is between 1 and 100."
      },
      {
        "input": "n = 150",
        "output": "false",
        "explanation": "150 is greater than 100."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if 1 <= n <= 100\n    pass\n\n# Test\nprint(solution(50))  # Expected: True",
    "testCases": [
      {
        "input": "(50,)",
        "expected": "True"
      },
      {
        "input": "(150,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Use `n >= 1 && n <= 100`."
    ],
    "approach": "Range check using relational and logical AND operators.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isBetween1And100(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"50: \" + sol.isBetween1And100(50)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isBetween1And100(int n) {\n        return n >= 1 && n <= 100;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"50 : \" + sol.isBetween1And100(50));  // true\n        System.out.println(\"150: \" + sol.isBetween1And100(150)); // false\n        System.out.println(\"0  : \" + sol.isBetween1And100(0));   // false\n    }\n}",
    "pythonSolution": "def solution(n):\n    return 1 <= n <= 100\n\n# Test\nprint(solution(50))   # True\nprint(solution(150))  # False",
    "intuitionEn": "Check both lower bound (`>= 1`) and upper bound (`<= 100`) simultaneously with `&&`.",
    "intuitionHi": "Dono boundaries check karein: `n >= 1` aur `n <= 100`.",
    "stepsEn": [
      "Check `n >= 1 && n <= 100`.",
      "Return boolean."
    ],
    "stepsHi": [
      "Range evaluate karein."
    ]
  },
  {
    "id": 19,
    "slug": "pass-or-fail",
    "title": "Check if a Student Passed or Failed (Marks >= 40)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given student marks as an integer `marks`, return `\"Pass\"` if `marks >= 40`, otherwise return `\"Fail\"`.",
    "examples": [
      {
        "input": "marks = 65",
        "output": "\"Pass\"",
        "explanation": "65 >= 40."
      },
      {
        "input": "marks = 32",
        "output": "\"Fail\"",
        "explanation": "32 < 40."
      }
    ],
    "constraints": [
      "0 ≤ marks ≤ 100"
    ],
    "starterCode": "def solution(marks):\n    # Return \"Pass\" if marks >= 40 else \"Fail\"\n    pass\n\n# Test\nprint(solution(65))  # Expected: Pass",
    "testCases": [
      {
        "input": "(65,)",
        "expected": "'Pass'"
      },
      {
        "input": "(32,)",
        "expected": "'Fail'"
      }
    ],
    "hints": [
      "Check if `marks >= 40`."
    ],
    "approach": "Single if-else branch on threshold 40.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkResult(int marks) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.checkResult(65)); // Pass\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkResult(int marks) {\n        if (marks >= 40) {\n            return \"Pass\";\n        } else {\n            return \"Fail\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Marks 65: \" + sol.checkResult(65)); // Pass\n        System.out.println(\"Marks 32: \" + sol.checkResult(32)); // Fail\n    }\n}",
    "pythonSolution": "def solution(marks):\n    return \"Pass\" if marks >= 40 else \"Fail\"\n\n# Test\nprint(solution(65))  # Pass\nprint(solution(32))  # Fail",
    "intuitionEn": "Standard benchmark threshold check.",
    "intuitionHi": "Pass mark 40 hai. Agar marks >= 40 hai to Pass, warna Fail.",
    "stepsEn": [
      "Check `marks >= 40`.",
      "Return Pass/Fail."
    ],
    "stepsHi": [
      "Marks >= 40 check karein."
    ]
  },
  {
    "id": 20,
    "slug": "bmi-category-checker",
    "title": "BMI Category Checker (Underweight/Normal/Overweight)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a Body Mass Index (BMI) value as a floating point number `bmi`, return the health category:\n- `bmi < 18.5`: `\"Underweight\"`\n- `18.5 <= bmi < 25.0`: `\"Normal\"`\n- `25.0 <= bmi < 30.0`: `\"Overweight\"`\n- `bmi >= 30.0`: `\"Obese\"`",
    "examples": [
      {
        "input": "bmi = 22.5",
        "output": "\"Normal\"",
        "explanation": "22.5 is between 18.5 and 25.0."
      },
      {
        "input": "bmi = 28.0",
        "output": "\"Overweight\"",
        "explanation": "28.0 is between 25.0 and 30.0."
      }
    ],
    "constraints": [
      "0.0 ≤ bmi ≤ 100.0"
    ],
    "starterCode": "def solution(bmi):\n    # Return category\n    pass\n\n# Test\nprint(solution(22.5))  # Expected: Normal",
    "testCases": [
      {
        "input": "(22.5,)",
        "expected": "'Normal'"
      },
      {
        "input": "(28.0,)",
        "expected": "'Overweight'"
      }
    ],
    "hints": [
      "Use chained `if - else if` from smallest threshold up."
    ],
    "approach": "Check thresholds ascending: `< 18.5`, `< 25.0`, `< 30.0`, else Obese.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String getBmiCategory(double bmi) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"BMI 22.5: \" + sol.getBmiCategory(22.5)); // Normal\n    }\n}",
    "javaSolution": "class Solution {\n    public String getBmiCategory(double bmi) {\n        if (bmi < 18.5) {\n            return \"Underweight\";\n        } else if (bmi < 25.0) {\n            return \"Normal\";\n        } else if (bmi < 30.0) {\n            return \"Overweight\";\n        } else {\n            return \"Obese\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"BMI 22.5: \" + sol.getBmiCategory(22.5)); // Normal\n        System.out.println(\"BMI 28.0: \" + sol.getBmiCategory(28.0)); // Overweight\n        System.out.println(\"BMI 16.0: \" + sol.getBmiCategory(16.0)); // Underweight\n    }\n}",
    "pythonSolution": "def solution(bmi):\n    if bmi < 18.5:\n        return \"Underweight\"\n    elif bmi < 25.0:\n        return \"Normal\"\n    elif bmi < 30.0:\n        return \"Overweight\"\n    else:\n        return \"Obese\"\n\n# Test\nprint(solution(22.5))  # Normal",
    "intuitionEn": "Sequential interval checks categorize continuous values into clinical bands.",
    "intuitionHi": "BMI intervals ko `else if` se check karke sahi health status categorize karein.",
    "stepsEn": [
      "Check < 18.5",
      "Check < 25.0",
      "Check < 30.0",
      "Default Obese"
    ],
    "stepsHi": [
      "Thresholds ascending order me match karein."
    ]
  },
  {
    "id": 21,
    "slug": "electricity-bill-calculator",
    "title": "Check Electricity Bill Slab based on Units Consumed",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given electricity units consumed as an integer `units`, calculate the total bill amount according to slabs:\n- First 100 units: ₹1.5 per unit\n- Next 100 units (101-200): ₹2.5 per unit\n- Above 200 units: ₹4.0 per unit",
    "examples": [
      {
        "input": "units = 150",
        "output": "275.0",
        "explanation": "100*1.5 + 50*2.5 = 150 + 125 = 275.0"
      }
    ],
    "constraints": [
      "0 ≤ units ≤ 10000"
    ],
    "starterCode": "def solution(units):\n    # Return total bill amount\n    pass\n\n# Test\nprint(solution(150))  # Expected: 275.0",
    "testCases": [
      {
        "input": "(150,)",
        "expected": "275.0"
      },
      {
        "input": "(50,)",
        "expected": "75.0"
      }
    ],
    "hints": [
      "Compute slab by slab: first 100, then up to 200, then remaining."
    ],
    "approach": "Calculate cumulative charges across tiers.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public double calculateBill(int units) {\n        return 0.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Bill for 150 units: \" + sol.calculateBill(150)); // 275.0\n    }\n}",
    "javaSolution": "class Solution {\n    public double calculateBill(int units) {\n        double bill = 0;\n        if (units <= 100) {\n            bill = units * 1.5;\n        } else if (units <= 200) {\n            bill = (100 * 1.5) + ((units - 100) * 2.5);\n        } else {\n            bill = (100 * 1.5) + (100 * 2.5) + ((units - 200) * 4.0);\n        }\n        return bill;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"150 units: ₹\" + sol.calculateBill(150)); // 275.0\n        System.out.println(\"50 units:  ₹\" + sol.calculateBill(50));  // 75.0\n    }\n}",
    "pythonSolution": "def solution(units):\n    if units <= 100:\n        return units * 1.5\n    elif units <= 200:\n        return (100 * 1.5) + ((units - 100) * 2.5)\n    else:\n        return (100 * 1.5) + (100 * 2.5) + ((units - 200) * 4.0)\n\n# Test\nprint(solution(150))  # 275.0",
    "intuitionEn": "Electricity bills use progressive taxation/tier billing where units within each bracket are taxed at that bracket's specific rate.",
    "intuitionHi": "Bijli ka bill slabs me calculate hota hai. Pehle 100 units ka rate alag hota hai, agle 100 ka alag.",
    "stepsEn": [
      "If <= 100, multiply by 1.5.",
      "If <= 200, add 150 + extra * 2.5.",
      "Else add 400 + extra * 4.0."
    ],
    "stepsHi": [
      "Units ke brackets me todkar multiply karein."
    ]
  },
  {
    "id": 22,
    "slug": "positive-and-even",
    "title": "Check if a Number is Positive and Even Simultaneously",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if `n` is both strictly greater than zero (`n > 0`) AND even (`n % 2 == 0`), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 6",
        "output": "true",
        "explanation": "6 > 0 and 6 % 2 == 0."
      },
      {
        "input": "n = -4",
        "output": "false",
        "explanation": "-4 is even but NOT positive."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if positive and even\n    pass\n\n# Test\nprint(solution(6))  # Expected: True",
    "testCases": [
      {
        "input": "(6,)",
        "expected": "True"
      },
      {
        "input": "(-4,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Use `n > 0 && n % 2 == 0`."
    ],
    "approach": "Combine positive check and modulus check with logical AND.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isPositiveAndEven(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"6: \" + sol.isPositiveAndEven(6)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isPositiveAndEven(int n) {\n        return n > 0 && n % 2 == 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"6 : \" + sol.isPositiveAndEven(6));  // true\n        System.out.println(\"-4: \" + sol.isPositiveAndEven(-4)); // false\n        System.out.println(\"7 : \" + sol.isPositiveAndEven(7));  // false\n    }\n}",
    "pythonSolution": "def solution(n):\n    return n > 0 and n % 2 == 0\n\n# Test\nprint(solution(6))   # True\nprint(solution(-4))  # False",
    "intuitionEn": "Both criteria must hold at the same time, modeled via logical AND `&&`.",
    "intuitionHi": "Dono conditions ek sath sach honi chahiye: `n > 0` aur `n % 2 == 0`.",
    "stepsEn": [
      "Check `n > 0`.",
      "Check `n % 2 == 0`.",
      "Return conjunction."
    ],
    "stepsHi": [
      "AND operator se dono conditions check karein."
    ]
  },
  {
    "id": 23,
    "slug": "traffic-light-action",
    "title": "Traffic Light Action using switch-case",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "switch-case",
    "phase": 1,
    "description": "Given a traffic light color as a string `color` (`\"Red\"`, `\"Yellow\"`, `\"Green\"`, case-insensitive), return the required driving action:\n- `\"Red\"` -> `\"Stop\"`\n- `\"Yellow\"` -> `\"Wait\"`\n- `\"Green\"` -> `\"Go\"`\n- Any other -> `\"Invalid Color\"`",
    "examples": [
      {
        "input": "color = \"Red\"",
        "output": "\"Stop\"",
        "explanation": "Red means Stop."
      },
      {
        "input": "color = \"Green\"",
        "output": "\"Go\"",
        "explanation": "Green means Go."
      }
    ],
    "constraints": [
      "color is a string"
    ],
    "starterCode": "def solution(color):\n    # Return action for traffic light color\n    pass\n\n# Test\nprint(solution(\"Red\"))  # Expected: Stop",
    "testCases": [
      {
        "input": "('Red',)",
        "expected": "'Stop'"
      },
      {
        "input": "('Green',)",
        "expected": "'Go'"
      }
    ],
    "hints": [
      "Use switch statement matching color in lowercase."
    ],
    "approach": "Match light color with action string.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String getAction(String color) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Red: \" + sol.getAction(\"Red\")); // Stop\n    }\n}",
    "javaSolution": "class Solution {\n    public String getAction(String color) {\n        if (color == null) return \"Invalid Color\";\n        switch (color.toLowerCase()) {\n            case \"red\":\n                return \"Stop\";\n            case \"yellow\":\n                return \"Wait\";\n            case \"green\":\n                return \"Go\";\n            default:\n                return \"Invalid Color\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Red:    \" + sol.getAction(\"Red\"));    // Stop\n        System.out.println(\"Yellow: \" + sol.getAction(\"Yellow\")); // Wait\n        System.out.println(\"Green:  \" + sol.getAction(\"Green\"));  // Go\n    }\n}",
    "pythonSolution": "def solution(color):\n    actions = {\"red\": \"Stop\", \"yellow\": \"Wait\", \"green\": \"Go\"}\n    return actions.get(color.lower(), \"Invalid Color\")\n\n# Test\nprint(solution(\"Red\"))    # Stop\nprint(solution(\"Green\"))  # Go",
    "intuitionEn": "Traffic signals map discrete color states directly to traffic regulations.",
    "intuitionHi": "Traffic light ke rang ko action (Stop, Wait, Go) me switch case se match karein.",
    "stepsEn": [
      "Normalize to lowercase.",
      "Switch cases.",
      "Return instruction."
    ],
    "stepsHi": [
      "Color ko lowercase karke switch case se match karein."
    ]
  },
  {
    "id": 24,
    "slug": "classify-character",
    "title": "Check if Input is a Digit, Letter, or Special Character",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a single character `ch`, return:\n- `\"Digit\"` if it is a number ('0'-'9')\n- `\"Letter\"` if it is an alphabet letter ('A'-'Z' or 'a'-'z')\n- `\"Special\"` otherwise.",
    "examples": [
      {
        "input": "ch = '7'",
        "output": "\"Digit\"",
        "explanation": "'7' is a number."
      },
      {
        "input": "ch = '@'",
        "output": "\"Special\"",
        "explanation": "'@' is a special symbol."
      }
    ],
    "constraints": [
      "ch is an ASCII character"
    ],
    "starterCode": "def solution(ch):\n    # Return \"Digit\", \"Letter\", or \"Special\"\n    pass\n\n# Test\nprint(solution('7'))  # Expected: Digit",
    "testCases": [
      {
        "input": "('7',)",
        "expected": "'Digit'"
      },
      {
        "input": "('@',)",
        "expected": "'Special'"
      }
    ],
    "hints": [
      "Check digit range `ch >= '0' && ch <= '9'`, letter range, else special."
    ],
    "approach": "Classify using ASCII range checks.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String classify(char ch) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'7': \" + sol.classify('7')); // Digit\n    }\n}",
    "javaSolution": "class Solution {\n    public String classify(char ch) {\n        if (ch >= '0' && ch <= '9') {\n            return \"Digit\";\n        } else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {\n            return \"Letter\";\n        } else {\n            return \"Special\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"'7': \" + sol.classify('7')); // Digit\n        System.out.println(\"'A': \" + sol.classify('A')); // Letter\n        System.out.println(\"'#': \" + sol.classify('#')); // Special\n    }\n}",
    "pythonSolution": "def solution(ch):\n    if '0' <= ch <= '9':\n        return \"Digit\"\n    elif ('A' <= ch <= 'Z') or ('a' <= ch <= 'z'):\n        return \"Letter\"\n    else:\n        return \"Special\"\n\n# Test\nprint(solution('7'))  # Digit\nprint(solution('@'))  # Special",
    "intuitionEn": "ASCII values fall in contiguous clusters: digits (48-57), uppercase letters (65-90), lowercase (97-122).",
    "intuitionHi": "Digits, letters aur special symbols ke ASCII codes alag alag ranges me aate hain.",
    "stepsEn": [
      "Check digit.",
      "Check letter.",
      "Default to special."
    ],
    "stepsHi": [
      "Digit range check karein.",
      "Letter range check karein.",
      "Baaki special hain."
    ]
  },
  {
    "id": 25,
    "slug": "atm-pin-verification",
    "title": "Simple ATM PIN Checker (Match with a Fixed Value)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an entered ATM PIN as `enteredPin` and the user's registered PIN as `actualPin`, return `\"Access Granted\"` if they match, otherwise return `\"Incorrect PIN\"`.",
    "examples": [
      {
        "input": "enteredPin = 1234, actualPin = 1234",
        "output": "\"Access Granted\"",
        "explanation": "PINs match."
      },
      {
        "input": "enteredPin = 9999, actualPin = 1234",
        "output": "\"Incorrect PIN\"",
        "explanation": "PINs do not match."
      }
    ],
    "constraints": [
      "0 ≤ enteredPin, actualPin ≤ 9999"
    ],
    "starterCode": "def solution(enteredPin, actualPin):\n    # Return \"Access Granted\" or \"Incorrect PIN\"\n    pass\n\n# Test\nprint(solution(1234, 1234))  # Expected: Access Granted",
    "testCases": [
      {
        "input": "(1234, 1234)",
        "expected": "'Access Granted'"
      },
      {
        "input": "(9999, 1234)",
        "expected": "'Incorrect PIN'"
      }
    ],
    "hints": [
      "Use `if (enteredPin == actualPin)`."
    ],
    "approach": "Equality check for authentication authorization.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String verifyPin(int enteredPin, int actualPin) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.verifyPin(1234, 1234)); // Access Granted\n    }\n}",
    "javaSolution": "class Solution {\n    public String verifyPin(int enteredPin, int actualPin) {\n        if (enteredPin == actualPin) {\n            return \"Access Granted\";\n        } else {\n            return \"Incorrect PIN\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.verifyPin(1234, 1234)); // Access Granted\n        System.out.println(sol.verifyPin(9999, 1234)); // Incorrect PIN\n    }\n}",
    "pythonSolution": "def solution(enteredPin, actualPin):\n    return \"Access Granted\" if enteredPin == actualPin else \"Incorrect PIN\"\n\n# Test\nprint(solution(1234, 1234))  # Access Granted",
    "intuitionEn": "Direct equality check provides the fundamental building block of passkey authorization.",
    "intuitionHi": "Dono PINs ka equality check karein. Barabar hone par Access Granted return karein.",
    "stepsEn": [
      "Check equality.",
      "Return access message."
    ],
    "stepsHi": [
      "PIN match check karein."
    ]
  },
  {
    "id": 26,
    "slug": "season-by-month-switch",
    "title": "Check Season Based on Month Number using switch-case",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "switch-case",
    "phase": 1,
    "description": "Given month number `month` (1 to 12), return the season using a switch-case statement:\n- 12, 1, 2 -> `\"Winter\"`\n- 3, 4, 5 -> `\"Spring\"`\n- 6, 7, 8 -> `\"Summer\"`\n- 9, 10, 11 -> `\"Autumn\"`\nFor any other number, return `\"Invalid Month\"`.",
    "examples": [
      {
        "input": "month = 1",
        "output": "\"Winter\"",
        "explanation": "January is Winter."
      },
      {
        "input": "month = 7",
        "output": "\"Summer\"",
        "explanation": "July is Summer."
      }
    ],
    "constraints": [
      "month is an integer"
    ],
    "starterCode": "def solution(month):\n    # Return season name\n    pass\n\n# Test\nprint(solution(1))  # Expected: Winter",
    "testCases": [
      {
        "input": "(1,)",
        "expected": "'Winter'"
      },
      {
        "input": "(7,)",
        "expected": "'Summer'"
      }
    ],
    "hints": [
      "Group month numbers into cases."
    ],
    "approach": "Group months using fall-through in switch-case.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String getSeason(int month) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Month 1: \" + sol.getSeason(1)); // Winter\n    }\n}",
    "javaSolution": "class Solution {\n    public String getSeason(int month) {\n        switch (month) {\n            case 12:\n            case 1:\n            case 2:\n                return \"Winter\";\n            case 3:\n            case 4:\n            case 5:\n                return \"Spring\";\n            case 6:\n            case 7:\n            case 8:\n                return \"Summer\";\n            case 9:\n            case 10:\n            case 11:\n                return \"Autumn\";\n            default:\n                return \"Invalid Month\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Month 1: \" + sol.getSeason(1)); // Winter\n        System.out.println(\"Month 7: \" + sol.getSeason(7)); // Summer\n    }\n}",
    "pythonSolution": "def solution(month):\n    if month in [12, 1, 2]:\n        return \"Winter\"\n    elif month in [3, 4, 5]:\n        return \"Spring\"\n    elif month in [6, 7, 8]:\n        return \"Summer\"\n    elif month in [9, 10, 11]:\n        return \"Autumn\"\n    return \"Invalid Month\"\n\n# Test\nprint(solution(1))  # Winter",
    "intuitionEn": "Grouping consecutive three-month windows cleanly defines quarterly astronomical seasons.",
    "intuitionHi": "Teen teen mahino ke group ko switch case me cluster karke season return karein.",
    "stepsEn": [
      "Group cases.",
      "Return season."
    ],
    "stepsHi": [
      "Mahino ke group se season match karein."
    ]
  },
  {
    "id": 27,
    "slug": "perfect-square-check",
    "title": "Find Whether a Number is a Perfect Square (Basic Check)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given a non-negative integer `n`, return `true` if `n` is a perfect square (an integer `k` exists such that `k * k == n`), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 16",
        "output": "true",
        "explanation": "4 * 4 = 16."
      },
      {
        "input": "n = 14",
        "output": "false",
        "explanation": "No integer multiplied by itself equals 14."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁸"
    ],
    "starterCode": "def solution(n):\n    # Return True if n is a perfect square\n    pass\n\n# Test\nprint(solution(16))  # Expected: True",
    "testCases": [
      {
        "input": "(16,)",
        "expected": "True"
      },
      {
        "input": "(14,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Take square root `int root = (int) Math.sqrt(n)` and check `root * root == n`."
    ],
    "approach": "Compute integer square root and square it back to verify equality.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isPerfectSquare(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"16: \" + sol.isPerfectSquare(16)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isPerfectSquare(int n) {\n        if (n < 0) return false;\n        int root = (int) Math.sqrt(n);\n        return root * root == n;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"16: \" + sol.isPerfectSquare(16)); // true\n        System.out.println(\"14: \" + sol.isPerfectSquare(14)); // false\n        System.out.println(\"25: \" + sol.isPerfectSquare(25)); // true\n    }\n}",
    "pythonSolution": "import math\n\ndef solution(n):\n    if n < 0:\n        return False\n    root = int(math.isqrt(n))\n    return root * root == n\n\n# Test\nprint(solution(16))  # True\nprint(solution(14))  # False",
    "intuitionEn": "If an integer is a perfect square, truncated square root multiplied by itself reproduces the exact original number.",
    "intuitionHi": "Kisi number ka square root nikaal kar use wapas square karein. Agar wahi number mile to perfect square hai.",
    "stepsEn": [
      "Take `int root = Math.sqrt(n)`.",
      "Check `root * root == n`."
    ],
    "stepsHi": [
      "Square root lekar wapas square karein."
    ]
  },
  {
    "id": 28,
    "slug": "triangle-validity-by-sides",
    "title": "Check if Three Sides Can Form a Triangle",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given three side lengths `a`, `b`, and `c`, determine if they can form a valid triangle.\n\nBy the **Triangle Inequality Theorem**, the sum of any two sides must be strictly greater than the third side:\n`a + b > c && a + c > b && b + c > a`.",
    "examples": [
      {
        "input": "a = 3, b = 4, c = 5",
        "output": "true",
        "explanation": "3+4>5, 3+5>4, 4+5>3. Valid triangle."
      },
      {
        "input": "a = 1, b = 2, c = 3",
        "output": "false",
        "explanation": "1 + 2 is NOT > 3 (it equals 3), so invalid."
      }
    ],
    "constraints": [
      "1 ≤ a, b, c ≤ 10⁴"
    ],
    "starterCode": "def solution(a, b, c):\n    # Return True if a+b>c, a+c>b, and b+c>a\n    pass\n\n# Test\nprint(solution(3, 4, 5))  # Expected: True",
    "testCases": [
      {
        "input": "(3, 4, 5)",
        "expected": "True"
      },
      {
        "input": "(1, 2, 3)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check all 3 inequality conditions simultaneously."
    ],
    "approach": "Verify Triangle Inequality Theorem: `a + b > c && a + c > b && b + c > a`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean canFormTriangle(int a, int b, int c) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.canFormTriangle(3, 4, 5)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean canFormTriangle(int a, int b, int c) {\n        return (a + b > c) && (a + c > b) && (b + c > a);\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"3, 4, 5: \" + sol.canFormTriangle(3, 4, 5)); // true\n        System.out.println(\"1, 2, 3: \" + sol.canFormTriangle(1, 2, 3)); // false\n    }\n}",
    "pythonSolution": "def solution(a, b, c):\n    return (a + b > c) and (a + c > b) and (b + c > a)\n\n# Test\nprint(solution(3, 4, 5))  # True\nprint(solution(1, 2, 3))  # False",
    "intuitionEn": "The shortest distance between two points is a straight line. If two sides don't exceed the third, the endpoints cannot close into a polygon.",
    "intuitionHi": "Triangle Inequality Theorem ke anusar kisi bhi do sides ka jod teesri side se bada hona anivarya hai.",
    "stepsEn": [
      "Check `a + b > c`",
      "Check `a + c > b`",
      "Check `b + c > a`"
    ],
    "stepsHi": [
      "Teeno combinations me do sides ka jod teesri se bada hona check karein."
    ]
  },
  {
    "id": 29,
    "slug": "driving-license-eligibility",
    "title": "Check Driving License Eligibility (Age >= 18 and Has ID)",
    "difficulty": "Easy",
    "topic": "Conditionals",
    "pattern": "if-else",
    "phase": 1,
    "description": "Given an applicant's `age` (integer) and a boolean `hasId` indicating if they possess a valid government ID, return `\"Eligible\"` if `age >= 18` AND `hasId == true`, otherwise return `\"Not Eligible\"`.",
    "examples": [
      {
        "input": "age = 19, hasId = true",
        "output": "\"Eligible\"",
        "explanation": "Age >= 18 and has valid ID."
      },
      {
        "input": "age = 25, hasId = false",
        "output": "\"Not Eligible\"",
        "explanation": "Missing valid ID."
      }
    ],
    "constraints": [
      "0 ≤ age ≤ 120",
      "hasId is a boolean"
    ],
    "starterCode": "def solution(age, hasId):\n    # Return \"Eligible\" if age >= 18 and hasId else \"Not Eligible\"\n    pass\n\n# Test\nprint(solution(19, True))  # Expected: Eligible",
    "testCases": [
      {
        "input": "(19, True)",
        "expected": "'Eligible'"
      },
      {
        "input": "(25, False)",
        "expected": "'Not Eligible'"
      }
    ],
    "hints": [
      "Use `if (age >= 18 && hasId)`."
    ],
    "approach": "Compound logical check with `&&`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkLicense(int age, boolean hasId) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.checkLicense(19, true)); // Eligible\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkLicense(int age, boolean hasId) {\n        if (age >= 18 && hasId) {\n            return \"Eligible\";\n        } else {\n            return \"Not Eligible\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Age 19, ID true:  \" + sol.checkLicense(19, true));  // Eligible\n        System.out.println(\"Age 25, ID false: \" + sol.checkLicense(25, false)); // Not Eligible\n        System.out.println(\"Age 16, ID true:  \" + sol.checkLicense(16, true));  // Not Eligible\n    }\n}",
    "pythonSolution": "def solution(age, hasId):\n    return \"Eligible\" if age >= 18 and hasId else \"Not Eligible\"\n\n# Test\nprint(solution(19, True))   # Eligible\nprint(solution(25, False))  # Not Eligible",
    "intuitionEn": "Both legal age and documentary proof are mandatory prerequisites.",
    "intuitionHi": "Umar 18 ya usse badi honi chahiye AUR valid ID card bhi hona chahiye.",
    "stepsEn": [
      "Check `age >= 18 && hasId`.",
      "Return status."
    ],
    "stepsHi": [
      "Umar aur ID dono ka AND check karein."
    ]
  },
  {
    "id": 30,
    "slug": "swap-without-temp",
    "title": "Swap Two Numbers Without Using a Third Variable",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given two integers `a` and `b`, swap their values without using any third/temporary variable, and return the swapped numbers as an array `[b, a]`.",
    "examples": [
      {
        "input": "a = 5, b = 10",
        "output": "[10, 5]",
        "explanation": "Swapped values."
      }
    ],
    "constraints": [
      "-10⁵ ≤ a, b ≤ 10⁵"
    ],
    "starterCode": "def solution(a, b):\n    # Swap without temp variable\n    a = a + b\n    b = a - b\n    a = a - b\n    return [a, b]\n\n# Test\nprint(solution(5, 10))  # Expected: [10, 5]",
    "testCases": [
      {
        "input": "(5, 10)",
        "expected": "[10, 5]"
      }
    ],
    "hints": [
      "Use addition and subtraction: `a = a + b; b = a - b; a = a - b;`."
    ],
    "approach": "Use arithmetic operations to store the combined sum and recover original values.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int[] swapNumbers(int a, int b) {\n        return new int[]{a, b};\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        int[] res = sol.swapNumbers(5, 10);\n        System.out.println(java.util.Arrays.toString(res)); // [10, 5]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] swapNumbers(int a, int b) {\n        a = a + b;\n        b = a - b;\n        a = a - b;\n        return new int[] { a, b };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        int[] res = sol.swapNumbers(5, 10);\n        System.out.println(\"Swapped (5, 10): \" + Arrays.toString(res)); // [10, 5]\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    a = a + b\n    b = a - b\n    a = a - b\n    return [a, b]\n\n# Test\nprint(solution(5, 10))  # [10, 5]",
    "intuitionEn": "`a + b` encodes both values into a single variable. Subtracting `b` yields original `a`, and subtracting again yields original `b`.",
    "intuitionHi": "`a = a + b` se dono ka sum ek jagah store ho jata hai, fir subtraction se bina teesre variable ke swap ho jata hai.",
    "stepsEn": [
      "`a = a + b`",
      "`b = a - b`",
      "`a = a - b`"
    ],
    "stepsHi": [
      "Pehle sum karein.",
      "Fir subtract karke swap karein."
    ]
  },
  {
    "id": 31,
    "slug": "bitwise-operations-demo",
    "title": "Bitwise AND, OR, and XOR of Two Numbers",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given two non-negative integers `a` and `b`, compute and return their bitwise results as an array: `[a & b, a | b, a ^ b]`.",
    "examples": [
      {
        "input": "a = 5, b = 3",
        "output": "[1, 7, 6]",
        "explanation": "5 is 101, 3 is 011. AND=001 (1), OR=111 (7), XOR=110 (6)."
      }
    ],
    "constraints": [
      "0 ≤ a, b ≤ 10⁹"
    ],
    "starterCode": "def solution(a, b):\n    # Return [a & b, a | b, a ^ b]\n    pass\n\n# Test\nprint(solution(5, 3))  # Expected: [1, 7, 6]",
    "testCases": [
      {
        "input": "(5, 3)",
        "expected": "[1, 7, 6]"
      }
    ],
    "hints": [
      "Use `&` for AND, `|` for OR, and `^` for XOR."
    ],
    "approach": "Apply fundamental bitwise operators directly.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int[] bitwiseOps(int a, int b) {\n        return new int[3];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(java.util.Arrays.toString(sol.bitwiseOps(5, 3))); // [1, 7, 6]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] bitwiseOps(int a, int b) {\n        int andResult = a & b;\n        int orResult  = a | b;\n        int xorResult = a ^ b;\n        return new int[] { andResult, orResult, xorResult };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        int[] res = sol.bitwiseOps(5, 3);\n        System.out.println(\"5 and 3 bitwise [AND, OR, XOR]: \" + Arrays.toString(res)); // [1, 7, 6]\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    return [a & b, a | b, a ^ b]\n\n# Test\nprint(solution(5, 3))  # [1, 7, 6]",
    "intuitionEn": "Bitwise operators operate directly on individual binary bit representations in hardware ALU.",
    "intuitionHi": "Bitwise operators binary bits (0 aur 1) par seedha kaam karte hain.",
    "stepsEn": [
      "Apply `&`",
      "Apply `|`",
      "Apply `^`"
    ],
    "stepsHi": [
      "Bitwise AND, OR, XOR calculate karein."
    ]
  },
  {
    "id": 32,
    "slug": "simple-interest-calculator",
    "title": "Calculate Simple Interest (P * R * T / 100)",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given principal `p`, annual interest rate `r`, and time period `t` in years, calculate and return the Simple Interest using the formula: `SI = (p * r * t) / 100`.",
    "examples": [
      {
        "input": "p = 1000, r = 5, t = 2",
        "output": "100.0",
        "explanation": "(1000 * 5 * 2) / 100 = 100.0"
      }
    ],
    "constraints": [
      "0 ≤ p, r, t ≤ 10⁶"
    ],
    "starterCode": "def solution(p, r, t):\n    # Return simple interest\n    pass\n\n# Test\nprint(solution(1000, 5, 2))  # Expected: 100.0",
    "testCases": [
      {
        "input": "(1000, 5, 2)",
        "expected": "100.0"
      }
    ],
    "hints": [
      "Use formula `(p * r * t) / 100.0`."
    ],
    "approach": "Apply standard financial formula.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public double calculateSI(double p, double r, double t) {\n        return 0.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.calculateSI(1000, 5, 2)); // 100.0\n    }\n}",
    "javaSolution": "class Solution {\n    public double calculateSI(double p, double r, double t) {\n        return (p * r * t) / 100.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"SI for (P=1000, R=5, T=2): \" + sol.calculateSI(1000, 5, 2)); // 100.0\n    }\n}",
    "pythonSolution": "def solution(p, r, t):\n    return (p * r * t) / 100.0\n\n# Test\nprint(solution(1000, 5, 2))  # 100.0",
    "intuitionEn": "Standard financial arithmetic formula implemented using basic floating-point multiplication and division.",
    "intuitionHi": "Sadharan byaj (Simple Interest) ka standard formula `(P * R * T) / 100` lagayein.",
    "stepsEn": [
      "Multiply P, R, T.",
      "Divide by 100.0."
    ],
    "stepsHi": [
      "Formula apply karein."
    ]
  },
  {
    "id": 33,
    "slug": "celsius-to-fahrenheit",
    "title": "Convert Celsius to Fahrenheit",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given temperature in Celsius as `c`, convert it to Fahrenheit using formula: `F = (c * 9.0 / 5.0) + 32.0`.",
    "examples": [
      {
        "input": "c = 0",
        "output": "32.0",
        "explanation": "0 C is 32 F."
      },
      {
        "input": "c = 100",
        "output": "212.0",
        "explanation": "100 C is 212 F."
      }
    ],
    "constraints": [
      "-273.15 ≤ c ≤ 1000"
    ],
    "starterCode": "def solution(c):\n    # Return temperature in Fahrenheit\n    pass\n\n# Test\nprint(solution(0))  # Expected: 32.0",
    "testCases": [
      {
        "input": "(0,)",
        "expected": "32.0"
      },
      {
        "input": "(100,)",
        "expected": "212.0"
      }
    ],
    "hints": [
      "Use formula `(c * 9.0 / 5.0) + 32.0`."
    ],
    "approach": "Apply thermodynamic unit conversion formula.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public double toFahrenheit(double c) {\n        return 0.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"0 C in F: \" + sol.toFahrenheit(0)); // 32.0\n    }\n}",
    "javaSolution": "class Solution {\n    public double toFahrenheit(double c) {\n        return (c * 9.0 / 5.0) + 32.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"0 C in F:   \" + sol.toFahrenheit(0));   // 32.0\n        System.out.println(\"100 C in F: \" + sol.toFahrenheit(100)); // 212.0\n    }\n}",
    "pythonSolution": "def solution(c):\n    return (c * 9.0 / 5.0) + 32.0\n\n# Test\nprint(solution(0))    # 32.0\nprint(solution(100))  # 212.0",
    "intuitionEn": "Celsius to Fahrenheit scaling factor is 9/5 with an offset of 32 degrees.",
    "intuitionHi": "Temperature conversion formula `(C * 9/5) + 32` use karein.",
    "stepsEn": [
      "Multiply by 9.",
      "Divide by 5.",
      "Add 32."
    ],
    "stepsHi": [
      "Formula apply karein."
    ]
  },
  {
    "slug": "arithmetic-operations-demo",
    "title": "Perform Basic Arithmetic Operations (+, -, *, /)",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given two positive integers `a` and `b`, calculate and return an array of 4 basic arithmetic results: `[sum, difference, product, integer quotient]`.",
    "examples": [
      {
        "input": "a = 20, b = 4",
        "output": "[24, 16, 80, 5]",
        "explanation": "20+4=24, 20-4=16, 20*4=80, 20/4=5."
      }
    ],
    "constraints": [
      "1 ≤ a, b ≤ 10⁵"
    ],
    "starterCode": "def solution(a, b):\n    # Return [a+b, a-b, a*b, a//b]\n    pass\n\n# Test\nprint(solution(20, 4))  # Expected: [24, 16, 80, 5]",
    "testCases": [
      {
        "input": "(20, 4)",
        "expected": "[24, 16, 80, 5]"
      },
      {
        "input": "(10, 2)",
        "expected": "[12, 8, 20, 5]"
      }
    ],
    "hints": [
      "Use `+`, `-`, `*`, and integer division `/` (or `//` in Python)."
    ],
    "approach": "Apply standard arithmetic operators sequentially.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] calculate(int a, int b) {\n        return new int[4];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.calculate(20, 4))); // [24, 16, 80, 5]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] calculate(int a, int b) {\n        int sum = a + b;\n        int diff = a - b;\n        int prod = a * b;\n        int quot = a / b;\n        return new int[] { sum, diff, prod, quot };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Result (20, 4): \" + Arrays.toString(sol.calculate(20, 4))); // [24, 16, 80, 5]\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    return [a + b, a - b, a * b, a // b]\n\n# Test\nprint(solution(20, 4))  # [24, 16, 80, 5]",
    "intuitionEn": "Basic CPU arithmetic instructions execute addition, subtraction, multiplication, and quotient directly in hardware registers.",
    "intuitionHi": "Arithmetic operators (+, -, *, /) seedhe hardware level par calculate hote hain.",
    "stepsEn": [
      "Compute sum `a + b`.",
      "Compute diff `a - b`.",
      "Compute product `a * b`.",
      "Compute quotient `a / b`."
    ],
    "stepsHi": [
      "Dono numbers ko jodein, ghatayein, multiply karein aur divide karein."
    ],
    "id": 34
  },
  {
    "slug": "remainder-without-modulo",
    "title": "Find Remainder Without Using Modulo (%) Operator",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given dividend `a` and divisor `b`, compute the remainder without using the `%` operator, using formula: `remainder = a - (a / b) * b`.",
    "examples": [
      {
        "input": "a = 14, b = 4",
        "output": "2",
        "explanation": "14 / 4 is 3. 14 - (3 * 4) = 2."
      }
    ],
    "constraints": [
      "1 ≤ a, b ≤ 10⁶"
    ],
    "starterCode": "def solution(a, b):\n    # Return remainder without %\n    pass\n\n# Test\nprint(solution(14, 4))  # Expected: 2",
    "testCases": [
      {
        "input": "(14, 4)",
        "expected": "2"
      },
      {
        "input": "(25, 5)",
        "expected": "0"
      }
    ],
    "hints": [
      "By division theorem: `Dividend = Quotient * Divisor + Remainder`."
    ],
    "approach": "Compute quotient using integer division, then subtract `quotient * b` from `a`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int findRemainder(int a, int b) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.findRemainder(14, 4)); // 2\n    }\n}",
    "javaSolution": "class Solution {\n    public int findRemainder(int a, int b) {\n        int quotient = a / b;\n        int remainder = a - (quotient * b);\n        return remainder;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Remainder of 14 / 4: \" + sol.findRemainder(14, 4)); // 2\n        System.out.println(\"Remainder of 25 / 5: \" + sol.findRemainder(25, 5)); // 0\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    quotient = a // b\n    return a - (quotient * b)\n\n# Test\nprint(solution(14, 4))  # 2",
    "intuitionEn": "Division algorithm identity: remainder is the leftover part after removing the largest multiple of divisor from dividend.",
    "intuitionHi": "Division theorem: Bhajya = (Bhagfal * Bhajak) + Sheshfal. Is formula se sheshfal nikal aata hai.",
    "stepsEn": [
      "Find integer quotient `q = a / b`.",
      "Multiply `q * b`.",
      "Subtract from `a`."
    ],
    "stepsHi": [
      "Bhagfal nikalein, use b se multiply karein aur a me se ghata dein."
    ],
    "id": 35
  },
  {
    "slug": "rectangle-area-perimeter",
    "title": "Calculate Area and Perimeter of a Rectangle",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given `length` and `breadth` of a rectangle, return an array `[area, perimeter]` where `area = length * breadth` and `perimeter = 2 * (length + breadth)`.",
    "examples": [
      {
        "input": "length = 5, breadth = 3",
        "output": "[15, 16]",
        "explanation": "Area = 5*3=15, Perimeter = 2*(5+3)=16."
      }
    ],
    "constraints": [
      "1 ≤ length, breadth ≤ 10⁴"
    ],
    "starterCode": "def solution(length, breadth):\n    # Return [area, perimeter]\n    pass\n\n# Test\nprint(solution(5, 3))  # Expected: [15, 16]",
    "testCases": [
      {
        "input": "(5, 3)",
        "expected": "[15, 16]"
      },
      {
        "input": "(10, 4)",
        "expected": "[40, 28]"
      }
    ],
    "hints": [
      "Area is `length * breadth`, perimeter is `2 * (length + breadth)`."
    ],
    "approach": "Apply geometry formulas using multiplication and addition.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] rectangleMetrics(int length, int breadth) {\n        return new int[2];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.rectangleMetrics(5, 3))); // [15, 16]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] rectangleMetrics(int length, int breadth) {\n        int area = length * breadth;\n        int perimeter = 2 * (length + breadth);\n        return new int[] { area, perimeter };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Rectangle (5, 3): \" + Arrays.toString(sol.rectangleMetrics(5, 3))); // [15, 16]\n    }\n}",
    "pythonSolution": "def solution(length, breadth):\n    area = length * breadth\n    perimeter = 2 * (length + breadth)\n    return [area, perimeter]\n\n# Test\nprint(solution(5, 3))  # [15, 16]",
    "intuitionEn": "Direct application of 2D Euclidean geometry formulas for 4-sided quadrilaterals with right angles.",
    "intuitionHi": "Aayat (Rectangle) ka kshetraphal aur parimap sidhe formula se nikalte hain.",
    "stepsEn": [
      "Compute `area = l * b`.",
      "Compute `perimeter = 2 * (l + b)`.",
      "Return `[area, perimeter]`."
    ],
    "stepsHi": [
      "Area aur Perimeter formula apply karein."
    ],
    "id": 36
  },
  {
    "slug": "circle-area-circumference",
    "title": "Calculate Area and Circumference of a Circle",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given the radius `r` of a circle, calculate and return `[area, circumference]` rounded to 2 decimal places using Math.PI (`Area = π * r²`, `Circumference = 2 * π * r`).",
    "examples": [
      {
        "input": "r = 7",
        "output": "[153.94, 43.98]",
        "explanation": "PI * 49 ≈ 153.94, 2 * PI * 7 ≈ 43.98."
      }
    ],
    "constraints": [
      "1 ≤ r ≤ 10⁴"
    ],
    "starterCode": "def solution(r):\n    # Return [round(area, 2), round(circumference, 2)]\n    pass\n\n# Test\nprint(solution(7))  # Expected: [153.94, 43.98]",
    "testCases": [
      {
        "input": "(7,)",
        "expected": "[153.94, 43.98]"
      }
    ],
    "hints": [
      "Use `math.pi` or `Math.PI`."
    ],
    "approach": "Use standard circle formulas with PI.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public double[] circleMetrics(double r) {\n        return new double[2];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.circleMetrics(7)));\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public double[] circleMetrics(double r) {\n        double area = Math.PI * r * r;\n        double circumference = 2 * Math.PI * r;\n        // Round to 2 decimal places\n        area = Math.round(area * 100.0) / 100.0;\n        circumference = Math.round(circumference * 100.0) / 100.0;\n        return new double[] { area, circumference };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Circle (r=7): \" + Arrays.toString(sol.circleMetrics(7))); // [153.94, 43.98]\n    }\n}",
    "pythonSolution": "import math\n\ndef solution(r):\n    area = round(math.pi * r * r, 2)\n    circumference = round(2 * math.pi * r, 2)\n    return [area, circumference]\n\n# Test\nprint(solution(7))  # [153.94, 43.98]",
    "intuitionEn": "The ratio of circumference to diameter is universally constant π (pi).",
    "intuitionHi": "Vritt (Circle) ka area aur paridhi Math.PI constant use karke nikala jata hai.",
    "stepsEn": [
      "Compute `area = pi * r * r`.",
      "Compute `circ = 2 * pi * r`.",
      "Round to 2 decimal places."
    ],
    "stepsHi": [
      "Formula apply karein aur 2 decimal places tak round karein."
    ],
    "id": 37
  },
  {
    "slug": "check-even-odd-bitwise",
    "title": "Check Even or Odd Using Bitwise AND (&) Operator",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given an integer `n`, determine whether it is **Even** or **Odd** using only the bitwise AND (`&`) operator instead of `% 2`.\n\nIn binary, the least significant bit (LSB) is 0 for even numbers and 1 for odd numbers.",
    "examples": [
      {
        "input": "n = 6",
        "output": "\"Even\"",
        "explanation": "6 in binary is 110 (LSB is 0, so Even)."
      },
      {
        "input": "n = 9",
        "output": "\"Odd\"",
        "explanation": "9 in binary is 1001 (LSB is 1, so Odd)."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return \"Even\" or \"Odd\" using bitwise &\n    pass\n\n# Test\nprint(solution(6))  # Expected: Even",
    "testCases": [
      {
        "input": "(6,)",
        "expected": "'Even'"
      },
      {
        "input": "(9,)",
        "expected": "'Odd'"
      }
    ],
    "hints": [
      "Evaluate `(n & 1) == 0`."
    ],
    "approach": "Inspect the lowest bit with mask `1`. If 0, number is even; if 1, number is odd.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public String checkEvenOddBitwise(int n) {\n        return \"\";\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.checkEvenOddBitwise(6)); // Even\n    }\n}",
    "javaSolution": "class Solution {\n    public String checkEvenOddBitwise(int n) {\n        // Bitwise AND with 1 tests the least significant bit (LSB)\n        if ((n & 1) == 0) {\n            return \"Even\";\n        } else {\n            return \"Odd\";\n        }\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"6 is: \" + sol.checkEvenOddBitwise(6)); // Even\n        System.out.println(\"9 is: \" + sol.checkEvenOddBitwise(9)); // Odd\n    }\n}",
    "pythonSolution": "def solution(n):\n    if (n & 1) == 0:\n        return \"Even\"\n    else:\n        return \"Odd\"\n\n# Test\nprint(solution(6))  # Even\nprint(solution(9))  # Odd",
    "intuitionEn": "All powers of 2 (2, 4, 8, 16...) are even. The only bit contributing an odd quantity 2^0 = 1 is the least significant bit.",
    "intuitionHi": "Binary me aakhiri bit (LSB) 0 ho to even hota hai, 1 ho to odd hota hai.",
    "stepsEn": [
      "Perform `n & 1`.",
      "If result is 0 return 'Even', else 'Odd'."
    ],
    "stepsHi": [
      "Bitwise AND karein: `n & 1 == 0` par Even return karein."
    ],
    "id": 38
  },
  {
    "slug": "multiply-divide-bitwise-shift",
    "title": "Multiply and Divide by 2 Using Bitwise Shift (<<, >>)",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given a non-negative integer `n`, return an array `[n * 2, n / 2]` computed strictly using bitwise Left Shift (`<< 1`) and Right Shift (`>> 1`).",
    "examples": [
      {
        "input": "n = 8",
        "output": "[16, 4]",
        "explanation": "8 << 1 is 16, 8 >> 1 is 4."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁶"
    ],
    "starterCode": "def solution(n):\n    # Return [n << 1, n >> 1]\n    pass\n\n# Test\nprint(solution(8))  # Expected: [16, 4]",
    "testCases": [
      {
        "input": "(8,)",
        "expected": "[16, 4]"
      },
      {
        "input": "(12,)",
        "expected": "[24, 6]"
      }
    ],
    "hints": [
      "`n << 1` multiplies by 2, `n >> 1` divides by 2."
    ],
    "approach": "Bit shift left adds a trailing zero (doubling), bit shift right drops the last bit (halving).",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] shiftMultiplyDivide(int n) {\n        return new int[2];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.shiftMultiplyDivide(8))); // [16, 4]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] shiftMultiplyDivide(int n) {\n        int multipliedByTwo = n << 1; // Left shift by 1 bit = * 2\n        int dividedByTwo    = n >> 1; // Right shift by 1 bit = / 2\n        return new int[] { multipliedByTwo, dividedByTwo };\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Shift ops on 8: \" + Arrays.toString(sol.shiftMultiplyDivide(8))); // [16, 4]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [n << 1, n >> 1]\n\n# Test\nprint(solution(8))  # [16, 4]",
    "intuitionEn": "In base 2, shifting binary bits to the left multiplies by 2, while shifting to the right divides by 2 in a single clock cycle.",
    "intuitionHi": "Left shift (`<<`) 1 baar karne se 2 se multiply hota hai, aur right shift (`>>`) se 2 se divide hota hai.",
    "stepsEn": [
      "Compute `n << 1`.",
      "Compute `n >> 1`.",
      "Return pair."
    ],
    "stepsHi": [
      "Shift operators apply karein."
    ],
    "id": 39
  },
  {
    "slug": "power-of-two-bitwise",
    "title": "Check if a Number is a Power of Two Using Bitwise",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if it is a power of two (`2⁰, 2¹, 2², ...`), otherwise return `false`. Use the classic bitwise trick: `n > 0 && (n & (n - 1)) == 0`.",
    "examples": [
      {
        "input": "n = 16",
        "output": "true",
        "explanation": "16 is 2^4."
      },
      {
        "input": "n = 18",
        "output": "false",
        "explanation": "18 is not a power of 2."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if n is power of two\n    pass\n\n# Test\nprint(solution(16))  # Expected: True",
    "testCases": [
      {
        "input": "(16,)",
        "expected": "True"
      },
      {
        "input": "(18,)",
        "expected": "False"
      },
      {
        "input": "(1,)",
        "expected": "True"
      }
    ],
    "hints": [
      "In binary, a power of two has exactly one set bit: `1000...`. `n - 1` has all lower bits set: `0111...`."
    ],
    "approach": "Apply `n > 0 && (n & (n - 1)) == 0`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isPowerOfTwo(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isPowerOfTwo(16)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isPowerOfTwo(int n) {\n        // A power of 2 must be positive and have exactly one set bit\n        return n > 0 && (n & (n - 1)) == 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"16 is power of 2: \" + sol.isPowerOfTwo(16)); // true\n        System.out.println(\"18 is power of 2: \" + sol.isPowerOfTwo(18)); // false\n        System.out.println(\"1 is power of 2 : \" + sol.isPowerOfTwo(1));  // true\n    }\n}",
    "pythonSolution": "def solution(n):\n    return n > 0 and (n & (n - 1)) == 0\n\n# Test\nprint(solution(16))  # True\nprint(solution(18))  # False",
    "intuitionEn": "A power of two in binary has a single '1' bit (e.g., 16 is 10000). Subtracting 1 flips all bits up to that 1 (15 is 01111). Their bitwise AND is strictly 0.",
    "intuitionHi": "Power of 2 me sirf ek single bit 1 hoti hai. `n & (n - 1)` karne par wo bit 0 ho jati hai.",
    "stepsEn": [
      "Check `n > 0`.",
      "Check `(n & (n - 1)) == 0`."
    ],
    "stepsHi": [
      "n > 0 aur `n & (n - 1) == 0` verify karein."
    ],
    "id": 40
  },
  {
    "slug": "check-kth-bit-set",
    "title": "Check if K-th Bit is Set (1 or 0)",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given an integer `n` and a 0-indexed position `k`, return `true` if the k-th bit from the right is set (1), otherwise return `false`.",
    "examples": [
      {
        "input": "n = 5, k = 0",
        "output": "true",
        "explanation": "5 is 101 in binary. Bit 0 is 1 (True)."
      },
      {
        "input": "n = 5, k = 1",
        "output": "false",
        "explanation": "5 is 101 in binary. Bit 1 is 0 (False)."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹",
      "0 ≤ k ≤ 30"
    ],
    "starterCode": "def solution(n, k):\n    # Return True if k-th bit is set else False\n    pass\n\n# Test\nprint(solution(5, 0))  # Expected: True",
    "testCases": [
      {
        "input": "(5, 0)",
        "expected": "True"
      },
      {
        "input": "(5, 1)",
        "expected": "False"
      }
    ],
    "hints": [
      "Use bit mask `1 << k` with `&` operator: `(n & (1 << k)) != 0`."
    ],
    "approach": "Create a mask with 1 at position k and test with bitwise AND.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isKthBitSet(int n, int k) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isKthBitSet(5, 0)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isKthBitSet(int n, int k) {\n        // Shift 1 left by k positions and bitwise AND with n\n        return (n & (1 << k)) != 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Bit 0 of 5 set? \" + sol.isKthBitSet(5, 0)); // true\n        System.out.println(\"Bit 1 of 5 set? \" + sol.isKthBitSet(5, 1)); // false\n    }\n}",
    "pythonSolution": "def solution(n, k):\n    return (n & (1 << k)) != 0\n\n# Test\nprint(solution(5, 0))  # True\nprint(solution(5, 1))  # False",
    "intuitionEn": "`1 << k` constructs a binary probe with only the k-th bit turned on. The bitwise AND isolates that exact bit.",
    "intuitionHi": "`1 << k` mask banakar bitwise AND karein. Agar result non-zero hai to bit 1 hai.",
    "stepsEn": [
      "Shift `mask = 1 << k`.",
      "Check `(n & mask) != 0`."
    ],
    "stepsHi": [
      "Mask banakar AND check karein."
    ],
    "id": 41
  },
  {
    "slug": "toggle-kth-bit",
    "title": "Toggle the K-th Bit of a Number",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Bitwise Operators",
    "phase": 1,
    "description": "Given an integer `n` and a 0-indexed position `k`, toggle the k-th bit (change 1 to 0 or 0 to 1) using bitwise XOR (`^`) with `1 << k` and return the new number.",
    "examples": [
      {
        "input": "n = 5, k = 1",
        "output": "7",
        "explanation": "5 is 101. Toggling bit 1 gives 111 (7)."
      },
      {
        "input": "n = 7, k = 1",
        "output": "5",
        "explanation": "7 is 111. Toggling bit 1 gives 101 (5)."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹",
      "0 ≤ k ≤ 30"
    ],
    "starterCode": "def solution(n, k):\n    # Return n with k-th bit toggled\n    pass\n\n# Test\nprint(solution(5, 1))  # Expected: 7",
    "testCases": [
      {
        "input": "(5, 1)",
        "expected": "7"
      },
      {
        "input": "(7, 1)",
        "expected": "5"
      }
    ],
    "hints": [
      "XOR with 1 flips the bit: `n ^ (1 << k)`."
    ],
    "approach": "Apply bitwise XOR with single-bit mask `1 << k`.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int toggleKthBit(int n, int k) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.toggleKthBit(5, 1)); // 7\n    }\n}",
    "javaSolution": "class Solution {\n    public int toggleKthBit(int n, int k) {\n        // XOR with (1 << k) flips only the k-th bit\n        return n ^ (1 << k);\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"5 with bit 1 toggled: \" + sol.toggleKthBit(5, 1)); // 7\n        System.out.println(\"7 with bit 1 toggled: \" + sol.toggleKthBit(7, 1)); // 5\n    }\n}",
    "pythonSolution": "def solution(n, k):\n    return n ^ (1 << k)\n\n# Test\nprint(solution(5, 1))  # 7",
    "intuitionEn": "The XOR truth table flips state whenever paired with 1: `0 ^ 1 = 1` and `1 ^ 1 = 0`.",
    "intuitionHi": "XOR operator (`^`) 1 ke sath bit ko invert (0 se 1 ya 1 se 0) kar deta hai.",
    "stepsEn": [
      "Shift `1 << k`.",
      "XOR with `n`."
    ],
    "stepsHi": [
      "`n ^ (1 << k)` calculate karein."
    ],
    "id": 42
  },
  {
    "slug": "average-of-three-numbers",
    "title": "Calculate Average of Three Numbers",
    "difficulty": "Easy",
    "topic": "Operators",
    "pattern": "Arithmetic Operators",
    "phase": 1,
    "description": "Given three numbers `a`, `b`, and `c`, calculate and return their average as a floating-point value rounded to 2 decimal places: `(a + b + c) / 3.0`.",
    "examples": [
      {
        "input": "a = 10, b = 20, c = 30",
        "output": "20.0",
        "explanation": "(10 + 20 + 30) / 3 = 20.0."
      }
    ],
    "constraints": [
      "0 ≤ a, b, c ≤ 10⁶"
    ],
    "starterCode": "def solution(a, b, c):\n    # Return average\n    pass\n\n# Test\nprint(solution(10, 20, 30))  # Expected: 20.0",
    "testCases": [
      {
        "input": "(10, 20, 30)",
        "expected": "20.0"
      },
      {
        "input": "(5, 10, 15)",
        "expected": "10.0"
      }
    ],
    "hints": [
      "Sum the three values and divide by 3.0."
    ],
    "approach": "Apply floating point division to prevent integer truncation.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public double average(double a, double b, double c) {\n        return 0.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.average(10, 20, 30)); // 20.0\n    }\n}",
    "javaSolution": "class Solution {\n    public double average(double a, double b, double c) {\n        double sum = a + b + c;\n        double avg = sum / 3.0;\n        return Math.round(avg * 100.0) / 100.0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Average of 10, 20, 30: \" + sol.average(10, 20, 30)); // 20.0\n    }\n}",
    "pythonSolution": "def solution(a, b, c):\n    return round((a + b + c) / 3.0, 2)\n\n# Test\nprint(solution(10, 20, 30))  # 20.0",
    "intuitionEn": "Sum of elements divided by sample size `n = 3` using floating-point arithmetic.",
    "intuitionHi": "Teeno numbers ko jodkar 3.0 se divide karein taaki decimal accuracy bani rahe.",
    "stepsEn": [
      "Sum `a + b + c`.",
      "Divide by 3.0.",
      "Round to 2 decimals."
    ],
    "stepsHi": [
      "Teeno ko jodein aur 3.0 se divide karein."
    ],
    "id": 43
  },
  {
    "id": 44,
    "slug": "print-1-to-n-loop",
    "title": "Print Numbers from 1 to N using Loop",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n`, generate and return an array containing all integers from 1 up to `n` in ascending order (`[1, 2, 3, ..., n]`).",
    "examples": [
      {
        "input": "n = 5",
        "output": "[1, 2, 3, 4, 5]",
        "explanation": "Numbers from 1 to 5."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 1000"
    ],
    "starterCode": "def solution(n):\n    # Return list of numbers from 1 to n\n    pass\n\n# Test\nprint(solution(5))  # Expected: [1, 2, 3, 4, 5]",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "[1, 2, 3, 4, 5]"
      }
    ],
    "hints": [
      "Use a for loop from 1 to n: `for (int i = 1; i <= n; i++)`."
    ],
    "approach": "Iterate from 1 to n and collect each integer in an array.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(n)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] print1ToN(int n) {\n        return new int[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.print1ToN(5))); // [1, 2, 3, 4, 5]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] print1ToN(int n) {\n        int[] result = new int[n];\n        for (int i = 0; i < n; i++) {\n            result[i] = i + 1; // Store numbers 1 to n\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"1 to 5: \" + Arrays.toString(sol.print1ToN(5))); // [1, 2, 3, 4, 5]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [i for i in range(1, n + 1)]\n\n# Test\nprint(solution(5))  # [1, 2, 3, 4, 5]",
    "intuitionEn": "The fundamental loop construct: starting at index 1 and incrementing by 1 on each repetition until reaching upper limit n.",
    "intuitionHi": "Loop ka sabse basic use: 1 se shuru karke n tak ek ek number aage badhna.",
    "stepsEn": [
      "Initialize array of size n.",
      "Loop `i` from 1 to n.",
      "Store `i` in array."
    ],
    "stepsHi": [
      "1 se n tak for-loop chalayein.",
      "Result array return karein."
    ]
  },
  {
    "id": 45,
    "slug": "sum-of-first-n-numbers",
    "title": "Calculate Sum of First N Natural Numbers",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given an integer `n`, calculate and return the sum of all natural numbers from 1 to `n` (`1 + 2 + 3 + ... + n`) using a loop.",
    "examples": [
      {
        "input": "n = 5",
        "output": "15",
        "explanation": "1 + 2 + 3 + 4 + 5 = 15."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 10⁴"
    ],
    "starterCode": "def solution(n):\n    # Return sum 1 + 2 + ... + n\n    pass\n\n# Test\nprint(solution(5))  # Expected: 15",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "15"
      },
      {
        "input": "(10,)",
        "expected": "55"
      }
    ],
    "hints": [
      "Initialize `sum = 0`, loop `i` from 1 to n and add `sum += i`."
    ],
    "approach": "Use an accumulator variable `sum` and add every number from 1 to n.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int sumFirstN(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.sumFirstN(5)); // 15\n    }\n}",
    "javaSolution": "class Solution {\n    public int sumFirstN(int n) {\n        int sum = 0;\n        int i = 1;\n        while (i <= n) {\n            sum += i;\n            i++;\n        }\n        return sum;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Sum 1..5 : \" + sol.sumFirstN(5));  // 15\n        System.out.println(\"Sum 1..10: \" + sol.sumFirstN(10)); // 55\n    }\n}",
    "pythonSolution": "def solution(n):\n    total = 0\n    for i in range(1, n + 1):\n        total += i\n    return total\n\n# Test\nprint(solution(5))  # 15",
    "intuitionEn": "Accumulation pattern: maintaining a running sum across sequential loop steps.",
    "intuitionHi": "Accumulator pattern: ek `sum` variable me har step par agla number jodte jana.",
    "stepsEn": [
      "Set `sum = 0`.",
      "Loop from 1 to n.",
      "Add each number to sum."
    ],
    "stepsHi": [
      "`sum = 0` se shuru karein.",
      "Har number ko sum me add karein."
    ]
  },
  {
    "id": 46,
    "slug": "multiplication-table",
    "title": "Multiplication Table of a Number",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n`, generate its multiplication table up to 10 multiples (`[n*1, n*2, n*3, ..., n*10]`).",
    "examples": [
      {
        "input": "n = 5",
        "output": "[5, 10, 15, 20, 25, 30, 35, 40, 45, 50]",
        "explanation": "5 * 1 to 5 * 10."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 1000"
    ],
    "starterCode": "def solution(n):\n    # Return table [n*1, ..., n*10]\n    pass\n\n# Test\nprint(solution(5))  # Expected: [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "[5, 10, 15, 20, 25, 30, 35, 40, 45, 50]"
      }
    ],
    "hints": [
      "Run a loop `i` from 1 to 10 and compute `n * i`."
    ],
    "approach": "Loop from 1 to 10, computing each multiple.",
    "timeComplexity": "O(1) — exactly 10 iterations",
    "spaceComplexity": "O(1) — fixed array of size 10",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] table(int n) {\n        return new int[10];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.table(5)));\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] table(int n) {\n        int[] result = new int[10];\n        for (int i = 1; i <= 10; i++) {\n            result[i - 1] = n * i;\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Table of 5: \" + Arrays.toString(sol.table(5)));\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [n * i for i in range(1, 11)]\n\n# Test\nprint(solution(5))",
    "intuitionEn": "Fixed-bound iteration: repeating a calculation exactly 10 times with counter `i`.",
    "intuitionHi": "1 se 10 tak loop chalakar har step par `n * i` nikalte hain.",
    "stepsEn": [
      "Loop from 1 to 10.",
      "Multiply `n * i`.",
      "Return array."
    ],
    "stepsHi": [
      "1 se 10 tak loop chalayein.",
      "Table array return karein."
    ]
  },
  {
    "id": 47,
    "slug": "factorial-of-number",
    "title": "Factorial of a Number (N!)",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n` (0 ≤ n ≤ 20), calculate its factorial `n! = n * (n-1) * ... * 1`. Note that `0! = 1`.",
    "examples": [
      {
        "input": "n = 5",
        "output": "120",
        "explanation": "5 * 4 * 3 * 2 * 1 = 120."
      },
      {
        "input": "n = 0",
        "output": "1",
        "explanation": "0! is defined as 1."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 20"
    ],
    "starterCode": "def solution(n):\n    # Return n!\n    pass\n\n# Test\nprint(solution(5))  # Expected: 120",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "120"
      },
      {
        "input": "(0,)",
        "expected": "1"
      }
    ],
    "hints": [
      "Initialize `ans = 1`, loop from 1 to n and multiply `ans *= i`."
    ],
    "approach": "Iterative product multiplication.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public long factorial(int n) {\n        return 1L;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"5! = \" + sol.factorial(5)); // 120\n    }\n}",
    "javaSolution": "class Solution {\n    public long factorial(int n) {\n        long result = 1;\n        for (int i = 1; i <= n; i++) {\n            result *= i;\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"5! = \" + sol.factorial(5)); // 120\n        System.out.println(\"0! = \" + sol.factorial(0)); // 1\n        System.out.println(\"6! = \" + sol.factorial(6)); // 720\n    }\n}",
    "pythonSolution": "def solution(n):\n    res = 1\n    for i in range(1, n + 1):\n        res *= i\n    return res\n\n# Test\nprint(solution(5))  # 120",
    "intuitionEn": "Product accumulator: multiply running total by consecutive integers.",
    "intuitionHi": "Product accumulator: `result = 1` lekar har number ko multiply karte jana.",
    "stepsEn": [
      "Start with `1`.",
      "Multiply by 1, 2, ..., n."
    ],
    "stepsHi": [
      "1 se n tak multiply karein."
    ]
  },
  {
    "id": 48,
    "slug": "count-digits-in-integer",
    "title": "Count Digits in an Integer",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given a non-negative integer `n`, count and return the total number of digits it contains. For `n = 0`, the count is 1.",
    "examples": [
      {
        "input": "n = 12345",
        "output": "5",
        "explanation": "12345 has 5 digits."
      },
      {
        "input": "n = 0",
        "output": "1",
        "explanation": "0 has 1 digit."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return number of digits\n    pass\n\n# Test\nprint(solution(12345))  # Expected: 5",
    "testCases": [
      {
        "input": "(12345,)",
        "expected": "5"
      },
      {
        "input": "(0,)",
        "expected": "1"
      }
    ],
    "hints": [
      "While `n > 0`, divide `n /= 10` and increment count."
    ],
    "approach": "Repeatedly divide by 10 until 0 is reached.",
    "timeComplexity": "O(log10(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int countDigits(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Digits in 12345: \" + sol.countDigits(12345)); // 5\n    }\n}",
    "javaSolution": "class Solution {\n    public int countDigits(int n) {\n        if (n == 0) return 1;\n        int count = 0;\n        while (n > 0) {\n            count++;\n            n /= 10; // Discard last digit\n        }\n        return count;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Digits in 12345: \" + sol.countDigits(12345)); // 5\n        System.out.println(\"Digits in 0    : \" + sol.countDigits(0));     // 1\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n == 0:\n        return 1\n    count = 0\n    while n > 0:\n        count += 1\n        n //= 10\n    return count\n\n# Test\nprint(solution(12345))  # 5",
    "intuitionEn": "Dividing an integer by 10 in integer arithmetic strips off the last decimal digit.",
    "intuitionHi": "Kisi number ko 10 se divide karne par uska aakhiri digit hat jata hai.",
    "stepsEn": [
      "Handle 0.",
      "Loop while n > 0.",
      "Increment count and `n /= 10`."
    ],
    "stepsHi": [
      "Jab tak n > 0 rahe, count badhayein aur n ko 10 se divide karein."
    ]
  },
  {
    "id": 49,
    "slug": "reverse-number-digits",
    "title": "Reverse a Given Integer",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given a non-negative integer `n`, reverse its digits and return the reversed integer (e.g. 1234 becomes 4321).",
    "examples": [
      {
        "input": "n = 1234",
        "output": "4321",
        "explanation": "Digits reversed."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return reversed integer\n    pass\n\n# Test\nprint(solution(1234))  # Expected: 4321",
    "testCases": [
      {
        "input": "(1234,)",
        "expected": "4321"
      },
      {
        "input": "(100,)",
        "expected": "1"
      }
    ],
    "hints": [
      "Extract last digit `d = n % 10`, then append: `rev = rev * 10 + d`."
    ],
    "approach": "Extract digits from right to left using `% 10` and append to reverse accumulator using `* 10`.",
    "timeComplexity": "O(log10(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int reverseNumber(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.reverseNumber(1234)); // 4321\n    }\n}",
    "javaSolution": "class Solution {\n    public int reverseNumber(int n) {\n        int rev = 0;\n        while (n > 0) {\n            int digit = n % 10;\n            rev = (rev * 10) + digit;\n            n /= 10;\n        }\n        return rev;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Reverse of 1234: \" + sol.reverseNumber(1234)); // 4321\n        System.out.println(\"Reverse of 500 : \" + sol.reverseNumber(500));  // 5\n    }\n}",
    "pythonSolution": "def solution(n):\n    rev = 0\n    while n > 0:\n        rev = rev * 10 + (n % 10)\n        n //= 10\n    return rev\n\n# Test\nprint(solution(1234))  # 4321",
    "intuitionEn": "To reverse digits, repeatedly take `n % 10` to get the least significant digit, and shift existing reversed digits left by multiplying by 10.",
    "intuitionHi": "Har baar last digit nikalne ke liye `n % 10` karein aur naye number me `rev * 10 + digit` jodte jayein.",
    "stepsEn": [
      "Extract last digit: `d = n % 10`.",
      "Shift and add: `rev = rev * 10 + d`.",
      "Remove last digit: `n /= 10`."
    ],
    "stepsHi": [
      "Last digit nikalein.",
      "Rev ko 10 se multiply karke digit jodein.",
      "n ko 10 se divide karein."
    ]
  },
  {
    "id": 50,
    "slug": "palindrome-number-check",
    "title": "Check if a Number is a Palindrome",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given an integer `n`, return `true` if `n` reads the same backward as forward (e.g. 121 is palindrome, 123 is not). Negative numbers are not palindromes.",
    "examples": [
      {
        "input": "n = 121",
        "output": "true",
        "explanation": "121 reversed is 121."
      },
      {
        "input": "n = 123",
        "output": "false",
        "explanation": "123 reversed is 321."
      }
    ],
    "constraints": [
      "-10⁹ ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return True if palindrome else False\n    pass\n\n# Test\nprint(solution(121))  # Expected: True",
    "testCases": [
      {
        "input": "(121,)",
        "expected": "True"
      },
      {
        "input": "(123,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Reverse the number and compare it with the original."
    ],
    "approach": "Reverse the integer and compare with original number.",
    "timeComplexity": "O(log10(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isPalindrome(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isPalindrome(121)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isPalindrome(int n) {\n        if (n < 0) return false;\n        int original = n;\n        int rev = 0;\n        while (n > 0) {\n            rev = (rev * 10) + (n % 10);\n            n /= 10;\n        }\n        return original == rev;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"121 is palindrome? \" + sol.isPalindrome(121)); // true\n        System.out.println(\"123 is palindrome? \" + sol.isPalindrome(123)); // false\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n < 0:\n        return False\n    return str(n) == str(n)[::-1]\n\n# Test\nprint(solution(121))  # True\nprint(solution(123))  # False",
    "intuitionEn": "A palindrome number equals its own reversed digit sequence.",
    "intuitionHi": "Agar kisi number ko ulta karne par wahi number wapas mile, to use Palindrome kehte hain.",
    "stepsEn": [
      "Check negative (false).",
      "Reverse digits.",
      "Compare with original."
    ],
    "stepsHi": [
      "Negative check karein.",
      "Number reverse karein.",
      "Original se compare karein."
    ]
  },
  {
    "id": 51,
    "slug": "check-prime-number",
    "title": "Check Whether a Number is Prime",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n`, determine whether it is a **Prime Number**.\n\nA prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself.",
    "examples": [
      {
        "input": "n = 7",
        "output": "true",
        "explanation": "7 is only divisible by 1 and 7."
      },
      {
        "input": "n = 8",
        "output": "false",
        "explanation": "8 is divisible by 2 and 4."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 10⁶"
    ],
    "starterCode": "def solution(n):\n    # Return True if prime else False\n    pass\n\n# Test\nprint(solution(7))  # Expected: True",
    "testCases": [
      {
        "input": "(7,)",
        "expected": "True"
      },
      {
        "input": "(8,)",
        "expected": "False"
      }
    ],
    "hints": [
      "Check divisibility from 2 up to sqrt(n): `i * i <= n`."
    ],
    "approach": "Test factors up to square root of n: `for (int i = 2; i * i <= n; i++)`.",
    "timeComplexity": "O(sqrt(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isPrime(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isPrime(7)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    // Optimal prime check up to sqrt(n)\n    public boolean isPrime(int n) {\n        if (n <= 1) return false;\n        for (int i = 2; i * i <= n; i++) {\n            if (n % i == 0) {\n                return false; // Found a factor, not prime\n            }\n        }\n        return true;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"7 is prime?  \" + sol.isPrime(7));  // true\n        System.out.println(\"8 is prime?  \" + sol.isPrime(8));  // false\n        System.out.println(\"29 is prime? \" + sol.isPrime(29)); // true\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n <= 1:\n        return False\n    i = 2\n    while i * i <= n:\n        if n % i == 0:\n            return False\n        i += 1\n    return True\n\n# Test\nprint(solution(7))  # True\nprint(solution(8))  # False",
    "intuitionEn": "If a number has any divisor, at least one divisor must be less than or equal to `sqrt(n)`. Checking beyond `sqrt(n)` is redundant.",
    "intuitionHi": "Agar kisi number ka koi factor hai to wo `sqrt(n)` se chhota ya barabar hoga. Isliye loop sirf `i * i <= n` tak chalta hai.",
    "stepsEn": [
      "If n <= 1 return false.",
      "Loop from 2 up to sqrt(n).",
      "If n % i == 0 return false.",
      "Return true."
    ],
    "stepsHi": [
      "n <= 1 par false.",
      "2 se sqrt(n) tak check karein.",
      "Agar divide hua to false, warna true."
    ]
  },
  {
    "id": 52,
    "slug": "power-of-number-loop",
    "title": "Calculate Power (base^exponent) using Loop",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given base `base` and non-negative exponent `exp`, calculate `base` raised to the power `exp` (`base^exp`) using a loop.",
    "examples": [
      {
        "input": "base = 2, exp = 3",
        "output": "8",
        "explanation": "2 * 2 * 2 = 8."
      }
    ],
    "constraints": [
      "0 ≤ base ≤ 50",
      "0 ≤ exp ≤ 20"
    ],
    "starterCode": "def solution(base, exp):\n    # Return base ** exp\n    pass\n\n# Test\nprint(solution(2, 3))  # Expected: 8",
    "testCases": [
      {
        "input": "(2, 3)",
        "expected": "8"
      },
      {
        "input": "(5, 0)",
        "expected": "1"
      }
    ],
    "hints": [
      "Multiply `ans *= base` `exp` times."
    ],
    "approach": "Loop `exp` times, multiplying result by base.",
    "timeComplexity": "O(exp)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public long power(int base, int exp) {\n        return 1L;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.power(2, 3)); // 8\n    }\n}",
    "javaSolution": "class Solution {\n    public long power(int base, int exp) {\n        long result = 1;\n        for (int i = 0; i < exp; i++) {\n            result *= base;\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"2^3 = \" + sol.power(2, 3)); // 8\n        System.out.println(\"5^0 = \" + sol.power(5, 0)); // 1\n    }\n}",
    "pythonSolution": "def solution(base, exp):\n    res = 1\n    for _ in range(exp):\n        res *= base\n    return res\n\n# Test\nprint(solution(2, 3))  # 8",
    "intuitionEn": "Exponentiation is repeated multiplication of the base by itself `exp` times.",
    "intuitionHi": "Power ka matlab hai base ko `exp` baar aapas me multiply karna.",
    "stepsEn": [
      "Initialize `res = 1`.",
      "Multiply by base `exp` times."
    ],
    "stepsHi": [
      "`res = 1` lekar `exp` baar base se multiply karein."
    ]
  },
  {
    "id": 53,
    "slug": "gcd-of-two-numbers",
    "title": "Find GCD / HCF of Two Numbers",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given two positive integers `a` and `b`, find their **Greatest Common Divisor (GCD)** / Highest Common Factor (HCF) using the Euclidean Algorithm.",
    "examples": [
      {
        "input": "a = 12, b = 18",
        "output": "6",
        "explanation": "Factors of 12: 1,2,3,4,6,12. Factors of 18: 1,2,3,6,9,18. Greatest common is 6."
      }
    ],
    "constraints": [
      "1 ≤ a, b ≤ 10⁹"
    ],
    "starterCode": "def solution(a, b):\n    # Return GCD of a and b\n    pass\n\n# Test\nprint(solution(12, 18))  # Expected: 6",
    "testCases": [
      {
        "input": "(12, 18)",
        "expected": "6"
      },
      {
        "input": "(20, 28)",
        "expected": "4"
      }
    ],
    "hints": [
      "Euclidean algorithm: while `b != 0`, `temp = b; b = a % b; a = temp;`."
    ],
    "approach": "Euclidean algorithm repeatedly replaces `(a, b)` with `(b, a % b)` until `b == 0`.",
    "timeComplexity": "O(log(min(a, b)))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int findGCD(int a, int b) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.findGCD(12, 18)); // 6\n    }\n}",
    "javaSolution": "class Solution {\n    // Euclidean Algorithm for GCD\n    public int findGCD(int a, int b) {\n        while (b != 0) {\n            int rem = a % b;\n            a = b;\n            b = rem;\n        }\n        return a;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"GCD(12, 18): \" + sol.findGCD(12, 18)); // 6\n        System.out.println(\"GCD(20, 28): \" + sol.findGCD(20, 28)); // 4\n    }\n}",
    "pythonSolution": "def solution(a, b):\n    while b:\n        a, b = b, a % b\n    return a\n\n# Test\nprint(solution(12, 18))  # 6",
    "intuitionEn": "Euclidean property: `gcd(a, b) = gcd(b, a % b)`. Each step shrinks values exponentially.",
    "intuitionHi": "Euclidean algorithm: jab tak `b != 0` ho, `a % b` nikal kar aage badhte jayein.",
    "stepsEn": [
      "Loop while b != 0.",
      "Compute `rem = a % b`.",
      "Shift `a = b, b = rem`.",
      "Return `a`."
    ],
    "stepsHi": [
      "Remainder nikal kar a aur b swap karte jayein."
    ]
  },
  {
    "id": 54,
    "slug": "sum-of-digits",
    "title": "Find Sum of Digits of an Integer",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given a non-negative integer `n`, compute and return the sum of its individual digits (e.g. for `123`, sum is `1 + 2 + 3 = 6`).",
    "examples": [
      {
        "input": "n = 123",
        "output": "6",
        "explanation": "1 + 2 + 3 = 6."
      },
      {
        "input": "n = 99",
        "output": "18",
        "explanation": "9 + 9 = 18."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return sum of digits\n    pass\n\n# Test\nprint(solution(123))  # Expected: 6",
    "testCases": [
      {
        "input": "(123,)",
        "expected": "6"
      },
      {
        "input": "(99,)",
        "expected": "18"
      }
    ],
    "hints": [
      "While `n > 0`, extract `n % 10`, add to sum, and `n /= 10`."
    ],
    "approach": "Extract each digit using modulo and accumulate.",
    "timeComplexity": "O(log10(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int sumDigits(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.sumDigits(123)); // 6\n    }\n}",
    "javaSolution": "class Solution {\n    public int sumDigits(int n) {\n        int sum = 0;\n        while (n > 0) {\n            sum += n % 10;\n            n /= 10;\n        }\n        return sum;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Sum of digits in 123: \" + sol.sumDigits(123)); // 6\n        System.out.println(\"Sum of digits in 99 : \" + sol.sumDigits(99));  // 18\n    }\n}",
    "pythonSolution": "def solution(n):\n    total = 0\n    while n > 0:\n        total += n % 10\n        n //= 10\n    return total\n\n# Test\nprint(solution(123))  # 6",
    "intuitionEn": "Repeatedly popping the last digit using `% 10` and adding it to an accumulator gives the digit sum.",
    "intuitionHi": "Har baar last digit nikal kar sum me add karte jayein jab tak number 0 na ho jaye.",
    "stepsEn": [
      "Extract `n % 10`.",
      "Add to sum.",
      "Divide `n /= 10`."
    ],
    "stepsHi": [
      "Last digit ko sum me jodein aur number 10 se divide karein."
    ]
  },
  {
    "slug": "print-n-to-1-countdown",
    "title": "Print Numbers in Reverse from N down to 1",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given a positive integer `n`, generate and return an array containing all integers in reverse order from `n` down to 1 (`[n, n-1, ..., 1]`).",
    "examples": [
      {
        "input": "n = 5",
        "output": "[5, 4, 3, 2, 1]",
        "explanation": "Numbers 5 down to 1."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 1000"
    ],
    "starterCode": "def solution(n):\n    # Return list [n, n-1, ..., 1]\n    pass\n\n# Test\nprint(solution(5))  # Expected: [5, 4, 3, 2, 1]",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "[5, 4, 3, 2, 1]"
      }
    ],
    "hints": [
      "Use a decreasing loop: `for (int i = n; i >= 1; i--)`."
    ],
    "approach": "Iterate backward from n down to 1.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(n)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] printNTo1(int n) {\n        return new int[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.printNTo1(5))); // [5, 4, 3, 2, 1]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] printNTo1(int n) {\n        int[] result = new int[n];\n        for (int i = 0; i < n; i++) {\n            result[i] = n - i; // Generates n down to 1\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Countdown 5: \" + Arrays.toString(sol.printNTo1(5))); // [5, 4, 3, 2, 1]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [i for i in range(n, 0, -1)]\n\n# Test\nprint(solution(5))  # [5, 4, 3, 2, 1]",
    "intuitionEn": "Decreasing loop counter demonstrating step decrements (`i--`).",
    "intuitionHi": "Ulta loop chalana: `n` se shuru karke 1 tak ghat-te kram me aana.",
    "stepsEn": [
      "Loop from n down to 1.",
      "Collect values in array."
    ],
    "stepsHi": [
      "n se 1 tak decrement loop chalayein."
    ],
    "id": 55
  },
  {
    "slug": "print-even-numbers-up-to-n",
    "title": "Print All Even Numbers Between 1 and N",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n`, return an array containing all even numbers from 1 up to `n` in ascending order (`[2, 4, 6, ..., <= n]`).",
    "examples": [
      {
        "input": "n = 10",
        "output": "[2, 4, 6, 8, 10]",
        "explanation": "Even numbers up to 10."
      },
      {
        "input": "n = 7",
        "output": "[2, 4, 6]",
        "explanation": "Even numbers up to 7."
      }
    ],
    "constraints": [
      "2 ≤ n ≤ 1000"
    ],
    "starterCode": "def solution(n):\n    # Return list of even numbers up to n\n    pass\n\n# Test\nprint(solution(10))  # Expected: [2, 4, 6, 8, 10]",
    "testCases": [
      {
        "input": "(10,)",
        "expected": "[2, 4, 6, 8, 10]"
      },
      {
        "input": "(7,)",
        "expected": "[2, 4, 6]"
      }
    ],
    "hints": [
      "Increment by 2: `for (int i = 2; i <= n; i += 2)`."
    ],
    "approach": "Loop from 2 to n with a step of 2.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(n)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] getEvenNumbers(int n) {\n        return new int[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.getEvenNumbers(10)));\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] getEvenNumbers(int n) {\n        int size = n / 2;\n        int[] result = new int[size];\n        for (int i = 0; i < size; i++) {\n            result[i] = (i + 1) * 2;\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Even up to 10: \" + Arrays.toString(sol.getEvenNumbers(10))); // [2, 4, 6, 8, 10]\n        System.out.println(\"Even up to 7 : \" + Arrays.toString(sol.getEvenNumbers(7)));  // [2, 4, 6]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [i for i in range(2, n + 1, 2)]\n\n# Test\nprint(solution(10))  # [2, 4, 6, 8, 10]",
    "intuitionEn": "Stepping by 2 skips odd integers entirely without requiring a conditional `% 2` branch inside the loop.",
    "intuitionHi": "2 se shuru karke 2-2 aage badhne se sirf even numbers milte hain.",
    "stepsEn": [
      "Loop from 2 to n stepping by 2.",
      "Store and return array."
    ],
    "stepsHi": [
      "2, 4, 6 karke n tak loop chalayein."
    ],
    "id": 56
  },
  {
    "slug": "print-odd-numbers-up-to-n",
    "title": "Print All Odd Numbers Between 1 and N",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n`, return an array containing all odd numbers from 1 up to `n` in ascending order (`[1, 3, 5, ..., <= n]`).",
    "examples": [
      {
        "input": "n = 9",
        "output": "[1, 3, 5, 7, 9]",
        "explanation": "Odd numbers up to 9."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 1000"
    ],
    "starterCode": "def solution(n):\n    # Return list of odd numbers up to n\n    pass\n\n# Test\nprint(solution(9))  # Expected: [1, 3, 5, 7, 9]",
    "testCases": [
      {
        "input": "(9,)",
        "expected": "[1, 3, 5, 7, 9]"
      }
    ],
    "hints": [
      "Start at 1 and step by 2: `for (int i = 1; i <= n; i += 2)`."
    ],
    "approach": "Loop from 1 to n with a step of 2.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(n)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] getOddNumbers(int n) {\n        return new int[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.getOddNumbers(9)));\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] getOddNumbers(int n) {\n        int size = (n + 1) / 2;\n        int[] result = new int[size];\n        for (int i = 0; i < size; i++) {\n            result[i] = (i * 2) + 1;\n        }\n        return result;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Odd up to 9: \" + Arrays.toString(sol.getOddNumbers(9))); // [1, 3, 5, 7, 9]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [i for i in range(1, n + 1, 2)]\n\n# Test\nprint(solution(9))  # [1, 3, 5, 7, 9]",
    "intuitionEn": "Starting at 1 with step 2 guarantees generating the odd number sequence `2k + 1`.",
    "intuitionHi": "1 se shuru karke 2-2 aage badhne par sirf odd numbers aate hain.",
    "stepsEn": [
      "Loop from 1 to n with step 2.",
      "Collect and return."
    ],
    "stepsHi": [
      "1, 3, 5 karke loop chalayein."
    ],
    "id": 57
  },
  {
    "slug": "sum-of-even-numbers",
    "title": "Calculate Sum of Even Numbers up to N",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given an integer `n`, compute and return the sum of all even integers from 2 up to `n` (`2 + 4 + 6 + ...`).",
    "examples": [
      {
        "input": "n = 6",
        "output": "12",
        "explanation": "2 + 4 + 6 = 12."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 10⁴"
    ],
    "starterCode": "def solution(n):\n    # Return sum of even numbers up to n\n    pass\n\n# Test\nprint(solution(6))  # Expected: 12",
    "testCases": [
      {
        "input": "(6,)",
        "expected": "12"
      },
      {
        "input": "(10,)",
        "expected": "30"
      }
    ],
    "hints": [
      "Initialize `sum = 0`, while `i <= n`, add `sum += i` and `i += 2`."
    ],
    "approach": "Accumulate sum of even numbers.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int sumEven(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.sumEven(6)); // 12\n    }\n}",
    "javaSolution": "class Solution {\n    public int sumEven(int n) {\n        int sum = 0;\n        int i = 2;\n        while (i <= n) {\n            sum += i;\n            i += 2;\n        }\n        return sum;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Sum of even up to 6 : \" + sol.sumEven(6));  // 12\n        System.out.println(\"Sum of even up to 10: \" + sol.sumEven(10)); // 30\n    }\n}",
    "pythonSolution": "def solution(n):\n    total = 0\n    i = 2\n    while i <= n:\n        total += i\n        i += 2\n    return total\n\n# Test\nprint(solution(6))  # 12",
    "intuitionEn": "Even accumulation: repeatedly adding multiples of 2 to a running sum.",
    "intuitionHi": "Sum variable lekar har baar agla even number jodte jana.",
    "stepsEn": [
      "Start `sum = 0, i = 2`.",
      "While `i <= n`, add and increment `i += 2`."
    ],
    "stepsHi": [
      "`sum = 0` se shuru karein aur even numbers jodein."
    ],
    "id": 58
  },
  {
    "slug": "fibonacci-series-n-terms",
    "title": "Generate First N Terms of Fibonacci Series",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given an integer `n` (n ≥ 1), generate and return an array containing the first `n` terms of the Fibonacci sequence: `0, 1, 1, 2, 3, 5, 8, ...` where each term is the sum of the two preceding ones.",
    "examples": [
      {
        "input": "n = 5",
        "output": "[0, 1, 1, 2, 3]",
        "explanation": "First 5 Fibonacci terms."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 40"
    ],
    "starterCode": "def solution(n):\n    # Return first n Fibonacci numbers\n    pass\n\n# Test\nprint(solution(5))  # Expected: [0, 1, 1, 2, 3]",
    "testCases": [
      {
        "input": "(5,)",
        "expected": "[0, 1, 1, 2, 3]"
      },
      {
        "input": "(2,)",
        "expected": "[0, 1]"
      }
    ],
    "hints": [
      "Start with `0` and `1`, then each next element is `fib[i] = fib[i-1] + fib[i-2]`."
    ],
    "approach": "Initialize array and iteratively compute subsequent terms as the sum of the last two.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(n)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public int[] fibonacci(int n) {\n        return new int[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.fibonacci(5))); // [0, 1, 1, 2, 3]\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public int[] fibonacci(int n) {\n        int[] fib = new int[n];\n        if (n >= 1) fib[0] = 0;\n        if (n >= 2) fib[1] = 1;\n        for (int i = 2; i < n; i++) {\n            fib[i] = fib[i - 1] + fib[i - 2];\n        }\n        return fib;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Fibonacci 5 terms: \" + Arrays.toString(sol.fibonacci(5))); // [0, 1, 1, 2, 3]\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n == 1:\n        return [0]\n    fib = [0, 1]\n    for _ in range(2, n):\n        fib.append(fib[-1] + fib[-2])\n    return fib[:n]\n\n# Test\nprint(solution(5))  # [0, 1, 1, 2, 3]",
    "intuitionEn": "The Fibonacci recurrence `F(n) = F(n-1) + F(n-2)` builds a sequence where each number combines its two immediate predecessors.",
    "intuitionHi": "Fibonacci series me har number pichle do numbers ka jod hota hai: 0, 1, 1, 2, 3, 5...",
    "stepsEn": [
      "Set `fib[0] = 0, fib[1] = 1`.",
      "Loop from 2 to n-1 computing sum."
    ],
    "stepsHi": [
      "Pehle do terms 0 aur 1 set karein, fir pichle do ko jodte jayein."
    ],
    "id": 59
  },
  {
    "slug": "check-armstrong-number",
    "title": "Check if a Number is an Armstrong Number",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given a 3-digit integer `n`, determine whether it is an **Armstrong Number**.\n\nA 3-digit number is an Armstrong number if the sum of the cubes of its digits equals the number itself (e.g. `153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153`).",
    "examples": [
      {
        "input": "n = 153",
        "output": "true",
        "explanation": "1^3 + 5^3 + 3^3 = 153."
      },
      {
        "input": "n = 120",
        "output": "false",
        "explanation": "1^3 + 2^3 + 0^3 = 9 != 120."
      }
    ],
    "constraints": [
      "100 ≤ n ≤ 999"
    ],
    "starterCode": "def solution(n):\n    # Return True if Armstrong else False\n    pass\n\n# Test\nprint(solution(153))  # Expected: True",
    "testCases": [
      {
        "input": "(153,)",
        "expected": "True"
      },
      {
        "input": "(120,)",
        "expected": "False"
      },
      {
        "input": "(370,)",
        "expected": "True"
      }
    ],
    "hints": [
      "Extract digits using `% 10`, cube each digit and accumulate."
    ],
    "approach": "Extract each digit, cube it, sum them, and compare with original number.",
    "timeComplexity": "O(1)",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public boolean isArmstrong(int n) {\n        return false;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.isArmstrong(153)); // true\n    }\n}",
    "javaSolution": "class Solution {\n    public boolean isArmstrong(int n) {\n        int original = n;\n        int sumOfCubes = 0;\n        while (n > 0) {\n            int digit = n % 10;\n            sumOfCubes += (digit * digit * digit);\n            n /= 10;\n        }\n        return sumOfCubes == original;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"153 is Armstrong? \" + sol.isArmstrong(153)); // true\n        System.out.println(\"120 is Armstrong? \" + sol.isArmstrong(120)); // false\n        System.out.println(\"370 is Armstrong? \" + sol.isArmstrong(370)); // true\n    }\n}",
    "pythonSolution": "def solution(n):\n    original = n\n    sum_cubes = 0\n    while n > 0:\n        d = n % 10\n        sum_cubes += d ** 3\n        n //= 10\n    return sum_cubes == original\n\n# Test\nprint(solution(153))  # True\nprint(solution(120))  # False",
    "intuitionEn": "Narcissistic number property: self-producing number where sum of digits raised to power of total digits reproduces the original value.",
    "intuitionHi": "Digits ka cube karke jodne par agar wahi number mile to wo Armstrong number hota hai.",
    "stepsEn": [
      "Extract each digit.",
      "Add cube of digit to sum.",
      "Compare with original."
    ],
    "stepsHi": [
      "Har digit ka cube jodkar original number se check karein."
    ],
    "id": 60
  },
  {
    "slug": "find-all-factors",
    "title": "Find All Factors (Divisors) of a Number",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "for loop",
    "phase": 1,
    "description": "Given a positive integer `n`, find and return all its positive divisors in ascending order.",
    "examples": [
      {
        "input": "n = 12",
        "output": "[1, 2, 3, 4, 6, 12]",
        "explanation": "12 is divisible by 1, 2, 3, 4, 6, 12."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 10⁴"
    ],
    "starterCode": "def solution(n):\n    # Return list of factors of n\n    pass\n\n# Test\nprint(solution(12))  # Expected: [1, 2, 3, 4, 6, 12]",
    "testCases": [
      {
        "input": "(12,)",
        "expected": "[1, 2, 3, 4, 6, 12]"
      }
    ],
    "hints": [
      "Loop `i` from 1 to n: if `n % i == 0`, add `i` to factors list."
    ],
    "approach": "Check divisibility for all numbers from 1 to n.",
    "timeComplexity": "O(n)",
    "spaceComplexity": "O(factors)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public List<Integer> findFactors(int n) {\n        return new ArrayList<>();\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.findFactors(12)); // [1, 2, 3, 4, 6, 12]\n    }\n}",
    "javaSolution": "import java.util.ArrayList;\nimport java.util.List;\n\nclass Solution {\n    public List<Integer> findFactors(int n) {\n        List<Integer> factors = new ArrayList<>();\n        for (int i = 1; i <= n; i++) {\n            if (n % i == 0) {\n                factors.add(i);\n            }\n        }\n        return factors;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Factors of 12: \" + sol.findFactors(12)); // [1, 2, 3, 4, 6, 12]\n    }\n}",
    "pythonSolution": "def solution(n):\n    return [i for i in range(1, n + 1) if n % i == 0]\n\n# Test\nprint(solution(12))  # [1, 2, 3, 4, 6, 12]",
    "intuitionEn": "A factor of n is an integer that divides n leaving zero remainder.",
    "intuitionHi": "1 se n tak check karein: jo bhi number n ko poora divide kare wo uska factor hai.",
    "stepsEn": [
      "Loop `i` from 1 to n.",
      "If `n % i == 0`, include `i`."
    ],
    "stepsHi": [
      "1 se n tak loop chalakar factors collect karein."
    ],
    "id": 61
  },
  {
    "slug": "lcm-of-two-numbers",
    "title": "Find LCM (Least Common Multiple) of Two Numbers",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given two positive integers `a` and `b`, find their **LCM** using the fundamental property: `LCM(a, b) = (a * b) / GCD(a, b)`.",
    "examples": [
      {
        "input": "a = 4, b = 6",
        "output": "12",
        "explanation": "Multiples of 4: 4,8,12... Multiples of 6: 6,12... Lowest common is 12."
      }
    ],
    "constraints": [
      "1 ≤ a, b ≤ 10⁴"
    ],
    "starterCode": "def solution(a, b):\n    # Return LCM of a and b\n    pass\n\n# Test\nprint(solution(4, 6))  # Expected: 12",
    "testCases": [
      {
        "input": "(4, 6)",
        "expected": "12"
      },
      {
        "input": "(5, 7)",
        "expected": "35"
      }
    ],
    "hints": [
      "Compute GCD first, then `LCM = (a * b) / gcd`."
    ],
    "approach": "Use Euclidean algorithm to find GCD and divide product of a and b by GCD.",
    "timeComplexity": "O(log(min(a, b)))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int findLCM(int a, int b) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.findLCM(4, 6)); // 12\n    }\n}",
    "javaSolution": "class Solution {\n    // Helper to find GCD using Euclidean algorithm\n    private int gcd(int a, int b) {\n        while (b != 0) {\n            int rem = a % b;\n            a = b;\n            b = rem;\n        }\n        return a;\n    }\n\n    public int findLCM(int a, int b) {\n        return (a * b) / gcd(a, b);\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"LCM of (4, 6): \" + sol.findLCM(4, 6)); // 12\n        System.out.println(\"LCM of (5, 7): \" + sol.findLCM(5, 7)); // 35\n    }\n}",
    "pythonSolution": "def gcd(a, b):\n    while b:\n        a, b = b, a % b\n    return a\n\ndef solution(a, b):\n    return (a * b) // gcd(a, b)\n\n# Test\nprint(solution(4, 6))  # 12",
    "intuitionEn": "Fundamental arithmetic relationship: product of two numbers equals product of their GCD and LCM (`a * b = GCD * LCM`).",
    "intuitionHi": "Dono numbers ka product unke LCM aur HCF ke product ke barabar hota hai.",
    "stepsEn": [
      "Compute `gcd = GCD(a, b)`.",
      "Return `(a * b) / gcd`."
    ],
    "stepsHi": [
      "Pehle GCD nikalein, fir `(a * b) / gcd` karein."
    ],
    "id": 62
  },
  {
    "slug": "product-of-digits",
    "title": "Calculate Product of Digits of an Integer",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "while loop",
    "phase": 1,
    "description": "Given a non-negative integer `n`, compute and return the product of all its individual digits (e.g. for `234`, product is `2 * 3 * 4 = 24`). For `n = 0`, return `0`.",
    "examples": [
      {
        "input": "n = 234",
        "output": "24",
        "explanation": "2 * 3 * 4 = 24."
      },
      {
        "input": "n = 0",
        "output": "0",
        "explanation": "0 has product 0."
      }
    ],
    "constraints": [
      "0 ≤ n ≤ 10⁹"
    ],
    "starterCode": "def solution(n):\n    # Return product of digits\n    pass\n\n# Test\nprint(solution(234))  # Expected: 24",
    "testCases": [
      {
        "input": "(234,)",
        "expected": "24"
      },
      {
        "input": "(0,)",
        "expected": "0"
      }
    ],
    "hints": [
      "While `n > 0`, extract `n % 10`, multiply with prod, and `n /= 10`."
    ],
    "approach": "Extract each digit using modulo and accumulate product.",
    "timeComplexity": "O(log10(n))",
    "spaceComplexity": "O(1)",
    "javaStarterCode": "class Solution {\n    public int productDigits(int n) {\n        return 0;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(sol.productDigits(234)); // 24\n    }\n}",
    "javaSolution": "class Solution {\n    public int productDigits(int n) {\n        if (n == 0) return 0;\n        int prod = 1;\n        while (n > 0) {\n            prod *= (n % 10);\n            n /= 10;\n        }\n        return prod;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"Product of digits in 234: \" + sol.productDigits(234)); // 24\n        System.out.println(\"Product of digits in 0  : \" + sol.productDigits(0));   // 0\n    }\n}",
    "pythonSolution": "def solution(n):\n    if n == 0:\n        return 0\n    prod = 1\n    while n > 0:\n        prod *= (n % 10)\n        n //= 10\n    return prod\n\n# Test\nprint(solution(234))  # 24",
    "intuitionEn": "Extracting digits sequentially and accumulating into a multiplicative product.",
    "intuitionHi": "Har baar last digit nikal kar product me multiply karte jayein.",
    "stepsEn": [
      "Handle 0.",
      "Multiply `prod *= (n % 10)`.",
      "Divide `n /= 10`."
    ],
    "stepsHi": [
      "Last digit nikal kar multiply karein."
    ],
    "id": 63
  },
  {
    "slug": "print-square-star-pattern",
    "title": "Print a Square Star Pattern of Size N (N x N Grid)",
    "difficulty": "Easy",
    "topic": "Loops",
    "pattern": "nested loops",
    "phase": 1,
    "description": "Given an integer `n`, return an array of `n` strings where each string contains `n` asterisks (`*`), representing an `N x N` square grid.",
    "examples": [
      {
        "input": "n = 3",
        "output": "[\"***\", \"***\", \"***\"]",
        "explanation": "3 rows with 3 stars each."
      }
    ],
    "constraints": [
      "1 ≤ n ≤ 20"
    ],
    "starterCode": "def solution(n):\n    # Return list of n star strings\n    pass\n\n# Test\nprint(solution(3))  # Expected: ['***', '***', '***']",
    "testCases": [
      {
        "input": "(3,)",
        "expected": "['***', '***', '***']"
      }
    ],
    "hints": [
      "Use nested loops: outer loop for rows, inner loop to build row string."
    ],
    "approach": "Outer loop iterates `n` rows, inner loop appends `n` stars.",
    "timeComplexity": "O(n²)",
    "spaceComplexity": "O(n²)",
    "javaStarterCode": "import java.util.*;\n\nclass Solution {\n    public String[] printSquarePattern(int n) {\n        return new String[0];\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(Arrays.toString(sol.printSquarePattern(3)));\n    }\n}",
    "javaSolution": "import java.util.Arrays;\n\nclass Solution {\n    public String[] printSquarePattern(int n) {\n        String[] grid = new String[n];\n        for (int i = 0; i < n; i++) {\n            StringBuilder row = new StringBuilder();\n            for (int j = 0; j < n; j++) {\n                row.append('*');\n            }\n            grid[i] = row.toString();\n        }\n        return grid;\n    }\n\n    public static void main(String[] args) {\n        Solution sol = new Solution();\n        System.out.println(\"3x3 square pattern: \" + Arrays.toString(sol.printSquarePattern(3)));\n    }\n}",
    "pythonSolution": "def solution(n):\n    return ['*' * n for _ in range(n)]\n\n# Test\nprint(solution(3))  # ['***', '***', '***']",
    "intuitionEn": "Nested 2D iteration: outer loop controls row index, inner loop controls column index.",
    "intuitionHi": "Nested loop: Bahar wala loop rows control karta hai aur andar wala columns.",
    "stepsEn": [
      "Outer loop `i` from 0 to n-1.",
      "Inner loop builds string of n stars.",
      "Return grid."
    ],
    "stepsHi": [
      "Nested loop se N x N stars generate karein."
    ],
    "id": 64
  }
];
