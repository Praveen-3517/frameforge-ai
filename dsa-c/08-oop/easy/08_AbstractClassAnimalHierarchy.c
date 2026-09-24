/*
 * Problem Statement:
 * Demonstrate Abstraction using Abstract Classes:
 * - Create an abstract class Animal with abstract methods `makeSound()` and `move()`.
 * - Include concrete methods (e.g. `sleep()`) and constructor initializing species.
 * - Create concrete subclasses Dog, Bird, and Fish implementing abstract behaviors.
 * 
 * Asked in: Samsung, TCS, Infosys, Capgemini
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

static abstract class Animal {
        const char* name;

        Animal(const char* name) {
            this.name = name;
        }

        // Abstract methods - every subclass MUST provide its own implementation
        abstract void makeSound();
        abstract void move();

        // Concrete method - common behavior inherited by all animals
        void sleep() {
            printf("%d is sleeping peacefully. Zzz...\n", name);
        }

        const char* getName() {
            return name;
        }
    }

    static class Dog extends Animal {
        Dog(const char* name) {
            super(name);
        }

        void makeSound() {
            printf("%d barks: Woof! Woof!\n", name);
        }

        void move() {
            printf("%d runs briskly on four legs.\n", name);
        }
    }

    static class Bird extends Animal {
        Bird(const char* name) {
            super(name);
        }

        void makeSound() {
            printf("%d chirps: Tweet! Chirp!\n", name);
        }

        void move() {
            printf("%d flaps its wings and soars through the sky.\n", name);
        }
    }

    static class Fish extends Animal {
        Fish(const char* name) {
            super(name);
        }

        void makeSound() {
            printf("%d makes silent bubbles: Blub... blub...\n", name);
        }

        void move() {
            printf("%d glides smoothly underwater using its fins.\n", name);
        }
    }

    int main(void) {
        // Animal animal = new Animal("Generic"); // Error: Animal is abstract; cannot be instantiated

        Animal[] menagerie = {
            new Dog("Buddy"),
            new Bird("Robin"),
            new Fish("Nemo")
        };

        printf("--- Abstract Class Polymorphism ---\n");
        for (Animal a : menagerie) {
            printf("\n[Animal: " + a.getName() + "]\n");
            a.makeSound();
            a.move();
            a.sleep();
        }
        return 0;
}

/*
 * Time Complexity: O(1) per method invocation.
 * Space Complexity: O(N) array storage for N animal references.
 */
