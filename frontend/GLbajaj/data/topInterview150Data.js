/**
 * LeetCode Top Interview 150 Study Plan Data
 * Complete catalog of 150 essential interview problems categorized into 23 topics,
 * with full editorial solutions, Python code, time/space complexity, and company tags.
 */

export const TOP_INTERVIEW_CATEGORIES = [
  'Array / String',
  'Two Pointers',
  'Sliding Window',
  'Matrix',
  'Hashmap',
  'Intervals',
  'Stack',
  'Linked List',
  'Binary Tree General',
  'Binary Tree BFS',
  'Binary Search Tree',
  'Graph General',
  'Graph BFS',
  'Trie',
  'Backtracking',
  'Divide & Conquer',
  "Kadane's Algorithm",
  'Binary Search',
  'Heap',
  'Bit Manipulation',
  'Math',
  '1D DP',
  'Multidimensional DP'
];

export const TOP_INTERVIEW_150 = [
  // ── 1. Array / String (24 problems) ─────────────────────────────────
  {
    id: 1,
    title: 'Merge Sorted Array',
    slug: 'merge-sorted-array',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta', 'Apple'],
    description: 'You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.\n\nMerge nums1 and nums2 into a single array sorted in non-decreasing order inside nums1 in-place.',
    approach: 'Start from the end of both arrays (three-pointer technique). Compare nums1[p1] and nums2[p2] and place the larger element at nums1[p]. This avoids overwriting elements in nums1.',
    code: `def merge(nums1, m, nums2, n):
    p1 = m - 1
    p2 = n - 1
    p = m + n - 1
    
    while p2 >= 0:
        if p1 >= 0 and nums1[p1] > nums2[p2]:
            nums1[p] = nums1[p1]
            p1 -= 1
        else:
            nums1[p] = nums2[p2]
            p2 -= 1
        p -= 1
    return nums1`,
    timeComplexity: 'O(m + n)',
    spaceComplexity: 'O(1) in-place',
    editorialUrl: 'https://leetcode.com/problems/merge-sorted-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 2,
    title: 'Remove Element',
    slug: 'remove-element',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Adobe', 'Microsoft'],
    description: 'Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.',
    approach: 'Two-pointer technique: Maintain a pointer k for placing valid elements. When nums[i] != val, assign nums[k] = nums[i] and increment k.',
    code: `def removeElement(nums, val):
    k = 0
    for i in range(len(nums)):
        if nums[i] != val:
            nums[k] = nums[i]
            k += 1
    return k`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/remove-element/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 3,
    title: 'Remove Duplicates from Sorted Array',
    slug: 'remove-duplicates-from-sorted-array',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Microsoft', 'Meta', 'Google', 'Apple'],
    description: 'Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same.',
    approach: 'Since array is already sorted, all duplicates are adjacent. Use a slow pointer k for placing unique elements. Compare current element with nums[k-1].',
    code: `def removeDuplicates(nums):
    if not nums:
        return 0
    k = 1
    for i in range(1, len(nums)):
        if nums[i] != nums[k - 1]:
            nums[k] = nums[i]
            k += 1
    return k`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/remove-duplicates-from-sorted-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 4,
    title: 'Remove Duplicates from Sorted Array II',
    slug: 'remove-duplicates-from-sorted-array-ii',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Meta', 'Uber'],
    description: 'Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element appears at most twice.',
    approach: 'Allow up to 2 duplicates by comparing nums[i] with nums[k - 2]. If nums[i] > nums[k - 2], copy it to nums[k] and increment k.',
    code: `def removeDuplicatesII(nums):
    if len(nums) <= 2:
        return len(nums)
    k = 2
    for i in range(2, len(nums)):
        if nums[i] != nums[k - 2]:
            nums[k] = nums[i]
            k += 1
    return k`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 5,
    title: 'Majority Element',
    slug: 'majority-element',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Adobe', 'Apple'],
    description: 'Given an array nums of size n, return the majority element. The majority element is the element that appears more than ⌊n / 2⌋ times.',
    approach: "Boyer-Moore Voting Algorithm: Keep candidate and count. If count == 0, pick current num as candidate. If num == candidate, increment count, else decrement.",
    code: `def majorityElement(nums):
    candidate = None
    count = 0
    for num in nums:
        if count == 0:
            candidate = num
        count += (1 if num == candidate else -1)
    return candidate`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/majority-element/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 6,
    title: 'Rotate Array',
    slug: 'rotate-array',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Meta', 'Google', 'Bloomberg'],
    description: 'Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.',
    approach: 'Three-reversal algorithm: 1) Reverse the entire array. 2) Reverse first k elements. 3) Reverse remaining n-k elements.',
    code: `def rotate(nums, k):
    n = len(nums)
    k %= n
    def reverse(l, r):
        while l < r:
            nums[l], nums[r] = nums[r], nums[l]
            l += 1
            r -= 1
    reverse(0, n - 1)
    reverse(0, k - 1)
    reverse(k, n - 1)
    return nums`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/rotate-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 7,
    title: 'Best Time to Buy and Sell Stock',
    slug: 'best-time-to-buy-and-sell-stock',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta', 'Goldman Sachs'],
    description: 'You are given an array prices where prices[i] is the price of a given stock on the ith day. You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.',
    approach: 'Single-pass greedy: Maintain min_price seen so far and max_profit. For each price, profit = price - min_price.',
    code: `def maxProfit(prices):
    min_price = float('inf')
    max_profit = 0
    for price in prices:
        if price < min_price:
            min_price = price
        elif price - min_price > max_profit:
            max_profit = price - min_price
    return max_profit`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/best-time-to-buy-and-sell-stock/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 8,
    title: 'Best Time to Buy and Sell Stock II',
    slug: 'best-time-to-buy-and-sell-stock-ii',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Bloomberg', 'Google', 'Meta'],
    description: 'You may decide to buy and/or sell the stock each day. You can only hold at most one share of the stock at any time. However, you can buy it and then immediately sell it on the same day. Find and return the maximum profit.',
    approach: 'Greedy approach: Capture every positive price difference between consecutive days (prices[i] - prices[i-1] > 0).',
    code: `def maxProfitII(prices):
    profit = 0
    for i in range(1, len(prices)):
        if prices[i] > prices[i - 1]:
            profit += prices[i] - prices[i - 1]
    return profit`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 9,
    title: 'Jump Game',
    slug: 'jump-game',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta', 'Apple'],
    description: 'You are given an integer array nums. You are initially positioned at the array\'s first index, and each element in the array represents your maximum jump length at that position. Return true if you can reach the last index.',
    approach: 'Greedy max reachable index: Track the maximum index reachable so far. If current index i > max_reach, return False.',
    code: `def canJump(nums):
    max_reach = 0
    for i, jump in enumerate(nums):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + jump)
    return True`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/jump-game/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 10,
    title: 'Jump Game II',
    slug: 'jump-game-ii',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].',
    approach: 'BFS-style greedy: Track current jump range [current_end] and the farthest point reachable within this jump [farthest]. When i reaches current_end, increment jumps.',
    code: `def jump(nums):
    jumps = 0
    current_end = 0
    farthest = 0
    for i in range(len(nums) - 1):
        farthest = max(farthest, i + nums[i])
        if i == current_end:
            jumps += 1
            current_end = farthest
    return jumps`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/jump-game-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 11,
    title: 'H-Index',
    slug: 'h-index',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Google', 'Meta', 'Amazon'],
    description: 'Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return the researcher\'s h-index.',
    approach: 'Sort citations descending. Find the maximum i such that citations[i] >= i + 1.',
    code: `def hIndex(citations):
    citations.sort(reverse=True)
    h = 0
    for i, c in enumerate(citations):
        if c >= i + 1:
            h = i + 1
        else:
            break
    return h`,
    timeComplexity: 'O(n log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/h-index/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 12,
    title: 'Insert Delete GetRandom O(1)',
    slug: 'insert-delete-getrandom-o1',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'LinkedIn', 'Uber'],
    description: 'Implement the RandomizedSet class with insert, remove, and getRandom all running in average O(1) time complexity.',
    approach: 'Combine dynamic array (list) for O(1) random access and hash map (dict) for O(1) index lookups. On delete, swap target with last element.',
    code: `import random

class RandomizedSet:
    def __init__(self):
        self.vals = []
        self.indices = {}

    def insert(self, val: int) -> bool:
        if val in self.indices:
            return False
        self.indices[val] = len(self.vals)
        self.vals.append(val)
        return True

    def remove(self, val: int) -> bool:
        if val not in self.indices:
            return False
        idx = self.indices[val]
        last_val = self.vals[-1]
        self.vals[idx] = last_val
        self.indices[last_val] = idx
        self.vals.pop()
        del self.indices[val]
        return True

    def getRandom(self) -> int:
        return random.choice(self.vals)`,
    timeComplexity: 'O(1) average for all operations',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/insert-delete-getrandom-o1/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 13,
    title: 'Product of Array Except Self',
    slug: 'product-of-array-except-self',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Meta', 'Google', 'Microsoft', 'Apple'],
    description: 'Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i] without using division in O(n) time.',
    approach: 'Prefix and Suffix products: Calculate left prefix products into output array, then maintain a running right suffix product in a variable.',
    code: `def productExceptSelf(nums):
    n = len(nums)
    res = [1] * n
    
    prefix = 1
    for i in range(n):
        res[i] = prefix
        prefix *= nums[i]
        
    suffix = 1
    for i in range(n - 1, -1, -1):
        res[i] *= suffix
        suffix *= nums[i]
        
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1) auxiliary',
    editorialUrl: 'https://leetcode.com/problems/product-of-array-except-self/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 14,
    title: 'Gas Station',
    slug: 'gas-station',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Bloomberg'],
    description: 'There are n gas stations along a circular route. Given gas and cost arrays, return the starting gas station\'s index if you can travel around the circuit once in the clockwise direction, otherwise return -1.',
    approach: 'If sum(gas) < sum(cost), impossible. Otherwise, whenever running tank < 0, start must be at station i + 1.',
    code: `def canCompleteCircuit(gas, cost):
    if sum(gas) < sum(cost):
        return -1
    total_tank = 0
    start = 0
    for i in range(len(gas)):
        total_tank += gas[i] - cost[i]
        if total_tank < 0:
            start = i + 1
            total_tank = 0
    return start`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/gas-station/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 15,
    title: 'Candy',
    slug: 'candy',
    category: 'Array / String',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google', 'Microsoft', 'Adobe'],
    description: 'There are n children standing in a line with ratings. Each child must have at least one candy. Children with a higher rating get more candies than their neighbors. Return the minimum number of candies.',
    approach: 'Two passes: Left-to-right pass ensuring candies[i] > candies[i-1] when ratings[i] > ratings[i-1]. Right-to-left pass ensuring candies[i] > candies[i+1] when ratings[i] > ratings[i+1].',
    code: `def candy(ratings):
    n = len(ratings)
    candies = [1] * n
    for i in range(1, n):
        if ratings[i] > ratings[i - 1]:
            candies[i] = candies[i - 1] + 1
    for i in range(n - 2, -1, -1):
        if ratings[i] > ratings[i + 1]:
            candies[i] = max(candies[i], candies[i + 1] + 1)
    return sum(candies)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/candy/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 16,
    title: 'Trapping Rain Water',
    slug: 'trapping-rain-water',
    category: 'Array / String',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google', 'Meta', 'Goldman Sachs', 'Apple'],
    description: 'Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.',
    approach: 'Two pointers (left, right) with max_left and max_right. The trapped water at each bar is determined by the shorter bound.',
    code: `def trap(height):
    if not height:
        return 0
    l, r = 0, len(height) - 1
    max_l, max_r = height[l], height[r]
    water = 0
    while l < r:
        if max_l <= max_r:
            l += 1
            max_l = max(max_l, height[l])
            water += max_l - height[l]
        else:
            r -= 1
            max_r = max(max_r, height[r])
            water += max_r - height[r]
    return water`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/trapping-rain-water/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 17,
    title: 'Roman to Integer',
    slug: 'roman-to-integer',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Apple', 'Meta'],
    description: 'Given a roman numeral, convert it to an integer.',
    approach: 'Map symbols to values. If current symbol is smaller than the next symbol (e.g. IV), subtract it; otherwise add it.',
    code: `def romanToInt(s):
    vals = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    total = 0
    n = len(s)
    for i in range(n):
        if i + 1 < n and vals[s[i]] < vals[s[i + 1]]:
            total -= vals[s[i]]
        else:
            total += vals[s[i]]
    return total`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/roman-to-integer/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 18,
    title: 'Integer to Roman',
    slug: 'integer-to-roman',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Bloomberg'],
    description: 'Given an integer, convert it to a roman numeral.',
    approach: 'Greedy decomposition using sorted list of standard values and subtractive pairs (1000, 900, 500, 400, ...).',
    code: `def intToRoman(num):
    val_map = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
    ]
    res = []
    for val, sym in val_map:
        if num == 0:
            break
        count, num = divmod(num, val)
        res.append(sym * count)
    return ''.join(res)`,
    timeComplexity: 'O(1)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/integer-to-roman/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 19,
    title: 'Length of Last Word',
    slug: 'length-of-last-word',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Apple', 'Google'],
    description: 'Given a string s consisting of words and spaces, return the length of the last word in the string.',
    approach: 'Strip trailing whitespace and count characters backwards until the next space.',
    code: `def lengthOfLastWord(s):
    s = s.rstrip()
    length = 0
    for ch in reversed(s):
        if ch == ' ':
            break
        length += 1
    return length`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/length-of-last-word/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 20,
    title: 'Longest Common Prefix',
    slug: 'longest-common-prefix',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Adobe'],
    description: 'Write a function to find the longest common prefix string amongst an array of strings. If there is no common prefix, return an empty string "".',
    approach: 'Horizontal scanning: Start with strs[0] as prefix and trim it until it matches the start of every string.',
    code: `def longestCommonPrefix(strs):
    if not strs:
        return ""
    prefix = strs[0]
    for s in strs[1:]:
        while not s.startswith(prefix):
            prefix = prefix[:-1]
            if not prefix:
                return ""
    return prefix`,
    timeComplexity: 'O(S) where S is sum of all characters',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/longest-common-prefix/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 21,
    title: 'Reverse Words in a String',
    slug: 'reverse-words-in-a-string',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Apple'],
    description: 'Given an input string s, reverse the order of the words.',
    approach: 'Split string by whitespace to auto-handle multiple consecutive spaces, reverse list of tokens, and rejoin with single space.',
    code: `def reverseWords(s):
    return ' '.join(s.strip().split()[::-1])`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/reverse-words-in-a-string/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 22,
    title: 'Zigzag Conversion',
    slug: 'zigzag-conversion',
    category: 'Array / String',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows. Read line by line.',
    approach: 'Simulate the ball bouncing between row 0 and row numRows - 1 using a step variable (+1 or -1).',
    code: `def convert(s, numRows):
    if numRows == 1 or numRows >= len(s):
        return s
    rows = [''] * numRows
    cur_row = 0
    going_down = False
    for ch in s:
        rows[cur_row] += ch
        if cur_row == 0 or cur_row == numRows - 1:
            going_down = not going_down
        cur_row += 1 if going_down else -1
    return ''.join(rows)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/zigzag-conversion/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 23,
    title: 'Find the Index of the First Occurrence in a String',
    slug: 'find-the-index-of-the-first-occurrence-in-a-string',
    category: 'Array / String',
    difficulty: 'Easy',
    companies: ['Amazon', 'Microsoft', 'Meta', 'Google'],
    description: 'Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.',
    approach: 'Sliding window substring check of length len(needle), or KMP / Python find().',
    code: `def strStr(haystack, needle):
    if not needle:
        return 0
    n, m = len(haystack), len(needle)
    for i in range(n - m + 1):
        if haystack[i:i + m] == needle:
            return i
    return -1`,
    timeComplexity: 'O((n - m + 1) * m)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 24,
    title: 'Text Justification',
    slug: 'text-justification',
    category: 'Array / String',
    difficulty: 'Hard',
    companies: ['Google', 'Meta', 'Amazon', 'LinkedIn', 'Apple'],
    description: 'Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.',
    approach: 'Greedy word packing: Fill each line until adding another word exceeds maxWidth. Distribute extra spaces evenly between words, with leftover spaces on the left.',
    code: `def fullJustify(words, maxWidth):
    res, cur, num_of_letters = [], [], 0
    for w in words:
        if num_of_letters + len(w) + len(cur) > maxWidth:
            for i in range(maxWidth - num_of_letters):
                cur[i % (len(cur) - 1 or 1)] += ' '
            res.append(''.join(cur))
            cur, num_of_letters = [], 0
        cur.append(w)
        num_of_letters += len(w)
    res.append(' '.join(cur).ljust(maxWidth))
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(maxWidth)',
    editorialUrl: 'https://leetcode.com/problems/text-justification/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 2. Two Pointers (5 problems) ────────────────────────────────────
  {
    id: 25,
    title: 'Valid Palindrome',
    slug: 'valid-palindrome',
    category: 'Two Pointers',
    difficulty: 'Easy',
    companies: ['Meta', 'Amazon', 'Microsoft', 'Google'],
    description: 'A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward.',
    approach: 'Two pointers inward: Skip non-alphanumeric characters using isalnum(), then compare lowercased characters.',
    code: `def isPalindrome(s):
    l, r = 0, len(s) - 1
    while l < r:
        while l < r and not s[l].isalnum():
            l += 1
        while l < r and not s[r].isalnum():
            r -= 1
        if s[l].lower() != s[r].lower():
            return False
        l += 1
        r -= 1
    return True`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/valid-palindrome/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 26,
    title: 'Is Subsequence',
    slug: 'is-subsequence',
    category: 'Two Pointers',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Meta'],
    description: 'Given two strings s and t, return true if s is a subsequence of t, or false otherwise.',
    approach: 'Two pointers: Advance pointer in s only when character matches current character in t.',
    code: `def isSubsequence(s, t):
    i = 0
    for ch in t:
        if i < len(s) and s[i] == ch:
            i += 1
    return i == len(s)`,
    timeComplexity: 'O(len(t))',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/is-subsequence/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 27,
    title: 'Two Sum II - Input Array Is Sorted',
    slug: 'two-sum-ii-input-array-is-sorted',
    category: 'Two Pointers',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number.',
    approach: 'Two pointers at ends (l = 0, r = n - 1). If sum < target, l += 1; if sum > target, r -= 1.',
    code: `def twoSumII(numbers, target):
    l, r = 0, len(numbers) - 1
    while l < r:
        s = numbers[l] + numbers[r]
        if s == target:
            return [l + 1, r + 1]
        elif s < target:
            l += 1
        else:
            r -= 1
    return []`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 28,
    title: 'Container With Most Water',
    slug: 'container-with-most-water',
    category: 'Two Pointers',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Goldman Sachs'],
    description: 'Find two lines that together with the x-axis form a container, such that the container contains the most water.',
    approach: 'Two pointers: Area is min(h[l], h[r]) * (r - l). Move the pointer with smaller height inward to find a taller line.',
    code: `def maxArea(height):
    l, r = 0, len(height) - 1
    max_w = 0
    while l < r:
        max_w = max(max_w, min(height[l], height[r]) * (r - l))
        if height[l] < height[r]:
            l += 1
        else:
            r -= 1
    return max_w`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/container-with-most-water/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 29,
    title: '3Sum',
    slug: '3sum',
    category: 'Two Pointers',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple'],
    description: 'Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0 without duplicates.',
    approach: 'Sort nums, iterate i and use Two Pointers for (j, k). Skip duplicates for both i, j, and k.',
    code: `def threeSum(nums):
    nums.sort()
    res = []
    n = len(nums)
    for i in range(n - 2):
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        l, r = i + 1, n - 1
        while l < r:
            s = nums[i] + nums[l] + nums[r]
            if s == 0:
                res.append([nums[i], nums[l], nums[r]])
                while l < r and nums[l] == nums[l + 1]:
                    l += 1
                while l < r and nums[r] == nums[r - 1]:
                    r -= 1
                l += 1
                r -= 1
            elif s < 0:
                l += 1
            else:
                r -= 1
    return res`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(1) auxiliary',
    editorialUrl: 'https://leetcode.com/problems/3sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 3. Sliding Window (4 problems) ──────────────────────────────────
  {
    id: 30,
    title: 'Minimum Size Subarray Sum',
    slug: 'minimum-size-subarray-sum',
    category: 'Sliding Window',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target.',
    approach: 'Expand right pointer to accumulate sum. When sum >= target, contract left pointer while updating min length.',
    code: `def minSubArrayLen(target, nums):
    l = 0
    cur_sum = 0
    min_len = float('inf')
    for r in range(len(nums)):
        cur_sum += nums[r]
        while cur_sum >= target:
            min_len = min(min_len, r - l + 1)
            cur_sum -= nums[l]
            l += 1
    return 0 if min_len == float('inf') else min_len`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/minimum-size-subarray-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 31,
    title: 'Longest Substring Without Repeating Characters',
    slug: 'longest-substring-without-repeating-characters',
    category: 'Sliding Window',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta', 'Apple'],
    description: 'Given a string s, find the length of the longest substring without repeating characters.',
    approach: 'Sliding window with hash map storing last seen index of each char: If char in map and >= left, move left = map[char] + 1.',
    code: `def lengthOfLongestSubstring(s):
    seen = {}
    l = 0
    max_len = 0
    for r, ch in enumerate(s):
        if ch in seen and seen[ch] >= l:
            l = seen[ch] + 1
        seen[ch] = r
        max_len = max(max_len, r - l + 1)
    return max_len`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(min(n, m)) where m is alphabet size',
    editorialUrl: 'https://leetcode.com/problems/longest-substring-without-repeating-characters/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 32,
    title: 'Substring with Concatenation of All Words',
    slug: 'substring-with-concatenation-of-all-words',
    category: 'Sliding Window',
    difficulty: 'Hard',
    companies: ['Google', 'Amazon', 'Meta'],
    description: 'Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.',
    approach: 'Sliding window with word length step size, comparing frequency maps of words.',
    code: `from collections import Counter

def findSubstring(s, words):
    if not s or not words:
        return []
    word_len = len(words[0])
    word_count = len(words)
    total_len = word_len * word_count
    word_map = Counter(words)
    res = []
    
    for i in range(word_len):
        l = i
        cur_map = Counter()
        count = 0
        for r in range(i, len(s) - word_len + 1, word_len):
            w = s[r:r + word_len]
            if w in word_map:
                cur_map[w] += 1
                count += 1
                while cur_map[w] > word_map[w]:
                    left_w = s[l:l + word_len]
                    cur_map[left_w] -= 1
                    count -= 1
                    l += word_len
                if count == word_count:
                    res.append(l)
            else:
                cur_map.clear()
                count = 0
                l = r + word_len
    return res`,
    timeComplexity: 'O(n * word_len)',
    spaceComplexity: 'O(k * word_len)',
    editorialUrl: 'https://leetcode.com/problems/substring-with-concatenation-of-all-words/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 33,
    title: 'Minimum Window Substring',
    slug: 'minimum-window-substring',
    category: 'Sliding Window',
    difficulty: 'Hard',
    companies: ['Meta', 'Google', 'Amazon', 'Microsoft', 'Uber'],
    description: 'Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window.',
    approach: 'Sliding window with required characters counter and "formed" match counter. Contract left pointer whenever window is valid.',
    code: `from collections import Counter

def minWindow(s, t):
    if not s or not t:
        return ""
    need = Counter(t)
    required = len(need)
    window = {}
    formed = 0
    ans = (float('inf'), None, None)
    l = 0
    
    for r, ch in enumerate(s):
        window[ch] = window.get(ch, 0) + 1
        if ch in need and window[ch] == need[ch]:
            formed += 1
        while l <= r and formed == required:
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)
            window[s[l]] -= 1
            if s[l] in need and window[s[l]] < need[s[l]]:
                formed -= 1
            l += 1
            
    return "" if ans[0] == float('inf') else s[ans[1]:ans[2] + 1]`,
    timeComplexity: 'O(|s| + |t|)',
    spaceComplexity: 'O(|s| + |t|)',
    editorialUrl: 'https://leetcode.com/problems/minimum-window-substring/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 4. Matrix (5 problems) ──────────────────────────────────────────
  {
    id: 34,
    title: 'Valid Sudoku',
    slug: 'valid-sudoku',
    category: 'Matrix',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Apple', 'Uber'],
    description: 'Determine if a 9 x 9 Sudoku board is valid according to standard rules.',
    approach: 'Use sets to track digits in each row, col, and 3x3 sub-box (box_idx = (r // 3, c // 3)).',
    code: `def isValidSudoku(board):
    rows = [set() for _ in range(9)]
    cols = [set() for _ in range(9)]
    boxes = [set() for _ in range(9)]
    for r in range(9):
        for c in range(9):
            val = board[r][c]
            if val == '.':
                continue
            b = (r // 3) * 3 + (c // 3)
            if val in rows[r] or val in cols[c] or val in boxes[b]:
                return False
            rows[r].add(val)
            cols[c].add(val)
            boxes[b].add(val)
    return True`,
    timeComplexity: 'O(1) (fixed 81 cells)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/valid-sudoku/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 35,
    title: 'Spiral Matrix',
    slug: 'spiral-matrix',
    category: 'Matrix',
    difficulty: 'Medium',
    companies: ['Microsoft', 'Amazon', 'Google', 'Apple'],
    description: 'Given an m x n matrix, return all elements of the matrix in spiral order.',
    approach: 'Simulate four boundary pointers: top, bottom, left, right. Traverse right, down, left, up while shrinking boundaries.',
    code: `def spiralOrder(matrix):
    res = []
    top, bottom = 0, len(matrix) - 1
    left, right = 0, len(matrix[0]) - 1
    while top <= bottom and left <= right:
        for c in range(left, right + 1):
            res.append(matrix[top][c])
        top += 1
        for r in range(top, bottom + 1):
            res.append(matrix[r][right])
        right -= 1
        if top <= bottom:
            for c in range(right, left - 1, -1):
                res.append(matrix[bottom][c])
            bottom -= 1
        if left <= right:
            for r in range(bottom, top - 1, -1):
                res.append(matrix[r][left])
            left += 1
    return res`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(1) auxiliary',
    editorialUrl: 'https://leetcode.com/problems/spiral-matrix/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 36,
    title: 'Rotate Image',
    slug: 'rotate-image',
    category: 'Matrix',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise) in-place.',
    approach: 'Transpose the matrix (swap matrix[i][j] with matrix[j][i]), then reverse each row.',
    code: `def rotateMatrix(matrix):
    n = len(matrix)
    # Transpose
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    # Reverse each row
    for row in matrix:
        row.reverse()`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(1) in-place',
    editorialUrl: 'https://leetcode.com/problems/rotate-image/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 37,
    title: 'Set Matrix Zeroes',
    slug: 'set-matrix-zeroes',
    category: 'Matrix',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Meta', 'Google'],
    description: 'Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0\'s in-place.',
    approach: 'Use the first row and first column as markers, with a separate boolean flag for the first column/row.',
    code: `def setZeroes(matrix):
    m, n = len(matrix), len(matrix[0])
    first_row_zero = any(matrix[0][c] == 0 for c in range(n))
    first_col_zero = any(matrix[r][0] == 0 for r in range(m))
    
    for r in range(1, m):
        for c in range(1, n):
            if matrix[r][c] == 0:
                matrix[r][0] = matrix[0][c] = 0
                
    for r in range(1, m):
        for c in range(1, n):
            if matrix[r][0] == 0 or matrix[0][c] == 0:
                matrix[r][c] = 0
                
    if first_row_zero:
        for c in range(n):
            matrix[0][c] = 0
    if first_col_zero:
        for r in range(m):
            matrix[r][0] = 0`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(1) in-place',
    editorialUrl: 'https://leetcode.com/problems/set-matrix-zeroes/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 38,
    title: 'Game of Life',
    slug: 'game-of-life',
    category: 'Matrix',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon', 'Dropbox'],
    description: 'Conway\'s Game of Life: Given an m x n grid of cells, update the board in-place according to four standard rules.',
    approach: 'Use temporary state values (e.g. 2 for 0->1, -1 for 1->0) to encode both past and future states in-place.',
    code: `def gameOfLife(board):
    m, n = len(board), len(board[0])
    dirs = [(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
    for r in range(m):
        for c in range(n):
            live_neighbors = sum(1 for dr, dc in dirs if 0 <= r+dr < m and 0 <= c+dc < n and abs(board[r+dr][c+dc]) == 1)
            if board[r][c] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                board[r][c] = -1  # live -> dead
            elif board[r][c] == 0 and live_neighbors == 3:
                board[r][c] = 2   # dead -> live
    for r in range(m):
        for c in range(n):
            if board[r][c] > 0:
                board[r][c] = 1
            else:
                board[r][c] = 0`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/game-of-life/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 5. Hashmap (9 problems) ─────────────────────────────────────────
  {
    id: 39,
    title: 'Ransom Note',
    slug: 'ransom-note',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Apple'],
    description: 'Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.',
    approach: 'Count characters in magazine. For each char in ransomNote, decrement count; if missing or 0, return False.',
    code: `from collections import Counter

def canConstruct(ransomNote, magazine):
    mag_count = Counter(magazine)
    for ch in ransomNote:
        if mag_count[ch] <= 0:
            return False
        mag_count[ch] -= 1
    return True`,
    timeComplexity: 'O(m + n)',
    spaceComplexity: 'O(1) (at most 26 letters)',
    editorialUrl: 'https://leetcode.com/problems/ransom-note/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 40,
    title: 'Isomorphic Strings',
    slug: 'isomorphic-strings',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'LinkedIn'],
    description: 'Given two strings s and t, determine if they are isomorphic (bijective mapping).',
    approach: 'Two hash maps: map_s_to_t and map_t_to_s to enforce one-to-one correspondence.',
    code: `def isIsomorphic(s, t):
    s2t, t2s = {}, {}
    for c1, c2 in zip(s, t):
        if (c1 in s2t and s2t[c1] != c2) or (c2 in t2s and t2s[c2] != c1):
            return False
        s2t[c1] = c2
        t2s[c2] = c1
    return True`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/isomorphic-strings/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 41,
    title: 'Word Pattern',
    slug: 'word-pattern',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Uber'],
    description: 'Given a pattern and a string s, find if s follows the same pattern (bijection between letter and word).',
    approach: 'Split s into words and check bidirectional mapping between pattern characters and words.',
    code: `def wordPattern(pattern, s):
    words = s.split()
    if len(pattern) != len(words):
        return False
    p2w, w2p = {}, {}
    for p, w in zip(pattern, words):
        if (p in p2w and p2w[p] != w) or (w in w2p and w2p[w] != p):
            return False
        p2w[p] = w
        w2p[w] = p
    return True`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(w)',
    editorialUrl: 'https://leetcode.com/problems/word-pattern/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 42,
    title: 'Valid Anagram',
    slug: 'valid-anagram',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'Given two strings s and t, return true if t is an anagram of s, and false otherwise.',
    approach: 'Counter equality or frequency array of size 26.',
    code: `from collections import Counter

def isAnagram(s, t):
    return Counter(s) == Counter(t)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/valid-anagram/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 43,
    title: 'Group Anagrams',
    slug: 'group-anagrams',
    category: 'Hashmap',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple'],
    description: 'Given an array of strings strs, group the anagrams together in any order.',
    approach: 'Use sorted word or character frequency tuple as dictionary key.',
    code: `from collections import defaultdict

def groupAnagrams(strs):
    groups = defaultdict(list)
    for s in strs:
        key = ''.join(sorted(s))
        groups[key].append(s)
    return list(groups.values())`,
    timeComplexity: 'O(n * k log k)',
    spaceComplexity: 'O(n * k)',
    editorialUrl: 'https://leetcode.com/problems/group-anagrams/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 44,
    title: 'Two Sum',
    slug: 'two-sum',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon', 'Microsoft', 'Meta', 'Apple'],
    description: 'Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.',
    approach: 'Hash Map lookup: Check if target - num is already in dictionary in O(1) time.',
    code: `def twoSum(nums, target):
    seen = {}
    for i, num in enumerate(nums):
        comp = target - num
        if comp in seen:
            return [seen[comp], i]
        seen[num] = i
    return []`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/two-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 45,
    title: 'Happy Number',
    slug: 'happy-number',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon', 'Apple'],
    description: 'A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits until it reaches 1.',
    approach: 'Cycle detection using Hash Set or Floyd\'s Tortoise & Hare.',
    code: `def isHappy(n):
    def get_next(num):
        total = 0
        while num > 0:
            num, digit = divmod(num, 10)
            total += digit ** 2
        return total
    seen = set()
    while n != 1 and n not in seen:
        seen.add(n)
        n = get_next(n)
    return n == 1`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(log n)',
    editorialUrl: 'https://leetcode.com/problems/happy-number/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 46,
    title: 'Contains Duplicate II',
    slug: 'contains-duplicate-ii',
    category: 'Hashmap',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Meta'],
    description: 'Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.',
    approach: 'Dictionary storing last seen index of each number. If i - seen[num] <= k, return True.',
    code: `def containsNearbyDuplicate(nums, k):
    seen = {}
    for i, num in enumerate(nums):
        if num in seen and i - seen[num] <= k:
            return True
        seen[num] = i
    return False`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(min(n, k))',
    editorialUrl: 'https://leetcode.com/problems/contains-duplicate-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 47,
    title: 'Longest Consecutive Sequence',
    slug: 'longest-consecutive-sequence',
    category: 'Hashmap',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence in O(n) time.',
    approach: 'Put elements in a set. Only start counting when num - 1 is not in the set (identifies sequence starts).',
    code: `def longestConsecutive(nums):
    num_set = set(nums)
    longest = 0
    for num in num_set:
        if num - 1 not in num_set:
            current = num
            streak = 1
            while current + 1 in num_set:
                current += 1
                streak += 1
            longest = max(longest, streak)
    return longest`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/longest-consecutive-sequence/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 6. Intervals (4 problems) ───────────────────────────────────────
  {
    id: 48,
    title: 'Summary Ranges',
    slug: 'summary-ranges',
    category: 'Intervals',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon'],
    description: 'Return the smallest sorted list of ranges that cover all the numbers in the array exactly.',
    approach: 'Two pointers to scan consecutive runs nums[j] == nums[j-1] + 1.',
    code: `def summaryRanges(nums):
    res = []
    i = 0
    n = len(nums)
    while i < n:
        start = nums[i]
        while i + 1 < n and nums[i + 1] == nums[i] + 1:
            i += 1
        if start == nums[i]:
            res.append(str(start))
        else:
            res.append(f"{start}->{nums[i]}")
        i += 1
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/summary-ranges/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 49,
    title: 'Merge Intervals',
    slug: 'merge-intervals',
    category: 'Intervals',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Bloomberg'],
    description: 'Given an array of intervals, merge all overlapping intervals.',
    approach: 'Sort intervals by start time. If current start <= previous end, merge: prev_end = max(prev_end, cur_end).',
    code: `def mergeIntervals(intervals):
    intervals.sort(key=lambda x: x[0])
    merged = []
    for interval in intervals:
        if not merged or merged[-1][1] < interval[0]:
            merged.append(interval)
        else:
            merged[-1][1] = max(merged[-1][1], interval[1])
    return merged`,
    timeComplexity: 'O(n log n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/merge-intervals/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 50,
    title: 'Insert Interval',
    slug: 'insert-interval',
    category: 'Intervals',
    difficulty: 'Medium',
    companies: ['Google', 'Meta', 'Amazon', 'Microsoft'],
    description: 'Insert newInterval into intervals such that intervals is still sorted in ascending order and non-overlapping.',
    approach: 'Three phases: 1) Add all intervals before newInterval. 2) Merge all overlapping intervals. 3) Add all remaining intervals.',
    code: `def insert(intervals, newInterval):
    res = []
    i = 0
    n = len(intervals)
    while i < n and intervals[i][1] < newInterval[0]:
        res.append(intervals[i])
        i += 1
    while i < n and intervals[i][0] <= newInterval[1]:
        newInterval[0] = min(newInterval[0], intervals[i][0])
        newInterval[1] = max(newInterval[1], intervals[i][1])
        i += 1
    res.append(newInterval)
    while i < n:
        res.append(intervals[i])
        i += 1
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/insert-interval/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 51,
    title: 'Minimum Number of Arrows to Burst Balloons',
    slug: 'minimum-number-of-arrows-to-burst-balloons',
    category: 'Intervals',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta'],
    description: 'Find the minimum number of arrows that must be shot to burst all balloons.',
    approach: 'Sort balloons by end coordinate. Greedily shoot arrow at current end coordinate; skip all balloons that overlap with this point.',
    code: `def findMinArrowShots(points):
    if not points:
        return 0
    points.sort(key=lambda x: x[1])
    arrows = 1
    prev_end = points[0][1]
    for start, end in points[1:]:
        if start > prev_end:
            arrows += 1
            prev_end = end
    return arrows`,
    timeComplexity: 'O(n log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 7. Stack (5 problems) ───────────────────────────────────────────
  {
    id: 52,
    title: 'Valid Parentheses',
    slug: 'valid-parentheses',
    category: 'Stack',
    difficulty: 'Easy',
    companies: ['Amazon', 'Meta', 'Google', 'Microsoft', 'Apple'],
    description: 'Given a string s containing just the characters "(", ")", "{", "}", "[" and "]", determine if the input string is valid.',
    approach: 'Use a stack. Push expected closing bracket when seeing an opening bracket. When seeing closing bracket, pop and compare.',
    code: `def isValid(s):
    stack = []
    mapping = {')': '(', '}': '{', ']': '['}
    for ch in s:
        if ch in mapping:
            if not stack or stack.pop() != mapping[ch]:
                return False
        else:
            stack.append(ch)
    return len(stack) == 0`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/valid-parentheses/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 53,
    title: 'Simplify Path',
    slug: 'simplify-path',
    category: 'Stack',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Simplify the Unix-style absolute path for a file or directory.',
    approach: 'Split by "/". Ignore empty and "." tokens. On "..", pop from stack. Join stack with "/".',
    code: `def simplifyPath(path):
    stack = []
    for token in path.split('/'):
        if token == '' or token == '.':
            continue
        elif token == '..':
            if stack:
                stack.pop()
        else:
            stack.append(token)
    return '/' + '/'.join(stack)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/simplify-path/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 54,
    title: 'Min Stack',
    slug: 'min-stack',
    category: 'Stack',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Bloomberg'],
    description: 'Design a stack that supports push, pop, top, and retrieving the minimum element in constant time O(1).',
    approach: 'Store tuples (val, current_min) in stack or maintain a parallel min_stack.',
    code: `class MinStack:
    def __init__(self):
        self.stack = []

    def push(self, val: int) -> None:
        cur_min = val if not self.stack else min(val, self.stack[-1][1])
        self.stack.append((val, cur_min))

    def pop(self) -> None:
        self.stack.pop()

    def top(self) -> int:
        return self.stack[-1][0]

    def getMin(self) -> int:
        return self.stack[-1][1]`,
    timeComplexity: 'O(1) for all operations',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/min-stack/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 55,
    title: 'Evaluate Reverse Polish Notation',
    slug: 'evaluate-reverse-polish-notation',
    category: 'Stack',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'LinkedIn'],
    description: 'Evaluate the value of an arithmetic expression in Reverse Polish Notation (postfix).',
    approach: 'Push numbers to stack. When operator encountered, pop b then a, evaluate a op b, push result back.',
    code: `def evalRPN(tokens):
    stack = []
    ops = {
        '+': lambda a, b: a + b,
        '-': lambda a, b: a - b,
        '*': lambda a, b: a * b,
        '/': lambda a, b: int(a / b)
    }
    for t in tokens:
        if t in ops:
            b = stack.pop()
            a = stack.pop()
            stack.append(ops[t](a, b))
        else:
            stack.append(int(t))
    return stack[0]`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/evaluate-reverse-polish-notation/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 56,
    title: 'Basic Calculator',
    slug: 'basic-calculator',
    category: 'Stack',
    difficulty: 'Hard',
    companies: ['Meta', 'Google', 'Amazon', 'Microsoft'],
    description: 'Implement a basic calculator to evaluate a simple expression string containing "+", "-", "(", ")" and spaces.',
    approach: 'Maintain running result and sign. On "(", push result and sign to stack. On ")", pop sign and previous result.',
    code: `def calculate(s):
    stack = []
    operand = 0
    res = 0
    sign = 1
    for ch in s:
        if ch.isdigit():
            operand = operand * 10 + int(ch)
        elif ch == '+':
            res += sign * operand
            sign = 1
            operand = 0
        elif ch == '-':
            res += sign * operand
            sign = -1
            operand = 0
        elif ch == '(':
            stack.append(res)
            stack.append(sign)
            sign = 1
            res = 0
        elif ch == ')':
            res += sign * operand
            res *= stack.pop()  # sign
            res += stack.pop()  # operand
            operand = 0
    return res + (sign * operand)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/basic-calculator/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 8. Linked List (11 problems) ────────────────────────────────────
  {
    id: 57,
    title: 'Linked List Cycle',
    slug: 'linked-list-cycle',
    category: 'Linked List',
    difficulty: 'Easy',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'Given head, the head of a linked list, determine if the linked list has a cycle in it.',
    approach: 'Floyd\'s Tortoise and Hare: slow moves 1 step, fast moves 2 steps. If fast == slow, cycle exists.',
    code: `def hasCycle(head):
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return True
    return False`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/linked-list-cycle/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 58,
    title: 'Add Two Numbers',
    slug: 'add-two-numbers',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple'],
    description: 'Add two non-empty linked lists representing two non-negative integers stored in reverse order.',
    approach: 'Traverse both lists with a carry variable. Sum = l1.val + l2.val + carry. Create new node with sum % 10.',
    code: `class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def addTwoNumbers(l1, l2):
    dummy = ListNode(0)
    cur = dummy
    carry = 0
    while l1 or l2 or carry:
        v1 = l1.val if l1 else 0
        v2 = l2.val if l2 else 0
        val = v1 + v2 + carry
        carry = val // 10
        cur.next = ListNode(val % 10)
        cur = cur.next
        if l1: l1 = l1.next
        if l2: l2 = l2.next
    return dummy.next`,
    timeComplexity: 'O(max(n, m))',
    spaceComplexity: 'O(max(n, m))',
    editorialUrl: 'https://leetcode.com/problems/add-two-numbers/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 59,
    title: 'Merge Two Sorted Lists',
    slug: 'merge-two-sorted-lists',
    category: 'Linked List',
    difficulty: 'Easy',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta', 'Apple'],
    description: 'Merge two sorted linked lists and return it as a sorted list.',
    approach: 'Dummy head pointer with iteration: Attach the node with the smaller value and advance.',
    code: `def mergeTwoLists(list1, list2):
    dummy = ListNode()
    tail = dummy
    while list1 and list2:
        if list1.val < list2.val:
            tail.next = list1
            list1 = list1.next
        else:
            tail.next = list2
            list2 = list2.next
        tail = tail.next
    tail.next = list1 or list2
    return dummy.next`,
    timeComplexity: 'O(n + m)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/merge-two-sorted-lists/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 60,
    title: 'Copy List with Random Pointer',
    slug: 'copy-list-with-random-pointer',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Meta', 'Microsoft', 'Google'],
    description: 'Construct a deep copy of a linked list with next and random pointers.',
    approach: 'Two-pass hash map: First pass maps old_node -> new_node. Second pass assigns next and random pointers.',
    code: `def copyRandomList(head):
    if not head:
        return None
    mapping = {}
    cur = head
    while cur:
        mapping[cur] = Node(cur.val)
        cur = cur.next
    cur = head
    while cur:
        if cur.next:
            mapping[cur].next = mapping[cur.next]
        if cur.random:
            mapping[cur].random = mapping[cur.random]
        cur = cur.next
    return mapping[head]`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/copy-list-with-random-pointer/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 61,
    title: 'Reverse Linked List II',
    slug: 'reverse-linked-list-ii',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Meta'],
    description: 'Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right in one pass.',
    approach: 'Navigate to node (left - 1). Perform standard in-place pointer reversal for (right - left) steps.',
    code: `def reverseBetween(head, left, right):
    if not head or left == right:
        return head
    dummy = ListNode(0, head)
    prev = dummy
    for _ in range(left - 1):
        prev = prev.next
    cur = prev.next
    for _ in range(right - left):
        nxt = cur.next
        cur.next = nxt.next
        nxt.next = prev.next
        prev.next = nxt
    return dummy.next`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/reverse-linked-list-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 62,
    title: 'Reverse Nodes in k-Group',
    slug: 'reverse-nodes-in-k-group',
    category: 'Linked List',
    difficulty: 'Hard',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'Reverse the nodes of a linked list k at a time and return its modified list.',
    approach: 'Count k nodes. If k nodes exist, reverse the group and link recursively or iteratively.',
    code: `def reverseKGroup(head, k):
    cur = head
    count = 0
    while cur and count < k:
        cur = cur.next
        count += 1
    if count == k:
        reversed_head = None
        curr = head
        for _ in range(k):
            nxt = curr.next
            curr.next = reversed_head
            reversed_head = curr
            curr = nxt
        head.next = reverseKGroup(curr, k)
        return reversed_head
    return head`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1) auxiliary',
    editorialUrl: 'https://leetcode.com/problems/reverse-nodes-in-k-group/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 63,
    title: 'Remove Nth Node From End of List',
    slug: 'remove-nth-node-from-end-of-list',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Apple'],
    description: 'Given the head of a linked list, remove the nth node from the end of the list and return its head.',
    approach: 'Two pointers fast and slow with a gap of n nodes. When fast reaches end, slow is just before target.',
    code: `def removeNthFromEnd(head, n):
    dummy = ListNode(0, head)
    fast = slow = dummy
    for _ in range(n):
        fast = fast.next
    while fast.next:
        fast = fast.next
        slow = slow.next
    slow.next = slow.next.next
    return dummy.next`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/remove-nth-node-from-end-of-list/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 64,
    title: 'Remove Duplicates from Sorted List II',
    slug: 'remove-duplicates-from-sorted-list-ii',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.',
    approach: 'Dummy head. While cur.next and cur.next.next have same value, skip all matching nodes.',
    code: `def deleteDuplicates(head):
    dummy = ListNode(0, head)
    prev = dummy
    while head:
        if head.next and head.val == head.next.val:
            while head.next and head.val == head.next.val:
                head = head.next
            prev.next = head.next
        else:
            prev = prev.next
        head = head.next
    return dummy.next`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 65,
    title: 'Rotate List',
    slug: 'rotate-list',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google'],
    description: 'Given the head of a linked list, rotate the list to the right by k places.',
    approach: 'Find length, connect tail to head (make ring), find new tail at (length - k % length - 1), break ring.',
    code: `def rotateRight(head, k):
    if not head or not head.next or k == 0:
        return head
    n = 1
    tail = head
    while tail.next:
        tail = tail.next
        n += 1
    k %= n
    if k == 0:
        return head
    tail.next = head
    new_tail = head
    for _ in range(n - k - 1):
        new_tail = new_tail.next
    new_head = new_tail.next
    new_tail.next = None
    return new_head`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/rotate-list/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 66,
    title: 'Partition List',
    slug: 'partition-list',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Adobe'],
    description: 'Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.',
    approach: 'Maintain two lists: less and greater_equal. Stitch them together at the end.',
    code: `def partition(head, x):
    less_dummy = ListNode(0)
    greater_dummy = ListNode(0)
    less = less_dummy
    greater = greater_dummy
    while head:
        if head.val < x:
            less.next = head
            less = less.next
        else:
            greater.next = head
            greater = greater.next
        head = head.next
    greater.next = None
    less.next = greater_dummy.next
    return less_dummy.next`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/partition-list/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 67,
    title: 'LRU Cache',
    slug: 'lru-cache',
    category: 'Linked List',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple', 'Bloomberg'],
    description: 'Design a data structure that follows the constraints of a Least Recently Used (LRU) cache with get and put in O(1) time.',
    approach: 'Hash map + Doubly Linked List with dummy head and tail. On access/update, move node to head. On capacity overflow, remove tail.prev.',
    code: `class DLinkedNode:
    def __init__(self, key=0, val=0):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.head = DLinkedNode()
        self.tail = DLinkedNode()
        self.head.next = self.tail
        self.tail.prev = self.head

    def _remove(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev

    def _add(self, node):
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def get(self, key: int) -> int:
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val
        return -1

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self._remove(self.cache[key])
        node = DLinkedNode(key, value)
        self._add(node)
        self.cache[key] = node
        if len(self.cache) > self.capacity:
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]`,
    timeComplexity: 'O(1) for get and put',
    spaceComplexity: 'O(capacity)',
    editorialUrl: 'https://leetcode.com/problems/lru-cache/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 9. Binary Tree General (14 problems) ────────────────────────────
  {
    id: 68,
    title: 'Maximum Depth of Binary Tree',
    slug: 'maximum-depth-of-binary-tree',
    category: 'Binary Tree General',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'LinkedIn'],
    description: 'Given the root of a binary tree, return its maximum depth.',
    approach: 'Recursive DFS: max_depth = 1 + max(maxDepth(root.left), maxDepth(root.right)).',
    code: `def maxDepth(root):
    if not root:
        return 0
    return 1 + max(maxDepth(root.left), maxDepth(root.right))`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/maximum-depth-of-binary-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 69,
    title: 'Same Tree',
    slug: 'same-tree',
    category: 'Binary Tree General',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given the roots of two binary trees p and q, check if they are the same or not.',
    approach: 'Recursive comparison: p.val == q.val and same(p.left, q.left) and same(p.right, q.right).',
    code: `def isSameTree(p, q):
    if not p and not q:
        return True
    if not p or not q or p.val != q.val:
        return False
    return isSameTree(p.left, q.left) and isSameTree(p.right, q.right)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/same-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 70,
    title: 'Invert Binary Tree',
    slug: 'invert-binary-tree',
    category: 'Binary Tree General',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon', 'Meta', 'Microsoft'],
    description: 'Given the root of a binary tree, invert the tree, and return its root.',
    approach: 'Recursively swap left and right subtrees.',
    code: `def invertTree(root):
    if not root:
        return None
    root.left, root.right = invertTree(root.right), invertTree(root.left)
    return root`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/invert-binary-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 71,
    title: 'Symmetric Tree',
    slug: 'symmetric-tree',
    category: 'Binary Tree General',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Bloomberg'],
    description: 'Given the root of a binary tree, check whether it is a mirror of itself.',
    approach: 'Compare t1.val == t2.val and mirror(t1.left, t2.right) and mirror(t1.right, t2.left).',
    code: `def isSymmetric(root):
    def isMirror(t1, t2):
        if not t1 and not t2:
            return True
        if not t1 or not t2 or t1.val != t2.val:
            return False
        return isMirror(t1.left, t2.right) and isMirror(t1.right, t2.left)
    return isMirror(root.left, root.right) if root else True`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/symmetric-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 72,
    title: 'Construct Binary Tree from Preorder and Inorder Traversal',
    slug: 'construct-binary-tree-from-preorder-and-inorder-traversal',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'Given two integer arrays preorder and inorder, construct and return the binary tree.',
    approach: 'Root is preorder[0]. Find root in inorder using hash map. Left subtree elements are before root in inorder.',
    code: `def buildTree(preorder, inorder):
    in_map = {val: idx for idx, val in enumerate(inorder)}
    pre_iter = iter(preorder)
    def helper(start, end):
        if start > end:
            return None
        val = next(pre_iter)
        root = TreeNode(val)
        mid = in_map[val]
        root.left = helper(start, mid - 1)
        root.right = helper(mid + 1, end)
        return root
    return helper(0, len(inorder) - 1)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 73,
    title: 'Construct Binary Tree from Inorder and Postorder Traversal',
    slug: 'construct-binary-tree-from-inorder-and-postorder-traversal',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google'],
    description: 'Given two integer arrays inorder and postorder, construct and return the binary tree.',
    approach: 'Root is postorder[-1]. Build right child before left child using postorder.pop().',
    code: `def buildTreePost(inorder, postorder):
    in_map = {val: i for i, val in enumerate(inorder)}
    def helper(start, end):
        if start > end:
            return None
        val = postorder.pop()
        root = TreeNode(val)
        mid = in_map[val]
        root.right = helper(mid + 1, end)
        root.left = helper(start, mid - 1)
        return root
    return helper(0, len(inorder) - 1)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 74,
    title: 'Populating Next Right Pointers in Each Node II',
    slug: 'populating-next-right-pointers-in-each-node-ii',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Bloomberg'],
    description: 'Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.',
    approach: 'Level-order traversal using existing next pointers of the parent level as a linked list (O(1) extra space).',
    code: `def connect(root):
    cur = root
    while cur:
        dummy = Node(0)
        tail = dummy
        while cur:
            if cur.left:
                tail.next = cur.left
                tail = tail.next
            if cur.right:
                tail.next = cur.right
                tail = tail.next
            cur = cur.next
        cur = dummy.next
    return root`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 75,
    title: 'Flatten Binary Tree to Linked List',
    slug: 'flatten-binary-tree-to-linked-list',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Microsoft'],
    description: 'Flatten the tree into a "linked list" in-place following preorder traversal.',
    approach: 'Morris-like traversal: Find predecessor of right child in left subtree and connect predecessor.right = cur.right.',
    code: `def flatten(root):
    cur = root
    while cur:
        if cur.left:
            pre = cur.left
            while pre.right:
                pre = pre.right
            pre.right = cur.right
            cur.right = cur.left
            cur.left = None
        cur = cur.right`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/flatten-binary-tree-to-linked-list/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 76,
    title: 'Path Sum',
    slug: 'path-sum',
    category: 'Binary Tree General',
    difficulty: 'Easy',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.',
    approach: 'Subtract node.val from targetSum. At leaf node, check if remainder == 0.',
    code: `def hasPathSum(root, targetSum):
    if not root:
        return False
    targetSum -= root.val
    if not root.left and not root.right:
        return targetSum == 0
    return hasPathSum(root.left, targetSum) or hasPathSum(root.right, targetSum)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/path-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 77,
    title: 'Sum Root to Leaf Numbers',
    slug: 'sum-root-to-leaf-numbers',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number. Return the total sum of all root-to-leaf numbers.',
    approach: 'DFS carrying current path number: cur_num = cur_num * 10 + node.val.',
    code: `def sumNumbers(root):
    def dfs(node, cur):
        if not node:
            return 0
        cur = cur * 10 + node.val
        if not node.left and not node.right:
            return cur
        return dfs(node.left, cur) + dfs(node.right, cur)
    return dfs(root, 0)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/sum-root-to-leaf-numbers/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 78,
    title: 'Binary Tree Maximum Path Sum',
    slug: 'binary-tree-maximum-path-sum',
    category: 'Binary Tree General',
    difficulty: 'Hard',
    companies: ['Meta', 'Google', 'Amazon', 'Microsoft'],
    description: 'A path in a binary tree is a sequence of nodes where each pair of adjacent nodes has an edge. Return the maximum path sum of any non-empty path.',
    approach: 'Bottom-up DFS: Compute max gain from left and right child (clamped at 0). Update global_max = max(global_max, node.val + left_gain + right_gain).',
    code: `def maxPathSum(root):
    max_sum = float('-inf')
    def gain(node):
        nonlocal max_sum
        if not node:
            return 0
        left = max(0, gain(node.left))
        right = max(0, gain(node.right))
        max_sum = max(max_sum, node.val + left + right)
        return node.val + max(left, right)
    gain(root)
    return max_sum`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/binary-tree-maximum-path-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 79,
    title: 'Binary Search Tree Iterator',
    slug: 'binary-search-tree-iterator',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Implement the BSTIterator class that represents an in-order iterator over a binary search tree (BST).',
    approach: 'Controlled stack traversal: Push all left nodes onto stack. When next() is called, pop node and push all left nodes of its right child.',
    code: `class BSTIterator:
    def __init__(self, root):
        self.stack = []
        self._push_left(root)

    def _push_left(self, node):
        while node:
            self.stack.append(node)
            node = node.left

    def next(self) -> int:
        node = self.stack.pop()
        if node.right:
            self._push_left(node.right)
        return node.val

    def hasNext(self) -> bool:
        return len(self.stack) > 0`,
    timeComplexity: 'O(1) amortized',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/binary-search-tree-iterator/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 80,
    title: 'Count Complete Tree Nodes',
    slug: 'count-complete-tree-nodes',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon', 'Meta'],
    description: 'Given the root of a complete binary tree, return the number of the nodes in the tree in less than O(n) time.',
    approach: 'Compare left height and right height. If equal, left subtree is full 2^h - 1. Use binary search over tree structure in O(log² n).',
    code: `def countNodes(root):
    if not root:
        return 0
    left_h = 0
    l = root
    while l:
        left_h += 1
        l = l.left
    right_h = 0
    r = root
    while r:
        right_h += 1
        r = r.right
    if left_h == right_h:
        return (1 << left_h) - 1
    return 1 + countNodes(root.left) + countNodes(root.right)`,
    timeComplexity: 'O(log² n)',
    spaceComplexity: 'O(log n)',
    editorialUrl: 'https://leetcode.com/problems/count-complete-tree-nodes/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 81,
    title: 'Lowest Common Ancestor of a Binary Tree',
    slug: 'lowest-common-ancestor-of-a-binary-tree',
    category: 'Binary Tree General',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'Microsoft', 'Apple'],
    description: 'Given a binary tree, find the lowest common ancestor (LCA) of two given nodes p and q.',
    approach: 'Recursive DFS: If root is p or q or None, return root. If both left and right return non-None, root is LCA.',
    code: `def lowestCommonAncestor(root, p, q):
    if not root or root == p or root == q:
        return root
    left = lowestCommonAncestor(root.left, p, q)
    right = lowestCommonAncestor(root.right, p, q)
    if left and right:
        return root
    return left or right`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 10. Binary Tree BFS (4 problems) ────────────────────────────────
  {
    id: 82,
    title: 'Binary Tree Right Side View',
    slug: 'binary-tree-right-side-view',
    category: 'Binary Tree BFS',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Bloomberg', 'Google'],
    description: 'Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.',
    approach: 'Level-order BFS: Append the last element of each level queue to the result list.',
    code: `from collections import deque

def rightSideView(root):
    if not root:
        return []
    res = []
    q = deque([root])
    while q:
        level_size = len(q)
        for i in range(level_size):
            node = q.popleft()
            if i == level_size - 1:
                res.append(node.val)
            if node.left: q.append(node.left)
            if node.right: q.append(node.right)
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(width)',
    editorialUrl: 'https://leetcode.com/problems/binary-tree-right-side-view/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 83,
    title: 'Average of Levels in Binary Tree',
    slug: 'average-of-levels-in-binary-tree',
    category: 'Binary Tree BFS',
    difficulty: 'Easy',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Given the root of a binary tree, return the average value of the nodes on each level in the form of an array.',
    approach: 'Standard BFS: compute sum of node values at each level and divide by level count.',
    code: `from collections import deque

def averageOfLevels(root):
    if not root:
        return []
    res = []
    q = deque([root])
    while q:
        count = len(q)
        level_sum = 0
        for _ in range(count):
            node = q.popleft()
            level_sum += node.val
            if node.left: q.append(node.left)
            if node.right: q.append(node.right)
        res.append(level_sum / count)
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(width)',
    editorialUrl: 'https://leetcode.com/problems/average-of-levels-in-binary-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 84,
    title: 'Binary Tree Level Order Traversal',
    slug: 'binary-tree-level-order-traversal',
    category: 'Binary Tree BFS',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta', 'Apple'],
    description: 'Given the root of a binary tree, return the level order traversal of its nodes\' values.',
    approach: 'BFS with queue: Collect all nodes at the current depth into a list before advancing.',
    code: `from collections import deque

def levelOrder(root):
    if not root:
        return []
    res = []
    q = deque([root])
    while q:
        level = []
        for _ in range(len(q)):
            node = q.popleft()
            level.append(node.val)
            if node.left: q.append(node.left)
            if node.right: q.append(node.right)
        res.append(level)
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/binary-tree-level-order-traversal/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 85,
    title: 'Binary Tree Zigzag Level Order Traversal',
    slug: 'binary-tree-zigzag-level-order-traversal',
    category: 'Binary Tree BFS',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Bloomberg'],
    description: 'Given the root of a binary tree, return the zigzag level order traversal of its nodes\' values (alternating left-to-right and right-to-left).',
    approach: 'Level-order BFS with a boolean flag: reverse level values array whenever flag indicates right-to-left.',
    code: `from collections import deque

def zigzagLevelOrder(root):
    if not root:
        return []
    res = []
    q = deque([root])
    left_to_right = True
    while q:
        level = []
        for _ in range(len(q)):
            node = q.popleft()
            level.append(node.val)
            if node.left: q.append(node.left)
            if node.right: q.append(node.right)
        if not left_to_right:
            level.reverse()
        res.append(level)
        left_to_right = not left_to_right
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 11. Binary Search Tree (3 problems) ─────────────────────────────
  {
    id: 86,
    title: 'Minimum Absolute Difference in BST',
    slug: 'minimum-absolute-difference-in-bst',
    category: 'Binary Search Tree',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon'],
    description: 'Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes.',
    approach: 'In-order traversal yields sorted values. Maintain prev_val and compute min(min_diff, cur.val - prev_val).',
    code: `def getMinimumDifference(root):
    prev = None
    min_diff = float('inf')
    def inorder(node):
        nonlocal prev, min_diff
        if not node:
            return
        inorder(node.left)
        if prev is not None:
            min_diff = min(min_diff, node.val - prev)
        prev = node.val
        inorder(node.right)
    inorder(root)
    return min_diff`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/minimum-absolute-difference-in-bst/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 87,
    title: 'Kth Smallest Element in a BST',
    slug: 'kth-smallest-element-in-a-bst',
    category: 'Binary Search Tree',
    difficulty: 'Medium',
    companies: ['Amazon', 'Meta', 'Google', 'Microsoft', 'Uber'],
    description: 'Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.',
    approach: 'Iterative in-order traversal using a stack; decrement k upon each popped node. When k == 0, return node.val.',
    code: `def kthSmallest(root, k):
    stack = []
    cur = root
    while cur or stack:
        while cur:
            stack.append(cur)
            cur = cur.left
        cur = stack.pop()
        k -= 1
        if k == 0:
            return cur.val
        cur = cur.right`,
    timeComplexity: 'O(height + k)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/kth-smallest-element-in-a-bst/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 88,
    title: 'Validate Binary Search Tree',
    slug: 'validate-binary-search-tree',
    category: 'Binary Search Tree',
    difficulty: 'Medium',
    companies: ['Amazon', 'Meta', 'Microsoft', 'Bloomberg', 'Apple'],
    description: 'Given the root of a binary tree, determine if it is a valid binary search tree (BST).',
    approach: 'DFS maintaining valid value boundaries: low < node.val < high.',
    code: `def isValidBST(root):
    def validate(node, low=float('-inf'), high=float('inf')):
        if not node:
            return True
        if not (low < node.val < high):
            return False
        return validate(node.left, low, node.val) and validate(node.right, node.val, high)
    return validate(root)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(height)',
    editorialUrl: 'https://leetcode.com/problems/validate-binary-search-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 12. Graph General (6 problems) ──────────────────────────────────
  {
    id: 89,
    title: 'Number of Islands',
    slug: 'number-of-islands',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta', 'Bloomberg'],
    description: 'Given an m x n 2D binary grid grid which represents a map of "1"s (land) and "0"s (water), return the number of islands.',
    approach: 'Iterate over every cell. When grid[r][c] == "1", increment count and run DFS/BFS to sink the island (mark as "0").',
    code: `def numIslands(grid):
    if not grid:
        return 0
    m, n = len(grid), len(grid[0])
    islands = 0
    def sink(r, c):
        if r < 0 or r >= m or c < 0 or c >= n or grid[r][c] != '1':
            return
        grid[r][c] = '0'
        sink(r + 1, c)
        sink(r - 1, c)
        sink(r, c + 1)
        sink(r, c - 1)
    for r in range(m):
        for c in range(n):
            if grid[r][c] == '1':
                islands += 1
                sink(r, c)
    return islands`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(m * n)',
    editorialUrl: 'https://leetcode.com/problems/number-of-islands/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 90,
    title: 'Surrounded Regions',
    slug: 'surrounded-regions',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given an m x n matrix board containing "X" and "O", capture all regions that are 4-directionally surrounded by "X".',
    approach: 'Boundary traversal: Mark all "O" cells connected to the boundary as safe (e.g. "S"). Flip remaining "O" to "X", and "S" back to "O".',
    code: `def solveRegions(board):
    if not board:
        return
    m, n = len(board), len(board[0])
    def mark(r, c):
        if r < 0 or r >= m or c < 0 or c >= n or board[r][c] != 'O':
            return
        board[r][c] = 'S'
        mark(r + 1, c); mark(r - 1, c); mark(r, c + 1); mark(r, c - 1)
    for r in range(m):
        mark(r, 0); mark(r, n - 1)
    for c in range(n):
        mark(0, c); mark(m - 1, c)
    for r in range(m):
        for c in range(n):
            if board[r][c] == 'O':
                board[r][c] = 'X'
            elif board[r][c] == 'S':
                board[r][c] = 'O'`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(m * n)',
    editorialUrl: 'https://leetcode.com/problems/surrounded-regions/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 91,
    title: 'Clone Graph',
    slug: 'clone-graph',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'Microsoft'],
    description: 'Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph.',
    approach: 'DFS with hash map visited[old_node] = new_node to avoid cycles.',
    code: `def cloneGraph(node):
    if not node:
        return None
    visited = {}
    def dfs(n):
        if n in visited:
            return visited[n]
        clone = Node(n.val)
        visited[n] = clone
        for neighbor in n.neighbors:
            clone.neighbors.append(dfs(neighbor))
        return clone
    return dfs(node)`,
    timeComplexity: 'O(V + E)',
    spaceComplexity: 'O(V)',
    editorialUrl: 'https://leetcode.com/problems/clone-graph/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 92,
    title: 'Evaluate Division',
    slug: 'evaluate-division',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon', 'Meta'],
    description: 'Given equations and values representing variable ratios, evaluate queries of form A / B.',
    approach: 'Graph BFS/DFS: Represent variables as nodes, ratios as directed weighted edges (weight for A->B is val, B->A is 1/val).',
    code: `from collections import defaultdict, deque

def calcEquation(equations, values, queries):
    graph = defaultdict(dict)
    for (a, b), val in zip(equations, values):
        graph[a][b] = val
        graph[b][a] = 1.0 / val
    def bfs(src, dst):
        if src not in graph or dst not in graph:
            return -1.0
        q = deque([(src, 1.0)])
        visited = {src}
        while q:
            node, prod = q.popleft()
            if node == dst:
                return prod
            for neighbor, weight in graph[node].items():
                if neighbor not in visited:
                    visited.add(neighbor)
                    q.append((neighbor, prod * weight))
        return -1.0
    return [bfs(a, b) for a, b in queries]`,
    timeComplexity: 'O(Q * (V + E))',
    spaceComplexity: 'O(V + E)',
    editorialUrl: 'https://leetcode.com/problems/evaluate-division/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 93,
    title: 'Course Schedule',
    slug: 'course-schedule',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'There are a total of numCourses you have to take. Some courses have prerequisites. Return true if you can finish all courses.',
    approach: 'Kahn\'s algorithm (Topological sort via in-degrees) or DFS cycle detection.',
    code: `from collections import defaultdict, deque

def canFinish(numCourses, prerequisites):
    adj = defaultdict(list)
    in_degree = [0] * numCourses
    for crs, pre in prerequisites:
        adj[pre].append(crs)
        in_degree[crs] += 1
    q = deque([i for i in range(numCourses) if in_degree[i] == 0])
    count = 0
    while q:
        node = q.popleft()
        count += 1
        for neighbor in adj[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                q.append(neighbor)
    return count == numCourses`,
    timeComplexity: 'O(V + E)',
    spaceComplexity: 'O(V + E)',
    editorialUrl: 'https://leetcode.com/problems/course-schedule/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 94,
    title: 'Course Schedule II',
    slug: 'course-schedule-ii',
    category: 'Graph General',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta'],
    description: 'Return the ordering of courses you should take to finish all courses. If impossible, return an empty array.',
    approach: 'Kahn\'s algorithm: Append nodes with 0 in-degree to the order array as they are popped from the queue.',
    code: `from collections import defaultdict, deque

def findOrder(numCourses, prerequisites):
    adj = defaultdict(list)
    in_degree = [0] * numCourses
    for crs, pre in prerequisites:
        adj[pre].append(crs)
        in_degree[crs] += 1
    q = deque([i for i in range(numCourses) if in_degree[i] == 0])
    order = []
    while q:
        node = q.popleft()
        order.append(node)
        for neighbor in adj[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                q.append(neighbor)
    return order if len(order) == numCourses else []`,
    timeComplexity: 'O(V + E)',
    spaceComplexity: 'O(V + E)',
    editorialUrl: 'https://leetcode.com/problems/course-schedule-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 13. Graph BFS (3 problems) ──────────────────────────────────────
  {
    id: 95,
    title: 'Snakes and Ladders',
    slug: 'snakes-and-ladders',
    category: 'Graph BFS',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'You are given an n x n integer matrix board where the cells are labeled from 1 to n² in Boustrophedon style. Return the least number of dice rolls to reach square n².',
    approach: 'Shortest path on unweighted graph using BFS: At each square s, explore all 6 dice moves (s + 1 to s + 6).',
    code: `from collections import deque

def snakesAndLadders(board):
    n = len(board)
    def get_coords(square):
        r = (square - 1) // n
        c = (square - 1) % n
        if r % 2 == 1:
            c = n - 1 - c
        return n - 1 - r, c
    q = deque([(1, 0)])
    visited = {1}
    while q:
        square, moves = q.popleft()
        if square == n * n:
            return moves
        for dice in range(1, 7):
            next_sq = square + dice
            if next_sq > n * n:
                break
            r, c = get_coords(next_sq)
            dest = board[r][c] if board[r][c] != -1 else next_sq
            if dest not in visited:
                visited.add(dest)
                q.append((dest, moves + 1))
    return -1`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(n²)',
    editorialUrl: 'https://leetcode.com/problems/snakes-and-ladders/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 96,
    title: 'Minimum Genetic Mutation',
    slug: 'minimum-genetic-mutation',
    category: 'Graph BFS',
    difficulty: 'Medium',
    companies: ['Twitter', 'Amazon'],
    description: 'A gene string can be represented by an 8-character long string. Return the minimum number of mutations needed to mutate from startGene to endGene.',
    approach: 'BFS over bank of valid mutations: Try mutating each character to "A", "C", "G", "T".',
    code: `from collections import deque

def minMutation(startGene, endGene, bank):
    bank_set = set(bank)
    if endGene not in bank_set:
        return -1
    q = deque([(startGene, 0)])
    visited = {startGene}
    while q:
        gene, steps = q.popleft()
        if gene == endGene:
            return steps
        for i in range(len(gene)):
            for ch in 'ACGT':
                mutated = gene[:i] + ch + gene[i+1:]
                if mutated in bank_set and mutated not in visited:
                    visited.add(mutated)
                    q.append((mutated, steps + 1))
    return -1`,
    timeComplexity: 'O(B * L * 4)',
    spaceComplexity: 'O(B)',
    editorialUrl: 'https://leetcode.com/problems/minimum-genetic-mutation/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 97,
    title: 'Word Ladder',
    slug: 'word-ladder',
    category: 'Graph BFS',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google', 'Meta', 'LinkedIn'],
    description: 'Return the number of words in the shortest transformation sequence from beginWord to endWord using a dictionary wordList.',
    approach: 'Bidirectional or single-source BFS on word patterns (e.g. "h*t").',
    code: `from collections import deque

def ladderLength(beginWord, endWord, wordList):
    words = set(wordList)
    if endWord not in words:
        return 0
    q = deque([(beginWord, 1)])
    visited = {beginWord}
    while q:
        word, length = q.popleft()
        if word == endWord:
            return length
        for i in range(len(word)):
            for ch in 'abcdefghijklmnopqrstuvwxyz':
                next_word = word[:i] + ch + word[i+1:]
                if next_word in words and next_word not in visited:
                    visited.add(next_word)
                    q.append((next_word, length + 1))
    return 0`,
    timeComplexity: 'O(M² * N)',
    spaceComplexity: 'O(M² * N)',
    editorialUrl: 'https://leetcode.com/problems/word-ladder/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 14. Trie (3 problems) ───────────────────────────────────────────
  {
    id: 98,
    title: 'Implement Trie (Prefix Tree)',
    slug: 'implement-trie-prefix-tree',
    category: 'Trie',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Twitter'],
    description: 'Implement a trie with insert, search, and startsWith methods.',
    approach: 'Nested dictionaries or TrieNode with children dict and is_end boolean.',
    code: `class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.is_end

    def startsWith(self, prefix: str) -> bool:
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True`,
    timeComplexity: 'O(L) per operation',
    spaceComplexity: 'O(total characters)',
    editorialUrl: 'https://leetcode.com/problems/implement-trie-prefix-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 99,
    title: 'Design Add and Search Words Data Structure',
    slug: 'design-add-and-search-words-data-structure',
    category: 'Trie',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Design a data structure that supports adding new words and finding if a string matches any previously added string with "." wildcard.',
    approach: 'Trie with recursive DFS for "." matching any child.',
    code: `class WordDictionary:
    def __init__(self):
        self.root = {}

    def addWord(self, word: str) -> None:
        node = self.root
        for ch in word:
            node = node.setdefault(ch, {})
        node['$'] = True

    def search(self, word: str) -> bool:
        def dfs(idx, node):
            if idx == len(word):
                return '$' in node
            ch = word[idx]
            if ch == '.':
                return any(dfs(idx + 1, child) for key, child in node.items() if key != '$')
            if ch not in node:
                return False
            return dfs(idx + 1, node[ch])
        return dfs(0, self.root)`,
    timeComplexity: 'O(M) for add, O(26^M) worst case for wildcard search',
    spaceComplexity: 'O(total characters)',
    editorialUrl: 'https://leetcode.com/problems/design-add-and-search-words-data-structure/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 100,
    title: 'Word Search II',
    slug: 'word-search-ii',
    category: 'Trie',
    difficulty: 'Hard',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta', 'Apple'],
    description: 'Given an m x n board of characters and a list of strings words, return all words on the board.',
    approach: 'Build Trie from words. Backtrack on board matching Trie paths to prune unpromising branches.',
    code: `def findWords(board, words):
    trie = {}
    for word in words:
        node = trie
        for ch in word:
            node = node.setdefault(ch, {})
        node['#'] = word
    m, n = len(board), len(board[0])
    res = []
    def dfs(r, c, parent):
        ch = board[r][c]
        node = parent[ch]
        if '#' in node:
            res.append(node.pop('#'))
        board[r][c] = '*'
        for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and board[nr][nc] in node:
                dfs(nr, nc, node)
        board[r][c] = ch
        if not node:
            parent.pop(ch)
    for r in range(m):
        for c in range(n):
            if board[r][c] in trie:
                dfs(r, c, trie)
    return res`,
    timeComplexity: 'O(M * 4 * 3^(L-1))',
    spaceComplexity: 'O(total words length)',
    editorialUrl: 'https://leetcode.com/problems/word-search-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 15. Backtracking (7 problems) ───────────────────────────────────
  {
    id: 101,
    title: 'Letter Combinations of a Phone Number',
    slug: 'letter-combinations-of-a-phone-number',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.',
    approach: 'Backtracking recursion iterating through phone keypad character mappings.',
    code: `def letterCombinations(digits):
    if not digits:
        return []
    phone = {'2': 'abc', '3': 'def', '4': 'ghi', '5': 'jkl', '6': 'mno', '7': 'pqrs', '8': 'tuv', '9': 'wxyz'}
    res = []
    def backtrack(idx, path):
        if idx == len(digits):
            res.append(''.join(path))
            return
        for ch in phone[digits[idx]]:
            path.append(ch)
            backtrack(idx + 1, path)
            path.pop()
    backtrack(0, [])
    return res`,
    timeComplexity: 'O(4^n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/letter-combinations-of-a-phone-number/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 102,
    title: 'Combinations',
    slug: 'combinations',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].',
    approach: 'Standard backtracking exploring numbers from start to n with remaining slots pruning.',
    code: `def combine(n, k):
    res = []
    def backtrack(start, path):
        if len(path) == k:
            res.append(list(path))
            return
        for num in range(start, n + 1):
            path.append(num)
            backtrack(num + 1, path)
            path.pop()
    backtrack(1, [])
    return res`,
    timeComplexity: 'O(C(n, k))',
    spaceComplexity: 'O(k)',
    editorialUrl: 'https://leetcode.com/problems/combinations/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 103,
    title: 'Permutations',
    slug: 'permutations',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta'],
    description: 'Given an array nums of distinct integers, return all the possible permutations.',
    approach: 'Backtracking with a visited boolean array or swapping elements in-place.',
    code: `def permute(nums):
    res = []
    def backtrack(path, used):
        if len(path) == len(nums):
            res.append(list(path))
            return
        for i, num in enumerate(nums):
            if not used[i]:
                used[i] = True
                path.append(num)
                backtrack(path, used)
                path.pop()
                used[i] = False
    backtrack([], [False] * len(nums))
    return res`,
    timeComplexity: 'O(n * n!)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/permutations/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 104,
    title: 'Combination Sum',
    slug: 'combination-sum',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple'],
    description: 'Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target.',
    approach: 'Backtracking passing current index so the same candidate can be reused.',
    code: `def combinationSum(candidates, target):
    res = []
    def backtrack(start, remain, path):
        if remain == 0:
            res.append(list(path))
            return
        if remain < 0:
            return
        for i in range(start, len(candidates)):
            path.append(candidates[i])
            backtrack(i, remain - candidates[i], path)
            path.pop()
    backtrack(0, target, [])
    return res`,
    timeComplexity: 'O(2^target)',
    spaceComplexity: 'O(target)',
    editorialUrl: 'https://leetcode.com/problems/combination-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 105,
    title: 'N-Queens II',
    slug: 'n-queens-ii',
    category: 'Backtracking',
    difficulty: 'Hard',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other. Return the number of distinct solutions.',
    approach: 'Row by row backtracking tracking attacked columns, main diagonals (r - c), and anti-diagonals (r + c).',
    code: `def totalNQueens(n):
    count = 0
    cols, diag1, diag2 = set(), set(), set()
    def backtrack(r):
        nonlocal count
        if r == n:
            count += 1
            return
        for c in range(n):
            if c in cols or (r - c) in diag1 or (r + c) in diag2:
                continue
            cols.add(c); diag1.add(r - c); diag2.add(r + c)
            backtrack(r + 1)
            cols.remove(c); diag1.remove(r - c); diag2.remove(r + c)
    backtrack(0)
    return count`,
    timeComplexity: 'O(n!)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/n-queens-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 106,
    title: 'Generate Parentheses',
    slug: 'generate-parentheses',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Amazon', 'Meta', 'Google', 'Microsoft'],
    description: 'Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.',
    approach: 'Backtracking: Can add "(" if open_count < n. Can add ")" if close_count < open_count.',
    code: `def generateParenthesis(n):
    res = []
    def backtrack(open_c, close_c, path):
        if len(path) == 2 * n:
            res.append(''.join(path))
            return
        if open_c < n:
            path.append('(')
            backtrack(open_c + 1, close_c, path)
            path.pop()
        if close_c < open_c:
            path.append(')')
            backtrack(open_c, close_c + 1, path)
            path.pop()
    backtrack(0, 0, [])
    return res`,
    timeComplexity: 'O(4^n / √n) Catalan number',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/generate-parentheses/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 107,
    title: 'Word Search',
    slug: 'word-search',
    category: 'Backtracking',
    difficulty: 'Medium',
    companies: ['Amazon', 'Microsoft', 'Google', 'Meta', 'Bloomberg'],
    description: 'Given an m x n grid of characters board and a string word, return true if word exists in the grid.',
    approach: '2D grid DFS backtracking marking visited cells with "#" and restoring afterward.',
    code: `def exist(board, word):
    m, n = len(board), len(board[0])
    def dfs(r, c, idx):
        if idx == len(word):
            return True
        if r < 0 or r >= m or c < 0 or c >= n or board[r][c] != word[idx]:
            return False
        temp = board[r][c]
        board[r][c] = '#'
        found = (dfs(r + 1, c, idx + 1) or
                 dfs(r - 1, c, idx + 1) or
                 dfs(r, c + 1, idx + 1) or
                 dfs(r, c - 1, idx + 1))
        board[r][c] = temp
        return found
    for r in range(m):
        for c in range(n):
            if dfs(r, c, 0):
                return True
    return False`,
    timeComplexity: 'O(m * n * 3^L)',
    spaceComplexity: 'O(L)',
    editorialUrl: 'https://leetcode.com/problems/word-search/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 16. Divide & Conquer (4 problems) ───────────────────────────────
  {
    id: 108,
    title: 'Convert Sorted Array to Binary Search Tree',
    slug: 'convert-sorted-array-to-binary-search-tree',
    category: 'Divide & Conquer',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.',
    approach: 'Pick middle element as root: root.left = build(left, mid - 1), root.right = build(mid + 1, right).',
    code: `def sortedArrayToBST(nums):
    def build(l, r):
        if l > r:
            return None
        mid = (l + r) // 2
        root = TreeNode(nums[mid])
        root.left = build(l, mid - 1)
        root.right = build(mid + 1, r)
        return root
    return build(0, len(nums) - 1)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(log n)',
    editorialUrl: 'https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 109,
    title: 'Sort List',
    slug: 'sort-list',
    category: 'Divide & Conquer',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'Microsoft'],
    description: 'Given the head of a linked list, return the list after sorting it in O(n log n) time and O(1) memory.',
    approach: 'Merge Sort on linked list: Split using fast & slow pointers, sort left and right halves recursively, then merge.',
    code: `def sortList(head):
    if not head or not head.next:
        return head
    slow, fast = head, head.next
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    mid = slow.next
    slow.next = None
    left = sortList(head)
    right = sortList(mid)
    dummy = ListNode()
    tail = dummy
    while left and right:
        if left.val < right.val:
            tail.next, left = left, left.next
        else:
            tail.next, right = right, right.next
        tail = tail.next
    tail.next = left or right
    return dummy.next`,
    timeComplexity: 'O(n log n)',
    spaceComplexity: 'O(log n)',
    editorialUrl: 'https://leetcode.com/problems/sort-list/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 110,
    title: 'Construct Quad Tree',
    slug: 'construct-quad-tree',
    category: 'Divide & Conquer',
    difficulty: 'Medium',
    companies: ['Google', 'Uber'],
    description: 'Given a n * n matrix grid of 0\'s and 1\'s only. We want to represent grid with a Quad-Tree.',
    approach: 'Divide grid into 4 quadrants. If all cells in region share the same value, return leaf node; otherwise construct 4 children.',
    code: `def constructQuadTree(grid):
    def build(r, c, length):
        val = grid[r][c]
        all_same = all(grid[r + i][c + j] == val for i in range(length) for j in range(length))
        if all_same:
            return Node(val == 1, True)
        half = length // 2
        return Node(True, False,
                    build(r, c, half),
                    build(r, c + half, half),
                    build(r + half, c, half),
                    build(r + half, c + half, half))
    return build(0, 0, len(grid))`,
    timeComplexity: 'O(n² log n)',
    spaceComplexity: 'O(log n)',
    editorialUrl: 'https://leetcode.com/problems/construct-quad-tree/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 111,
    title: 'Merge k Sorted Lists',
    slug: 'merge-k-sorted-lists',
    category: 'Divide & Conquer',
    difficulty: 'Hard',
    companies: ['Amazon', 'Meta', 'Google', 'Microsoft', 'Apple'],
    description: 'You are given an array of k linked-lists lists, each linked-list is sorted in ascending order. Merge all the linked-lists into one sorted linked-list.',
    approach: 'Min-heap of size k storing (node.val, id(node), node) or divide & conquer pairwise merge.',
    code: `import heapq

def mergeKLists(lists):
    h = []
    for i, l in enumerate(lists):
        if l:
            heapq.heappush(h, (l.val, i, l))
    dummy = ListNode(0)
    tail = dummy
    while h:
        val, i, node = heapq.heappop(h)
        tail.next = node
        tail = tail.next
        if node.next:
            heapq.heappush(h, (node.next.val, i, node.next))
    return dummy.next`,
    timeComplexity: 'O(N log k)',
    spaceComplexity: 'O(k)',
    editorialUrl: 'https://leetcode.com/problems/merge-k-sorted-lists/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 17. Kadane's Algorithm (2 problems) ─────────────────────────────
  {
    id: 112,
    title: 'Maximum Subarray',
    slug: 'maximum-subarray',
    category: "Kadane's Algorithm",
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta', 'Apple'],
    description: 'Given an integer array nums, find the subarray with the largest sum, and return its sum.',
    approach: 'Kadane\'s algorithm: cur_sum = max(num, cur_sum + num); max_sum = max(max_sum, cur_sum).',
    code: `def maxSubArray(nums):
    max_sum = cur_sum = nums[0]
    for num in nums[1:]:
        cur_sum = max(num, cur_sum + num)
        max_sum = max(max_sum, cur_sum)
    return max_sum`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/maximum-subarray/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 113,
    title: 'Maximum Sum Circular Subarray',
    slug: 'maximum-sum-circular-subarray',
    category: "Kadane's Algorithm",
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.',
    approach: 'Answer is either standard max_subarray or total_sum - min_subarray (wrapped sum).',
    code: `def maxSubarraySumCircular(nums):
    total = sum(nums)
    cur_max = cur_min = 0
    max_sum = min_sum = nums[0]
    for x in nums:
        cur_max = max(x, cur_max + x)
        max_sum = max(max_sum, cur_max)
        cur_min = min(x, cur_min + x)
        min_sum = min(min_sum, cur_min)
    return max_sum if max_sum < 0 else max(max_sum, total - min_sum)`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/maximum-sum-circular-subarray/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 18. Binary Search (7 problems) ──────────────────────────────────
  {
    id: 114,
    title: 'Search Insert Position',
    slug: 'search-insert-position',
    category: 'Binary Search',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon', 'Apple'],
    description: 'Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.',
    approach: 'Standard binary search. If target not found, left pointer points to insertion position.',
    code: `def searchInsert(nums, target):
    l, r = 0, len(nums) - 1
    while l <= r:
        mid = (l + r) // 2
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            l = mid + 1
        else:
            r = mid - 1
    return l`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/search-insert-position/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 115,
    title: 'Search a 2D Matrix',
    slug: 'search-a-2d-matrix',
    category: 'Binary Search',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given an m x n integer matrix matrix with sorted rows and first element of each row greater than last element of previous row, determine if target exists in O(log(m * n)).',
    approach: 'Treat 2D matrix as flattened 1D array: cell = matrix[mid // n][mid % n].',
    code: `def searchMatrix(matrix, target):
    m, n = len(matrix), len(matrix[0])
    l, r = 0, m * n - 1
    while l <= r:
        mid = (l + r) // 2
        val = matrix[mid // n][mid % n]
        if val == target:
            return True
        elif val < target:
            l = mid + 1
        else:
            r = mid - 1
    return False`,
    timeComplexity: 'O(log(m * n))',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/search-a-2d-matrix/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 116,
    title: 'Find Peak Element',
    slug: 'find-peak-element',
    category: 'Binary Search',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'A peak element is an element that is strictly greater than its neighbors. Given a 0-indexed integer array nums, find a peak element and return its index.',
    approach: 'Binary search: If nums[mid] < nums[mid + 1], peak must lie to the right; else to the left.',
    code: `def findPeakElement(nums):
    l, r = 0, len(nums) - 1
    while l < r:
        mid = (l + r) // 2
        if nums[mid] < nums[mid + 1]:
            l = mid + 1
        else:
            r = mid
    return l`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/find-peak-element/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 117,
    title: 'Search in Rotated Sorted Array',
    slug: 'search-in-rotated-sorted-array',
    category: 'Binary Search',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Apple'],
    description: 'Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.',
    approach: 'At least one half is always normally sorted. Check whether target lies within the sorted half.',
    code: `def searchRotated(nums, target):
    l, r = 0, len(nums) - 1
    while l <= r:
        mid = (l + r) // 2
        if nums[mid] == target:
            return mid
        if nums[l] <= nums[mid]:
            if nums[l] <= target < nums[mid]:
                r = mid - 1
            else:
                l = mid + 1
        else:
            if nums[mid] < target <= nums[r]:
                l = mid + 1
            else:
                r = mid - 1
    return -1`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/search-in-rotated-sorted-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 118,
    title: 'Find First and Last Position of Element in Sorted Array',
    slug: 'find-first-and-last-position-of-element-in-sorted-array',
    category: 'Binary Search',
    difficulty: 'Medium',
    companies: ['Meta', 'Google', 'Amazon', 'Microsoft'],
    description: 'Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value in O(log n).',
    approach: 'Two binary searches: One biased to find leftmost occurrence, second biased to find rightmost.',
    code: `def searchRange(nums, target):
    def findBound(is_first):
        l, r = 0, len(nums) - 1
        res = -1
        while l <= r:
            mid = (l + r) // 2
            if nums[mid] == target:
                res = mid
                if is_first:
                    r = mid - 1
                else:
                    l = mid + 1
            elif nums[mid] < target:
                l = mid + 1
            else:
                r = mid - 1
        return res
    return [findBound(True), findBound(False)]`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 119,
    title: 'Find Minimum in Rotated Sorted Array',
    slug: 'find-minimum-in-rotated-sorted-array',
    category: 'Binary Search',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given the sorted rotated array nums of unique elements, return the minimum element of this array.',
    approach: 'Binary search: Compare nums[mid] with nums[r]. If nums[mid] > nums[r], minimum is in right half; else left half.',
    code: `def findMin(nums):
    l, r = 0, len(nums) - 1
    while l < r:
        mid = (l + r) // 2
        if nums[mid] > nums[r]:
            l = mid + 1
        else:
            r = mid
    return nums[l]`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 120,
    title: 'Median of Two Sorted Arrays',
    slug: 'median-of-two-sorted-arrays',
    category: 'Binary Search',
    difficulty: 'Hard',
    companies: ['Google', 'Amazon', 'Microsoft', 'Meta', 'Apple'],
    description: 'Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays in O(log (m+n)).',
    approach: 'Binary search partition on the smaller array so left partition contains half of total elements.',
    code: `def findMedianSortedArrays(nums1, nums2):
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1
    m, n = len(nums1), len(nums2)
    l, r = 0, m
    while l <= r:
        i = (l + r) // 2
        j = (m + n + 1) // 2 - i
        max_left1 = float('-inf') if i == 0 else nums1[i - 1]
        min_right1 = float('inf') if i == m else nums1[i]
        max_left2 = float('-inf') if j == 0 else nums2[j - 1]
        min_right2 = float('inf') if j == n else nums2[j]
        if max_left1 <= min_right2 and max_left2 <= min_right1:
            if (m + n) % 2 == 1:
                return max(max_left1, max_left2)
            return (max(max_left1, max_left2) + min(min_right1, min_right2)) / 2.0
        elif max_left1 > min_right2:
            r = i - 1
        else:
            l = i + 1`,
    timeComplexity: 'O(log(min(m, n)))',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/median-of-two-sorted-arrays/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 19. Heap (4 problems) ───────────────────────────────────────────
  {
    id: 121,
    title: 'Kth Largest Element in an Array',
    slug: 'kth-largest-element-in-an-array',
    category: 'Heap',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'Microsoft'],
    description: 'Given an integer array nums and an integer k, return the kth largest element in the array.',
    approach: 'Maintain a min-heap of size k: push each number and pop smallest if heap size > k.',
    code: `import heapq

def findKthLargest(nums, k):
    h = []
    for num in nums:
        heapq.heappush(h, num)
        if len(h) > k:
            heapq.heappop(h)
    return h[0]`,
    timeComplexity: 'O(n log k)',
    spaceComplexity: 'O(k)',
    editorialUrl: 'https://leetcode.com/problems/kth-largest-element-in-an-array/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 122,
    title: 'IPO',
    slug: 'ipo',
    category: 'Heap',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google'],
    description: 'Find the maximum maximized capital after finishing at most k distinct projects.',
    approach: 'Sort projects by required capital. Push available projects into a max-heap of profits.',
    code: `import heapq

def findMaximizedCapital(k, w, profits, capital):
    projects = sorted(zip(capital, profits))
    max_heap = []
    i = 0
    n = len(projects)
    for _ in range(k):
        while i < n and projects[i][0] <= w:
            heapq.heappush(max_heap, -projects[i][1])
            i += 1
        if not max_heap:
            break
        w += -heapq.heappop(max_heap)
    return w`,
    timeComplexity: 'O(n log n + k log n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/ipo/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 123,
    title: 'Find K Pairs with Smallest Sums',
    slug: 'find-k-pairs-with-smallest-sums',
    category: 'Heap',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given two integer arrays nums1 and nums2 sorted in ascending order and an integer k, return the k pairs (u, v) with the smallest sums.',
    approach: 'Min-heap seeded with (nums1[i] + nums2[0], i, 0) for i in 0..min(k, len(nums1)).',
    code: `import heapq

def kSmallestPairs(nums1, nums2, k):
    if not nums1 or not nums2:
        return []
    h = []
    for i in range(min(k, len(nums1))):
        heapq.heappush(h, (nums1[i] + nums2[0], i, 0))
    res = []
    while h and len(res) < k:
        _, i, j = heapq.heappop(h)
        res.append([nums1[i], nums2[j]])
        if j + 1 < len(nums2):
            heapq.heappush(h, (nums1[i] + nums2[j + 1], i, j + 1))
    return res`,
    timeComplexity: 'O(k log k)',
    spaceComplexity: 'O(k)',
    editorialUrl: 'https://leetcode.com/problems/find-k-pairs-with-smallest-sums/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 124,
    title: 'Find Median from Data Stream',
    slug: 'find-median-from-data-stream',
    category: 'Heap',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google', 'Meta', 'Apple', 'Microsoft'],
    description: 'Design a data structure that supports adding numbers from a data stream and finding the median of the current numbers in O(1) time.',
    approach: 'Two heaps: max-heap (lower half) and min-heap (upper half). Keep balance diff <= 1.',
    code: `import heapq

class MedianFinder:
    def __init__(self):
        self.small = []  # max-heap
        self.large = []  # min-heap

    def addNum(self, num: int) -> None:
        heapq.heappush(self.small, -num)
        heapq.heappush(self.large, -heapq.heappop(self.small))
        if len(self.large) > len(self.small):
            heapq.heappush(self.small, -heapq.heappop(self.large))

    def findMedian(self) -> float:
        if len(self.small) > len(self.large):
            return -self.small[0]
        return (-self.small[0] + self.large[0]) / 2.0`,
    timeComplexity: 'O(log n) for addNum, O(1) for findMedian',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/find-median-from-data-stream/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 20. Bit Manipulation (6 problems) ───────────────────────────────
  {
    id: 125,
    title: 'Add Binary',
    slug: 'add-binary',
    category: 'Bit Manipulation',
    difficulty: 'Easy',
    companies: ['Meta', 'Amazon', 'Google'],
    description: 'Given two binary strings a and b, return their sum as a binary string.',
    approach: 'Sum bits from right to left with carry: bit = total % 2, carry = total // 2.',
    code: `def addBinary(a, b):
    i, j = len(a) - 1, len(b) - 1
    carry = 0
    res = []
    while i >= 0 or j >= 0 or carry:
        total = carry
        if i >= 0: total += int(a[i]); i -= 1
        if j >= 0: total += int(b[j]); j -= 1
        res.append(str(total % 2))
        carry = total // 2
    return ''.join(reversed(res))`,
    timeComplexity: 'O(max(n, m))',
    spaceComplexity: 'O(max(n, m))',
    editorialUrl: 'https://leetcode.com/problems/add-binary/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 126,
    title: 'Reverse Bits',
    slug: 'reverse-bits',
    category: 'Bit Manipulation',
    difficulty: 'Easy',
    companies: ['Apple', 'Amazon', 'Google'],
    description: 'Reverse bits of a given 32 bits unsigned integer.',
    approach: 'Iterate 32 times: shift result left and append n & 1, then shift n right.',
    code: `def reverseBits(n):
    res = 0
    for _ in range(32):
        res = (res << 1) | (n & 1)
        n >>= 1
    return res`,
    timeComplexity: 'O(1) (fixed 32 iterations)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/reverse-bits/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 127,
    title: 'Number of 1 Bits',
    slug: 'number-of-1-bits',
    category: 'Bit Manipulation',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Write a function that takes the binary representation of a positive integer and returns the number of set bits it has (Hamming weight).',
    approach: 'Brian Kernighan\'s algorithm: n &= (n - 1) clears the lowest set bit in each step.',
    code: `def hammingWeight(n):
    count = 0
    while n:
        n &= n - 1
        count += 1
    return count`,
    timeComplexity: 'O(k) where k is number of set bits',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/number-of-1-bits/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 128,
    title: 'Single Number',
    slug: 'single-number',
    category: 'Bit Manipulation',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft'],
    description: 'Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.',
    approach: 'XOR all elements: a ^ a = 0 and a ^ 0 = a. All duplicate numbers cancel out.',
    code: `def singleNumber(nums):
    res = 0
    for num in nums:
        res ^= num
    return res`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/single-number/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 129,
    title: 'Single Number II',
    slug: 'single-number-ii',
    category: 'Bit Manipulation',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element.',
    approach: 'Sum bits modulo 3 for each of the 32 bit positions, or use two bitmasks (ones, twos).',
    code: `def singleNumberII(nums):
    ones = twos = 0
    for num in nums:
        ones = (ones ^ num) & ~twos
        twos = (twos ^ num) & ~ones
    return ones`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/single-number-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 130,
    title: 'Bitwise AND of Numbers Range',
    slug: 'bitwise-and-of-numbers-range',
    category: 'Bit Manipulation',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.',
    approach: 'Find common binary prefix between left and right by right-shifting until they are equal.',
    code: `def rangeBitwiseAnd(left, right):
    shift = 0
    while left < right:
        left >>= 1
        right >>= 1
        shift += 1
    return left << shift`,
    timeComplexity: 'O(1) (at most 32 shifts)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/bitwise-and-of-numbers-range/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 21. Math (6 problems) ───────────────────────────────────────────
  {
    id: 131,
    title: 'Palindrome Number',
    slug: 'palindrome-number',
    category: 'Math',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given an integer x, return true if x is a palindrome, and false otherwise without converting to a string.',
    approach: 'Reverse the second half of the number mathematically and compare with the first half.',
    code: `def isPalindromeNum(x):
    if x < 0 or (x % 10 == 0 and x != 0):
        return False
    rev = 0
    while x > rev:
        rev = rev * 10 + x % 10
        x //= 10
    return x == rev or x == rev // 10`,
    timeComplexity: 'O(log10 n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/palindrome-number/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 132,
    title: 'Plus One',
    slug: 'plus-one',
    category: 'Math',
    difficulty: 'Easy',
    companies: ['Google', 'Amazon', 'Meta'],
    description: 'Given a large integer represented as an integer array digits, increment the large integer by one and return the resulting array of digits.',
    approach: 'Iterate from right: If digit < 9, increment and return. Else set to 0. If all 9s, prepend 1.',
    code: `def plusOne(digits):
    for i in range(len(digits) - 1, -1, -1):
        if digits[i] < 9:
            digits[i] += 1
            return digits
        digits[i] = 0
    return [1] + digits`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/plus-one/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 133,
    title: 'Factorial Trailing Zeroes',
    slug: 'factorial-trailing-zeroes',
    category: 'Math',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given an integer n, return the number of trailing zeroes in n! in O(log n) time.',
    approach: 'Count factors of 5 in n!: zeroes = n // 5 + n // 25 + n // 125 + ...',
    code: `def trailingZeroes(n):
    count = 0
    while n >= 5:
        count += n // 5
        n //= 5
    return count`,
    timeComplexity: 'O(log5 n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/factorial-trailing-zeroes/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 134,
    title: 'Sqrt(x)',
    slug: 'sqrtx',
    category: 'Math',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Bloomberg'],
    description: 'Given a non-negative integer x, return the square root of x rounded down to the nearest integer.',
    approach: 'Binary search between 1 and x.',
    code: `def mySqrt(x):
    if x < 2:
        return x
    l, r = 1, x // 2
    res = 1
    while l <= r:
        mid = (l + r) // 2
        if mid * mid <= x:
            res = mid
            l = mid + 1
        else:
            r = mid - 1
    return res`,
    timeComplexity: 'O(log x)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/sqrtx/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 135,
    title: 'Pow(x, n)',
    slug: 'powx-n',
    category: 'Math',
    difficulty: 'Medium',
    companies: ['Meta', 'Amazon', 'Google', 'Microsoft', 'LinkedIn'],
    description: 'Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).',
    approach: 'Binary exponentiation (fast power): If n is odd, x * (x^2)^((n-1)//2); if even, (x^2)^(n//2).',
    code: `def myPow(x, n):
    if n < 0:
        x = 1 / x
        n = -n
    res = 1
    cur = x
    while n > 0:
        if n % 2 == 1:
            res *= cur
        cur *= cur
        n //= 2
    return res`,
    timeComplexity: 'O(log n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/powx-n/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 136,
    title: 'Max Points on a Line',
    slug: 'max-points-on-a-line',
    category: 'Math',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.',
    approach: 'For each point, compute slopes to all other points using gcd(dx, dy) to avoid floating point inaccuracies.',
    code: `from math import gcd
from collections import defaultdict

def maxPoints(points):
    n = len(points)
    if n <= 2:
        return n
    max_pts = 1
    for i in range(n):
        slopes = defaultdict(int)
        for j in range(i + 1, n):
            dx = points[j][0] - points[i][0]
            dy = points[j][1] - points[i][1]
            g = gcd(dx, dy)
            slope = (dx // g, dy // g)
            slopes[slope] += 1
            max_pts = max(max_pts, slopes[slope] + 1)
    return max_pts`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/max-points-on-a-line/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 22. 1D DP (5 problems) ──────────────────────────────────────────
  {
    id: 137,
    title: 'Climbing Stairs',
    slug: 'climbing-stairs',
    category: '1D DP',
    difficulty: 'Easy',
    companies: ['Amazon', 'Google', 'Microsoft', 'Apple', 'Meta'],
    description: 'You are climbing a staircase. It takes n steps to reach the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?',
    approach: 'Fibonacci recurrence: dp[i] = dp[i-1] + dp[i-2] with two rolling variables.',
    code: `def climbStairs(n):
    if n <= 2:
        return n
    a, b = 1, 2
    for _ in range(3, n + 1):
        a, b = b, a + b
    return b`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/climbing-stairs/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 138,
    title: 'House Robber',
    slug: 'house-robber',
    category: '1D DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Determine the maximum amount of money you can rob tonight without alerting the police (cannot rob adjacent houses).',
    approach: 'dp[i] = max(dp[i-1], dp[i-2] + nums[i]) maintained with two rolling variables rob1 and rob2.',
    code: `def rob(nums):
    rob1 = rob2 = 0
    for num in nums:
        temp = max(rob2, rob1 + num)
        rob1 = rob2
        rob2 = temp
    return rob2`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/house-robber/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 139,
    title: 'Word Break',
    slug: 'word-break',
    category: '1D DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta', 'Microsoft', 'Bloomberg'],
    description: 'Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.',
    approach: 'Boolean DP: dp[i] is True if s[:i] can be segmented. For each valid dp[j], check if s[j:i] in wordDict.',
    code: `def wordBreak(s, wordDict):
    words = set(wordDict)
    dp = [False] * (len(s) + 1)
    dp[0] = True
    for i in range(1, len(s) + 1):
        for j in range(i):
            if dp[j] and s[j:i] in words:
                dp[i] = True
                break
    return dp[len(s)]`,
    timeComplexity: 'O(n² * k)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/word-break/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 140,
    title: 'Coin Change',
    slug: 'coin-change',
    category: '1D DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Apple', 'Meta'],
    description: 'Given an integer array coins representing coins of different denominations and an integer amount, return the fewest number of coins that you need to make up that amount.',
    approach: 'Bottom-up DP: dp[i] = min(dp[i], dp[i - coin] + 1). Initialize dp array with infinity.',
    code: `def coinChange(coins, amount):
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    for coin in coins:
        for x in range(coin, amount + 1):
            dp[x] = min(dp[x], dp[x - coin] + 1)
    return dp[amount] if dp[amount] != float('inf') else -1`,
    timeComplexity: 'O(amount * len(coins))',
    spaceComplexity: 'O(amount)',
    editorialUrl: 'https://leetcode.com/problems/coin-change/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 141,
    title: 'Longest Increasing Subsequence',
    slug: 'longest-increasing-subsequence',
    category: '1D DP',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon', 'Microsoft', 'Meta'],
    description: 'Given an integer array nums, return the length of the longest strictly increasing subsequence in O(n log n).',
    approach: 'Patience sorting with binary search (bisect_left): Maintain tails array where tails[i] is the smallest tail of all increasing subsequences of length i + 1.',
    code: `from bisect import bisect_left

def lengthOfLIS(nums):
    tails = []
    for x in nums:
        idx = bisect_left(tails, x)
        if idx == len(tails):
            tails.append(x)
        else:
            tails[idx] = x
    return len(tails)`,
    timeComplexity: 'O(n log n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/longest-increasing-subsequence/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },

  // ── 23. Multidimensional DP (9 problems) ────────────────────────────
  {
    id: 142,
    title: 'Triangle',
    slug: 'triangle',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Apple'],
    description: 'Given a triangle array, return the minimum path sum from top to bottom.',
    approach: 'Bottom-up DP: triangle[r][c] += min(triangle[r+1][c], triangle[r+1][c+1]). Top element contains min sum.',
    code: `def minimumTotal(triangle):
    for r in range(len(triangle) - 2, -1, -1):
        for c in range(len(triangle[r])):
            triangle[r][c] += min(triangle[r + 1][c], triangle[r + 1][c + 1])
    return triangle[0][0]`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(1) in-place',
    editorialUrl: 'https://leetcode.com/problems/triangle/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 143,
    title: 'Minimum Path Sum',
    slug: 'minimum-path-sum',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft'],
    description: 'Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.',
    approach: 'Grid DP in-place: grid[r][c] += min(grid[r-1][c], grid[r][c-1]).',
    code: `def minPathSum(grid):
    m, n = len(grid), len(grid[0])
    for c in range(1, n):
        grid[0][c] += grid[0][c - 1]
    for r in range(1, m):
        grid[r][0] += grid[r - 1][0]
    for r in range(1, m):
        for c in range(1, n):
            grid[r][c] += min(grid[r - 1][c], grid[r][c - 1])
    return grid[-1][-1]`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(1) in-place',
    editorialUrl: 'https://leetcode.com/problems/minimum-path-sum/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 144,
    title: 'Unique Paths II',
    slug: 'unique-paths-ii',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Meta'],
    description: 'You are given an m x n integer array grid. An obstacle is marked as 1. Return the number of possible unique paths to reach the bottom-right corner.',
    approach: 'DP with obstacle check: If cell == 1, dp = 0; else dp[r][c] = dp[r-1][c] + dp[r][c-1].',
    code: `def uniquePathsWithObstacles(obstacleGrid):
    if obstacleGrid[0][0] == 1 or obstacleGrid[-1][-1] == 1:
        return 0
    m, n = len(obstacleGrid), len(obstacleGrid[0])
    dp = [0] * n
    dp[0] = 1
    for r in range(m):
        for c in range(n):
            if obstacleGrid[r][c] == 1:
                dp[c] = 0
            elif c > 0:
                dp[c] += dp[c - 1]
    return dp[-1]`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/unique-paths-ii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 145,
    title: 'Longest Palindromic Substring',
    slug: 'longest-palindromic-substring',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given a string s, return the longest palindromic substring in s.',
    approach: 'Expand around center for all 2n - 1 possible centers (single character and two characters).',
    code: `def longestPalindrome(s):
    res = ""
    def expand(l, r):
        while l >= 0 and r < len(s) and s[l] == s[r]:
            l -= 1
            r += 1
        return s[l + 1:r]
    for i in range(len(s)):
        odd = expand(i, i)
        even = expand(i, i + 1)
        res = max(res, odd, even, key=len)
    return res`,
    timeComplexity: 'O(n²)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/longest-palindromic-substring/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 146,
    title: 'Interleaving String',
    slug: 'interleaving-string',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon'],
    description: 'Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.',
    approach: '2D boolean DP: dp[i][j] is True if s1[:i] and s2[:j] can interleave to form s3[:i+j].',
    code: `def isInterleave(s1, s2, s3):
    if len(s1) + len(s2) != len(s3):
        return False
    dp = [True] + [False] * len(s2)
    for j in range(1, len(s2) + 1):
        dp[j] = dp[j - 1] and s2[j - 1] == s3[j - 1]
    for i in range(1, len(s1) + 1):
        dp[0] = dp[0] and s1[i - 1] == s3[i - 1]
        for j in range(1, len(s2) + 1):
            dp[j] = (dp[j] and s1[i - 1] == s3[i + j - 1]) or (dp[j - 1] and s2[j - 1] == s3[i + j - 1])
    return dp[-1]`,
    timeComplexity: 'O(len(s1) * len(s2))',
    spaceComplexity: 'O(len(s2))',
    editorialUrl: 'https://leetcode.com/problems/interleaving-string/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 147,
    title: 'Edit Distance',
    slug: 'edit-distance',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Amazon', 'Google', 'Microsoft', 'Meta'],
    description: 'Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.',
    approach: 'Classic 2D Levenshtein distance: dp[i][j] = dp[i-1][j-1] if match else 1 + min(insert, delete, replace).',
    code: `def minDistance(word1, word2):
    m, n = len(word1), len(word2)
    dp = list(range(n + 1))
    for i in range(1, m + 1):
        new_dp = [i] + [0] * n
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                new_dp[j] = dp[j - 1]
            else:
                new_dp[j] = 1 + min(dp[j], new_dp[j - 1], dp[j - 1])
        dp = new_dp
    return dp[-1]`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/edit-distance/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 148,
    title: 'Best Time to Buy and Sell Stock III',
    slug: 'best-time-to-buy-and-sell-stock-iii',
    category: 'Multidimensional DP',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google'],
    description: 'Find the maximum profit you can achieve. You may complete at most two transactions.',
    approach: 'Track 4 state variables: buy1, sell1, buy2, sell2 in one pass.',
    code: `def maxProfitIII(prices):
    buy1 = buy2 = float('inf')
    sell1 = sell2 = 0
    for p in prices:
        buy1 = min(buy1, p)
        sell1 = max(sell1, p - buy1)
        buy2 = min(buy2, p - sell1)
        sell2 = max(sell2, p - buy2)
    return sell2`,
    timeComplexity: 'O(n)',
    spaceComplexity: 'O(1)',
    editorialUrl: 'https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 149,
    title: 'Best Time to Buy and Sell Stock IV',
    slug: 'best-time-to-buy-and-sell-stock-iv',
    category: 'Multidimensional DP',
    difficulty: 'Hard',
    companies: ['Amazon', 'Google'],
    description: 'You may complete at most k transactions. Return the maximum profit you can achieve.',
    approach: 'Maintain buy[k] and sell[k] arrays updated for each day price.',
    code: `def maxProfitIV(k, prices):
    if not prices or k == 0:
        return 0
    if k >= len(prices) // 2:
        return sum(max(0, prices[i] - prices[i - 1]) for i in range(1, len(prices)))
    buy = [float('inf')] * (k + 1)
    sell = [0] * (k + 1)
    for p in prices:
        for i in range(1, k + 1):
            buy[i] = min(buy[i], p - sell[i - 1])
            sell[i] = max(sell[i], p - buy[i])
    return sell[k]`,
    timeComplexity: 'O(n * k)',
    spaceComplexity: 'O(k)',
    editorialUrl: 'https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/editorial/?envType=study-plan-v2&envId=top-interview-150'
  },
  {
    id: 150,
    title: 'Maximal Square',
    slug: 'maximal-square',
    category: 'Multidimensional DP',
    difficulty: 'Medium',
    companies: ['Google', 'Amazon', 'Meta', 'Apple'],
    description: 'Given an m x n binary matrix filled with 0\'s and 1\'s, find the largest square containing only 1\'s and return its area.',
    approach: 'DP where dp[r][c] is the side length of maximal square with bottom-right corner at (r, c): dp[r][c] = 1 + min(dp[r-1][c], dp[r][c-1], dp[r-1][c-1]).',
    code: `def maximalSquare(matrix):
    if not matrix:
        return 0
    m, n = len(matrix), len(matrix[0])
    dp = [0] * (n + 1)
    max_side = prev = 0
    for r in range(1, m + 1):
        for c in range(1, n + 1):
            temp = dp[c]
            if matrix[r - 1][c - 1] == '1':
                dp[c] = 1 + min(dp[c], dp[c - 1], prev)
                max_side = max(max_side, dp[c])
            else:
                dp[c] = 0
            prev = temp
    return max_side * max_side`,
    timeComplexity: 'O(m * n)',
    spaceComplexity: 'O(n)',
    editorialUrl: 'https://leetcode.com/problems/maximal-square/editorial/?envType=study-plan-v2&envId=top-interview-150'
  }
];
