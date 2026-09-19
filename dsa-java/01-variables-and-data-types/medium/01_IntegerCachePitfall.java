/**
 * Problem Statement:
 * Demonstrate Java's Integer Cache mechanism (-128 to 127).
 * Explain why comparing two `Integer` wrapper objects with `==` returns `true`
 * for values within [-128, 127] but returns `false` outside that range.
 *
 * Asked in: Amazon, Oracle, Goldman Sachs, Morgan Stanley
 *
 * Approach:
 * - Java specification mandates caching of `Integer` objects between -128 and 127 via `Integer.valueOf(int)`.
 * - Autoboxing (e.g., `Integer a = 100;`) calls `Integer.valueOf(100)`, returning the shared instance from the cache.
 * - For values >= 128 or <= -129, `Integer.valueOf()` instantiates a distinct new `Integer` object on the heap.
 * - Comparing with `==` checks reference equality (memory addresses), which produces unexpected `false` for values >= 128.
 * - Always use `.equals()` to check numeric equivalence.
 */
class IntegerCachePitfall {

    public static void testCacheComparison(int val) {
        Integer objA = val; // Autoboxing -> Integer.valueOf(val)
        Integer objB = val;

        boolean refEqual = (objA == objB);
        boolean valEqual = objA.equals(objB);

        System.out.printf("Value: %-5d | objA == objB (Reference): %-6b | objA.equals(objB) (Value): %-6b | IdentityHash A: %-10d | IdentityHash B: %-10d%n",
                val, refEqual, valEqual, System.identityHashCode(objA), System.identityHashCode(objB));
    }

    public static void main(String[] args) {
        System.out.println("=== Java Integer Cache (-128 to 127) Deep Dive ===");
        System.out.println("Testing values within the cache [-128, 127]:");
        testCacheComparison(50);
        testCacheComparison(127);
        testCacheComparison(-128);

        System.out.println("\nTesting values outside the cache (heap allocation triggered):");
        testCacheComparison(128);
        testCacheComparison(200);
        testCacheComparison(-129);

        System.out.println("\nKey Takeaway: In interviews, NEVER compare wrapper types (Integer, Long, Short) using `==`!");
    }
}

/*
 * Time Complexity: O(1) - Reference comparison and hash lookup.
 * Space Complexity: O(1) - Handled by the internal JVM IntegerCache array.
 */
