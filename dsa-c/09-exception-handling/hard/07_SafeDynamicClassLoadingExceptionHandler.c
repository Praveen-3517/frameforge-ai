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

static class PluginLoadingException extends Exception {
        PluginLoadingException(const char* message, Throwable cause) {
            super(message, cause);
        }
    }

    Object loadAndInvokePlugin(const char* className, const char* methodName) throws PluginLoadingException {
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
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        } catch (NoSuchMethodException e) {
            throw new PluginLoadingException("Required hook method '" + methodName + "()' is missing.", e);
        } catch (IllegalAccessException e) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        } catch (InvocationTargetException e) {
            // The underlying method threw an exception! Unwrap with getTargetException()
            throw new PluginLoadingException("Plugin failed during execution: " + e.getTargetException().getMessage(), e.getTargetException());
        } catch (Exception e) {
            throw new PluginLoadingException("General failure initializing plugin: " + e.getMessage(), e);
        }
    }

    // Dummy plugin for test
    class SamplePlugin {
        const char* execute() {
            return "SamplePlugin loaded and executed flawlessly!";
        }
    }

    int main(void) {
        printf("--- Reflection & Dynamic Class Loading Exception Handling ---\n");

        // Case 1: Valid plugin
        try {
            Object res = loadAndInvokePlugin(
                    "SafeDynamicClassLoadingExceptionHandler$SamplePlugin", "execute");
            printf("Success: %d\n", res);
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
        return 0;
}

/*
 * Time Complexity: O(1) reflection lookup and dispatch.
 * Space Complexity: O(1) auxiliary reflection metadata.
 */
