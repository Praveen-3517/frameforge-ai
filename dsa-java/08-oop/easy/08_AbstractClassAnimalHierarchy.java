/*
 * Problem Statement:
 * Demonstrate Abstraction using Abstract Classes:
 * - Create an abstract class Animal with abstract methods `makeSound()` and `move()`.
 * - Include concrete methods (e.g. `sleep()`) and constructor initializing species.
 * - Create concrete subclasses Dog, Bird, and Fish implementing abstract behaviors.
 * 
 * Asked in: Samsung, TCS, Infosys, Capgemini
 */

class AbstractClassAnimalHierarchy {

    static abstract class Animal {
        protected String name;

        public Animal(String name) {
            this.name = name;
        }

        // Abstract methods - every subclass MUST provide its own implementation
        public abstract void makeSound();
        public abstract void move();

        // Concrete method - common behavior inherited by all animals
        public void sleep() {
            System.out.println(name + " is sleeping peacefully. Zzz...");
        }

        public String getName() {
            return name;
        }
    }

    static class Dog extends Animal {
        public Dog(String name) {
            super(name);
        }

        @Override
        public void makeSound() {
            System.out.println(name + " barks: Woof! Woof!");
        }

        @Override
        public void move() {
            System.out.println(name + " runs briskly on four legs.");
        }
    }

    static class Bird extends Animal {
        public Bird(String name) {
            super(name);
        }

        @Override
        public void makeSound() {
            System.out.println(name + " chirps: Tweet! Chirp!");
        }

        @Override
        public void move() {
            System.out.println(name + " flaps its wings and soars through the sky.");
        }
    }

    static class Fish extends Animal {
        public Fish(String name) {
            super(name);
        }

        @Override
        public void makeSound() {
            System.out.println(name + " makes silent bubbles: Blub... blub...");
        }

        @Override
        public void move() {
            System.out.println(name + " glides smoothly underwater using its fins.");
        }
    }

    public static void main(String[] args) {
        // Animal animal = new Animal("Generic"); // Error: Animal is abstract; cannot be instantiated

        Animal[] menagerie = {
            new Dog("Buddy"),
            new Bird("Robin"),
            new Fish("Nemo")
        };

        System.out.println("--- Abstract Class Polymorphism ---");
        for (Animal a : menagerie) {
            System.out.println("\n[Animal: " + a.getName() + "]");
            a.makeSound();
            a.move();
            a.sleep();
        }
    }
}

/*
 * Time Complexity: O(1) per method invocation.
 * Space Complexity: O(N) array storage for N animal references.
 */
