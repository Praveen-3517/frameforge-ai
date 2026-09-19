# Topic 09: Exception Handling in Java

Exception handling is Java's robust mechanism to handle runtime errors, ensuring the normal flow of an application is maintained even when unexpected conditions occur.

---

## The Exception Hierarchy

```
                    Throwable
                   /         \
              Exception       Error (Fatal JVM errors: OutOfMemoryError, StackOverflowError)
             /         \
    Checked Exceptions  RuntimeException (Unchecked Exceptions)
    (IOException,       (NullPointerException,
     SQLException)       ArrayIndexOutOfBoundsException,
                         ArithmeticException,
                         IllegalArgumentException)
```

### 1. Checked vs. Unchecked Exceptions
- **Checked Exceptions**: Subclasses of `Exception` (excluding `RuntimeException`). The compiler forces you to handle them using `try-catch` or declare them using `throws`.
- **Unchecked Exceptions**: Subclasses of `RuntimeException`. Usually represent programming bugs or logic flaws (e.g. dividing by zero, dereferencing `null`). Compiler does not enforce handling.

---

## Core Keywords and Syntax

### `try-catch-finally`
```java
try {
    // Code that might throw an exception
} catch (SpecificException e) {
    // Handling specific exception
} catch (GeneralException e) {
    // Handling general fallback exception
} finally {
    // Always executes, regardless of exception or return statement
    // Used for releasing resources (closing files, sockets)
}
```

### `try-with-resources` (Java 7+)
Any class implementing `java.lang.AutoCloseable` or `java.io.Closeable` can be automatically closed:
```java
try (BufferedReader br = new BufferedReader(new FileReader("file.txt"))) {
    return br.readLine();
} // Automatically closed here without explicit finally
```

### Multi-Catch (Java 7+)
```java
try {
    process();
} catch (IOException | SQLException e) {
    logger.error("Data access error: ", e);
}
```

### `throw` vs. `throws`
- **`throw`**: Used explicitly inside method body to trigger an exception instance (`throw new IllegalArgumentException("Invalid");`).
- **`throws`**: Used in method declaration signature to declare which checked exceptions the method may propagate.

---

## Custom Exceptions
Extend `Exception` for checked exceptions or `RuntimeException` for unchecked domain exceptions.
Always include constructors accepting:
1. `(String message)`
2. `(String message, Throwable cause)` (Exception Chaining).

---

## Best Practices
1. Never catch generic `Throwable` or `Error`.
2. Avoid empty `catch` blocks (silent swallowing).
3. Do not use exceptions for standard control flow (exceptions are slow due to stack trace generation).
4. Clean up resources using `try-with-resources`.
5. Preserve original causes using exception chaining.
