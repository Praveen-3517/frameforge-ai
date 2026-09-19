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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

class GenericRepositoryPattern {

    interface Identifiable<ID> {
        ID getId();
    }

    interface Repository<T extends Identifiable<ID>, ID> {
        T save(T entity);
        Optional<T> findById(ID id);
        List<T> findAll();
        boolean deleteById(ID id);
        long count();
    }

    static class InMemoryRepository<T extends Identifiable<ID>, ID> implements Repository<T, ID> {
        private final Map<ID, T> database = new HashMap<>();

        @Override
        public T save(T entity) {
            database.put(entity.getId(), entity);
            return entity;
        }

        @Override
        public Optional<T> findById(ID id) {
            return Optional.ofNullable(database.get(id));
        }

        @Override
        public List<T> findAll() {
            return new ArrayList<>(database.values());
        }

        @Override
        public boolean deleteById(ID id) {
            return database.remove(id) != null;
        }

        @Override
        public long count() {
            return database.size();
        }
    }

    // Domain Model: Customer
    static class Customer implements Identifiable<Long> {
        private final Long id;
        private final String name;
        private final String email;

        public Customer(Long id, String name, String email) {
            this.id = id;
            this.name = name;
            this.email = email;
        }

        @Override public Long getId() { return id; }
        @Override public String toString() {
            return "Customer[id=" + id + ", name='" + name + "', email='" + email + "']";
        }
    }

    public static void main(String[] args) {
        Repository<Customer, Long> customerRepo = new InMemoryRepository<>();

        System.out.println("--- Generic Repository Pattern Demo ---");
        customerRepo.save(new Customer(1L, "Alice Johnson", "alice@example.com"));
        customerRepo.save(new Customer(2L, "Bob Smith", "bob@example.com"));
        customerRepo.save(new Customer(3L, "Carol White", "carol@example.com"));

        System.out.println("Total customers: " + customerRepo.count());
        System.out.println("Find ID 2: " + customerRepo.findById(2L).orElse(null));

        customerRepo.deleteById(2L);
        System.out.println("After deleting ID 2, remaining count: " + customerRepo.count());
        System.out.println("All remaining customers: " + customerRepo.findAll());
    }
}

/*
 * Time Complexity: O(1) for save, findById, and deleteById via HashMap. O(N) for findAll().
 * Space Complexity: O(N) where N is number of stored entities.
 */
