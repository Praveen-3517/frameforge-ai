/**
 * Problem Statement:
 * Model a smart traffic light controller using a Java `enum` and modern `switch` expression.
 * The controller must support:
 * 1. State transitions: RED -> GREEN -> YELLOW -> RED.
 * 2. Duration lookup for each light state.
 * 3. Driver advisory action (e.g. "STOP", "PROCEED WITH CAUTION", "GO").
 * Demonstrate compile-time exhaustiveness checking (when switching over enums, modern Java
 * requires no default clause if all enum values are covered!).
 *
 * Asked in: Amazon, Oracle, Siemens, Bosch
 *
 * Approach:
 * - Define enum `TrafficLight { RED, YELLOW, GREEN }`.
 * - Transition method: `nextState(TrafficLight current)` returns the subsequent state.
 * - Modern switch expressions over enums enforce exhaustive matching. If a developer adds
 *   a new enum constant (e.g. FLASHING_RED), the compiler flags all unhandled switch expressions!
 */
class TrafficLightStateSwitch {

    enum TrafficLight {
        RED,
        YELLOW,
        GREEN
    }

    // State Transition: Exhaustive enum switch without default
    public static TrafficLight getNextState(TrafficLight current) {
        return switch (current) {
            case RED    -> TrafficLight.GREEN;
            case GREEN  -> TrafficLight.YELLOW;
            case YELLOW -> TrafficLight.RED;
        };
    }

    // Duration lookup in seconds
    public static int getDurationSeconds(TrafficLight light) {
        return switch (light) {
            case RED    -> 60;
            case GREEN  -> 45;
            case YELLOW -> 5;
        };
    }

    // Advisory action
    public static String getAdvisory(TrafficLight light) {
        return switch (light) {
            case RED    -> "STOP: Complete vehicle halt behind line.";
            case YELLOW -> "CAUTION: Prepare to stop; clear intersection.";
            case GREEN  -> "GO: Proceed if intersection is clear.";
        };
    }

    public static void main(String[] args) {
        System.out.println("=== Finite State Machine: Traffic Light Controller (Enum Switch) ===");

        TrafficLight state = TrafficLight.RED;
        System.out.println("Simulating 6 state transitions:");

        for (int cycle = 1; cycle <= 6; cycle++) {
            System.out.printf("Step %d: [%-6s] (Duration: %2ds) -> %s%n",
                    cycle, state, getDurationSeconds(state), getAdvisory(state));
            state = getNextState(state);
        }
    }
}

/*
 * Time Complexity: O(1) - Enum ordinal index lookup in JVM tableswitch.
 * Space Complexity: O(1) - Static enum singletons.
 */
