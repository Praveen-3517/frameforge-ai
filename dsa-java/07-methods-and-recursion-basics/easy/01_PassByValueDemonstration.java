/**
 * Problem Statement:
 * Prove that Java is strictly Pass-by-Value using two experiments:
 * 1. Primitive Swap: Attempt to swap two primitive integers inside a method and show caller is unchanged.
 * 2. Object Reference Reassignment: Attempt to swap two objects by reassigning their parameters
 *    and prove that the caller's references remain unchanged.
 * 3. Object State Mutation: Show that calling a setter method DOES mutate the shared underlying heap object.
 *
 * Asked in: Amazon, Oracle, TCS, Infosys, Cognizant (Classic Core Java Question)
 *
 * Approach:
 * - Primitives: Bits are copied directly. Changes are local to the callee's stack frame.
 * - Object References: The pointer value (heap memory address) is copied by value.
 *   - Reassigning parameter `a = b` changes only the local stack pointer variable.
 *   - Mutating `a.value = 100` dereferences the shared heap address, affecting the heap state.
 */
class PassByValueDemonstration {

    static class Box {
        int value;
        Box(int value) { this.value = value; }
    }

    // Attempt 1: Swap primitives (Fails to affect caller)
    public static void swapPrimitives(int x, int y) {
        int temp = x;
        x = y;
        y = temp;
    }

    // Attempt 2: Swap object references via parameter reassignment (Fails to affect caller)
    public static void swapReferences(Box b1, Box b2) {
        Box temp = b1;
        b1 = b2;
        b2 = temp;
    }

    // Attempt 3: Mutate object state (Succeeds because heap object is modified)
    public static void mutateState(Box b) {
        b.value = 999;
    }

    public static void main(String[] args) {
        System.out.println("=== Proof: Java is Strictly Pass-by-Value ===");

        // Test 1: Primitives
        int a = 10, b = 20;
        System.out.println("1. Primitives Before Swap: a = " + a + ", b = " + b);
        swapPrimitives(a, b);
        System.out.println("   Primitives After Swap : a = " + a + ", b = " + b + " (Unchanged!)\n");

        // Test 2: Reference Reassignment
        Box box1 = new Box(100);
        Box box2 = new Box(200);
        System.out.println("2. Boxes Before Reference Swap: box1=" + box1.value + ", box2=" + box2.value);
        swapReferences(box1, box2);
        System.out.println("   Boxes After Reference Swap : box1=" + box1.value + ", box2=" + box2.value + " (Unchanged!)\n");

        // Test 3: State Mutation
        Box box3 = new Box(50);
        System.out.println("3. Box Before Mutation: value = " + box3.value);
        mutateState(box3);
        System.out.println("   Box After Mutation : value = " + box3.value + " (Mutated via shared heap reference!)");
    }
}

/*
 * Time Complexity: O(1) - Constant stack and reference assignments.
 * Space Complexity: O(1) - Small test objects on JVM heap.
 */
