/*
 * Problem Statement:
 * Design a Car class that demonstrates foundational OOP concepts:
 * - State (attributes): make, model, year, speed
 * - Behaviors (methods): accelerate, brake, displayStatus
 * - Instantiation of multiple objects with independent states.
 * 
 * Asked in: Infosys, Wipro, TCS, Cognizant
 */

class ClassAndObjectBasics {

    static class Car {
        // Attributes (Instance Variables)
        private String make;
        private String model;
        private int year;
        private double speed;

        // Constructor
        public Car(String make, String model, int year) {
            this.make = make;
            this.model = model;
            this.year = year;
            this.speed = 0.0;
        }

        // Behaviors
        public void accelerate(double increment) {
            if (increment > 0) {
                this.speed += increment;
            }
        }

        public void brake(double decrement) {
            if (decrement > 0) {
                this.speed = Math.max(0.0, this.speed - decrement);
            }
        }

        public void displayStatus() {
            System.out.printf("[%d %s %s] Current speed: %.1f km/h%n", year, make, model, speed);
        }

        public double getSpeed() {
            return speed;
        }
    }

    public static void main(String[] args) {
        // Object Instantiation
        Car car1 = new Car("Toyota", "Corolla", 2022);
        Car car2 = new Car("Tesla", "Model 3", 2024);

        System.out.println("--- Initial State ---");
        car1.displayStatus();
        car2.displayStatus();

        System.out.println("\n--- Performing Actions ---");
        car1.accelerate(50);
        car2.accelerate(85);
        car1.displayStatus();
        car2.displayStatus();

        car1.brake(20);
        car2.brake(100);
        System.out.println("\n--- After Braking ---");
        car1.displayStatus();
        car2.displayStatus();
    }
}

/*
 * Time Complexity: O(1) for all car state transitions and queries.
 * Space Complexity: O(1) per instantiated car object on heap.
 */
