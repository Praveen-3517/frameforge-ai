/*
 * Problem Statement:
 * Demonstrate multiple interface implementation and Java 8+ interface features:
 * - Define interfaces Flyable and Swimmable.
 * - Show how a class Duck can implement both (Multiple Inheritance of Type).
 * - Demonstrate `default` methods, `static` methods, and resolving default method collisions.
 * 
 * Asked in: Amazon, Oracle, Walmart, Mindtree
 */

class InterfaceMultipleInheritance {

    interface Flyable {
        void fly();

        // Java 8 default method
        default void logActivity() {
            System.out.println("Log: Operating in Aerial mode.");
        }

        // Java 8 static utility method
        static double knotsToKmh(double knots) {
            return knots * 1.852;
        }
    }

    interface Swimmable {
        void swim();

        // Java 8 default method with colliding name
        default void logActivity() {
            System.out.println("Log: Operating in Aquatic mode.");
        }
    }

    // Implementing multiple interfaces
    static class Duck implements Flyable, Swimmable {
        private String name;

        public Duck(String name) {
            this.name = name;
        }

        @Override
        public void fly() {
            System.out.println(name + " takes flight across the lake.");
        }

        @Override
        public void swim() {
            System.out.println(name + " paddles gracefully through the water.");
        }

        // Disambiguate colliding default methods from both interfaces
        @Override
        public void logActivity() {
            System.out.println(name + " unified status log:");
            Flyable.super.logActivity();
            Swimmable.super.logActivity();
        }
    }

    public static void main(String[] args) {
        Duck mallard = new Duck("Mallard");

        System.out.println("--- Multiple Interfaces & Default Methods ---");
        mallard.fly();
        mallard.swim();
        mallard.logActivity();

        // Invoking interface static method
        double speedKnots = 25.0;
        System.out.printf("%nFlight speed %.1f knots = %.2f km/h (via Flyable static method)%n",
                speedKnots, Flyable.knotsToKmh(speedKnots));
    }
}

/*
 * Time Complexity: O(1) for interface method calls and conflict resolution.
 * Space Complexity: O(1) heap allocation per Duck object.
 */
