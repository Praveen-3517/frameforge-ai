/*
 * Problem Statement:
 * Handle the complex web of Reflection and Dynamic Class Loading Exceptions in Java:
 * - When dynamically loading plugins or classes at runtime:
 *   - ClassNotFoundException (class missing from classpath)
 *   - NoSuchMethodException (requested method does not exist)
 *   - IllegalAccessException (method/constructor is private or inaccessible)
 *   - InvocationTargetException (underlying invoked method threw an exception)
 *   - InstantiationException (attempting to instantiate abstract class or interface)
 * - Wrap these reflection exceptions into a clean PluginLoadingException with root cause diagnosis.
 * 
 * Asked in: Oracle, Spring Framework, Apache Foundation, Red Hat
 */

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

class SafeDynamicClassLoadingExceptionHandler {

    static class PluginLoadingException extends Exception {
        public PluginLoadingException(String message, Throwable cause) {
            super(message, cause);
        }
    }

    public static Object loadAndInvokePlugin(String className, String methodName) throws PluginLoadingException {
        try {
            // 1. Load class
            Class<?> clazz = Class.forName(className);

            // 2. Instantiate (using no-arg constructor)
            Object instance = clazz.getDeclaredConstructor().newInstance();

            // 3. Find method
            Method method = clazz.getMethod(methodName);

            // 4. Invoke
            return method.invoke(instance);

        } catch (ClassNotFoundException e) {
            throw new PluginLoadingException("Plugin class '" + className + "' could not be found on classpath.", e);
        } catch (NoSuchMethodException e) {
            throw new PluginLoadingException("Required hook method '" + methodName + "()' is missing.", e);
        } catch (IllegalAccessException e) {
            throw new PluginLoadingException("Access denied: Target class or method is not public.", e);
        } catch (InvocationTargetException e) {
            // The underlying method threw an exception! Unwrap with getTargetException()
            throw new PluginLoadingException("Plugin failed during execution: " + e.getTargetException().getMessage(), e.getTargetException());
        } catch (Exception e) {
            throw new PluginLoadingException("General failure initializing plugin: " + e.getMessage(), e);
        }
    }

    // Dummy plugin for test
    public static class SamplePlugin {
        public String execute() {
            return "SamplePlugin loaded and executed flawlessly!";
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Reflection & Dynamic Class Loading Exception Handling ---");

        // Case 1: Valid plugin
        try {
            Object res = loadAndInvokePlugin(
                    "SafeDynamicClassLoadingExceptionHandler$SamplePlugin", "execute");
            System.out.println("Success: " + res);
        } catch (PluginLoadingException e) {
            System.err.println("Error: " + e.getMessage());
        }

        // Case 2: Missing class
        try {
            loadAndInvokePlugin("com.nonexistent.FakePlugin", "run");
        } catch (PluginLoadingException e) {
            System.err.println("Missing Class Caught: " + e.getMessage());
        }

        // Case 3: Missing method
        try {
            loadAndInvokePlugin("SafeDynamicClassLoadingExceptionHandler$SamplePlugin", "invalidMethod");
        } catch (PluginLoadingException e) {
            System.err.println("Missing Method Caught: " + e.getMessage());
        }
    }
}

/*
 * Time Complexity: O(1) reflection lookup and dispatch.
 * Space Complexity: O(1) auxiliary reflection metadata.
 */
