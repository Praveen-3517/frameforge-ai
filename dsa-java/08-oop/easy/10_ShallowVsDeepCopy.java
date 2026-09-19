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

class ShallowVsDeepCopy {

    static class Address implements Cloneable {
        String city;
        String zipCode;

        Address(String city, String zipCode) {
            this.city = city;
            this.zipCode = zipCode;
        }

        @Override
        public Address clone() {
            try {
                return (Address) super.clone();
            } catch (CloneNotSupportedException e) {
                return new Address(this.city, this.zipCode);
            }
        }

        @Override
        public String toString() {
            return city + " (" + zipCode + ")";
        }
    }

    static class User implements Cloneable {
        String name;
        Address address;

        User(String name, Address address) {
            this.name = name;
            this.address = address;
        }

        // Shallow Copy via super.clone()
        public User shallowCopy() {
            try {
                return (User) super.clone();
            } catch (CloneNotSupportedException e) {
                return new User(this.name, this.address);
            }
        }

        // Deep Copy: Creates a brand new Address object
        public User deepCopy() {
            return new User(this.name, new Address(this.address.city, this.address.zipCode));
        }

        @Override
        public String toString() {
            return "User[name='" + name + "', address=" + address + "]";
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Shallow Copy Demonstration ---");
        Address originalAddr = new Address("Seattle", "98101");
        User user1 = new User("Alice", originalAddr);
        User shallowCopy = user1.shallowCopy();

        System.out.println("Original: " + user1);
        System.out.println("Shallow:  " + shallowCopy);

        // Modifying address in shallowCopy
        shallowCopy.address.city = "San Francisco";
        System.out.println("\nAfter modifying shallowCopy.address.city to 'San Francisco':");
        System.out.println("Original: " + user1 + " <- UNINTENTIONALLY MUTATED!");
        System.out.println("Shallow:  " + shallowCopy);

        System.out.println("\n--- Deep Copy Demonstration ---");
        Address addr2 = new Address("Boston", "02101");
        User user2 = new User("Bob", addr2);
        User deepCopy = user2.deepCopy();

        System.out.println("Original: " + user2);
        System.out.println("Deep:     " + deepCopy);

        // Modifying address in deepCopy
        deepCopy.address.city = "New York";
        System.out.println("\nAfter modifying deepCopy.address.city to 'New York':");
        System.out.println("Original: " + user2 + " <- SAFE, UNCHANGED");
        System.out.println("Deep:     " + deepCopy);
    }
}

/*
 * Time Complexity: O(1) for cloning shallow and deep references.
 * Space Complexity: O(1) new heap objects created.
 */
