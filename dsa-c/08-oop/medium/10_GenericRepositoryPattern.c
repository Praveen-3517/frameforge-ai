/*
 * Problem Statement:
 * Implement an Enterprise Generic Repository Pattern in Java using Generics and OOP:
 * - Interface Repository<T, ID>:
 *   - save(T entity)
 *   - findById(ID id)
 *   - findAll()
 *   - deleteById(ID id)
 * - Identifiable interface requiring getId().
 * - InMemoryRepository<T extends Identifiable<ID>, ID> concrete implementation.
 * - Demonstrate type-safe CRUD operations on User and Order domain models.
 * 
 * Asked in: Amazon, Microsoft, PayPal, VMware
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

interface Identifiable<ID> {
        ID getId();
    }

    interface Repository<T extends Identifiable<ID>, ID> {
        T save(T entity);
        Optional<T> findById(ID id);
        int* findAll();
        bool deleteById(ID id);
        long long count();
    }

    static class InMemoryRepository<T extends Identifiable<ID>, ID> implements Repository<T, ID> {
        static const Map<ID, T> database = new HashMap<>();

        T save(T entity) {
            database.put(entity.getId(), entity);
            return entity;
        }

        Optional<T> findById(ID id) {
            return Optional.ofNullable(database.get(id));
        }

        int* findAll() {
            return new ArrayList<>(database.values());
        }

        bool deleteById(ID id) {
            return database.remove(id) != NULL;
        }

        long long count() {
            return database.size();
        }
    }

    // Domain Model: Customer
    static class Customer implements Identifiable<long long long long> {
        static const long long long long id;
        static const const char* name;
        static const const char* email;

        Customer(long long long long id, const char* name, const char* email) {
            this.id = id;
            this.name = name;
            this.email = email;
        }

        long long long long getId() { return id; }
        const char* toString() {
            return "Customer[id=" + id + ", name='" + name + "', email='" + email + "']";
        }
    }

    int main(void) {
        Repository<Customer, long long long long> customerRepo = new InMemoryRepository<>();

        printf("--- Generic Repository Pattern Demo ---\n");
        customerRepo.save(new Customer(1L, "Alice Johnson", "alice@example.com"));
        customerRepo.save(new Customer(2L, "Bob Smith", "bob@example.com"));
        customerRepo.save(new Customer(3L, "Carol White", "carol@example.com"));

        printf("Total customers: %d\n", customerRepo.count());
        printf("Find ID 2: %d\n", customerRepo.findById(2L).orElse(NULL));

        customerRepo.deleteById(2L);
        printf("After deleting ID 2, remaining count: %d\n", customerRepo.count());
        printf("All remaining customers: %d\n", customerRepo.findAll());
        return 0;
}

/*
 * Time Complexity: O(1) for save, findById, and deleteById via HashMap. O(N) for findAll().
 * Space Complexity: O(N) where N is number of stored entities.
 */
