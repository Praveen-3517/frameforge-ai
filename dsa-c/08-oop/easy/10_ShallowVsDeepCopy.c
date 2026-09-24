/*
 * Problem Statement:
 * Demonstrate the critical difference between Shallow Copy and Deep Copy in Java:
 * - Define an Address class (mutable reference field).
 * - Define a User class containing an Address reference.
 * - Implement shallow copy (shared Address reference) vs deep copy (independent cloned Address).
 * - Demonstrate how modifying the address in a shallow copy corrupts the original object,
 *   while a deep copy remains completely isolated.
 * 
 * Asked in: Goldman Sachs, Morgan Stanley, Amazon, Adobe
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

static class Address implements Cloneable {
        const char* city;
        const char* zipCode;

        Address(const char* city, const char* zipCode) {
            this.city = city;
            this.zipCode = zipCode;
        }

        Address clone() {
            try {
                return (Address) super.clone();
            } catch (CloneNotSupportedException e) {
                return new Address(this.city, this.zipCode);
            }
        }

        const char* toString() {
            return city + " (" + zipCode + ")";
        }
    }

    static class User implements Cloneable {
        const char* name;
        Address address;

        User(const char* name, Address address) {
            this.name = name;
            this.address = address;
        }

        // Shallow Copy via super.clone()
        User shallowCopy() {
            try {
                return (User) super.clone();
            } catch (CloneNotSupportedException e) {
                return new User(this.name, this.address);
            }
        }

        // Deep Copy: Creates a brand new Address object
        User deepCopy() {
            return new User(this.name, new Address(this.address.city, this.address.zipCode));
        }

        const char* toString() {
            return "User[name='" + name + "', address=" + address + "]";
        }
    }

    int main(void) {
        printf("--- Shallow Copy Demonstration ---\n");
        Address originalAddr = new Address("Seattle", "98101");
        User user1 = new User("Alice", originalAddr);
        User shallowCopy = user1.shallowCopy();

        printf("Original: %d\n", user1);
        printf("Shallow:  %d\n", shallowCopy);

        // Modifying address in shallowCopy
        shallowCopy.address.city = "San Francisco";
        printf("\nAfter modifying shallowCopy.address.city to 'San Francisco':\n");
        printf("Original: " + user1 + " <- UNINTENTIONALLY MUTATED!\n");
        printf("Shallow:  %d\n", shallowCopy);

        printf("\n--- Deep Copy Demonstration ---\n");
        Address addr2 = new Address("Boston", "02101");
        User user2 = new User("Bob", addr2);
        User deepCopy = user2.deepCopy();

        printf("Original: %d\n", user2);
        printf("Deep:     %d\n", deepCopy);

        // Modifying address in deepCopy
        deepCopy.address.city = "New York";
        printf("\nAfter modifying deepCopy.address.city to 'New York':\n");
        printf("Original: " + user2 + " <- SAFE, UNCHANGED\n");
        printf("Deep:     %d\n", deepCopy);
        return 0;
}

/*
 * Time Complexity: O(1) for cloning shallow and deep references.
 * Space Complexity: O(1) new heap objects created.
 */
