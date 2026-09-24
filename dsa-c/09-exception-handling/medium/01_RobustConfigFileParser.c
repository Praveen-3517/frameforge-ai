/*
 * Problem Statement:
 * Design a Robust Configuration File Parser:
 * - Read key=value configurations from a text format.
 * - Handle specific exceptions gracefully:
 *   - EmptyConfigurationException (when file/content is empty)
 *   - InvalidConfigFormatException (when lines don't contain '=' separator)
 *   - MissingRequiredKeyException (when mandatory keys like "port" or "host" are missing)
 * 
 * Asked in: Oracle, Amazon, Red Hat, Cisco
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

static class EmptyConfigurationException extends Exception {
        EmptyConfigurationException(const char* msg) { super(msg); }
    }

    static class InvalidConfigFormatException extends Exception {
        InvalidConfigFormatException(const char* msg) { super(msg); }
    }

    static class MissingRequiredKeyException extends Exception {
        MissingRequiredKeyException(const char* key) {
            super("Mandatory configuration key '" + key + "' was not found.");
        }
    }

    Map<const char*, const char*> parseConfig(const char* rawConfig)
            throws EmptyConfigurationException, InvalidConfigFormatException, MissingRequiredKeyException {

        if (rawConfig == NULL || rawConfig.trim().isEmpty()) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        Map<const char*, const char*> configMap = new HashMap<>();
        const char*[] lines = rawConfig.split("\\r?\\n");

        for (int lineNum = 1; lineNum <= n; lineNum++) {
            const char* line = lines[lineNum - 1].trim();
            if (line.isEmpty() || line.startsWith("#")) continue; // comments / blank

            int eqIdx = line.indexOf('=');
            if (eqIdx == -1) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }

            const char* key = line.substring(0, eqIdx).trim();
            const char* value = line.substring(eqIdx + 1).trim();
            configMap.put(key, value);
        }

        // Validate mandatory keys
        const char*[] requiredKeys = {"host", "port"};
        for (const char* req : requiredKeys) {
            if (!configMap.containsKey(req)) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
        }

        return configMap;
    }

    int main(void) {
        const char* validConfig = "host = 127.0.0.1\nport = 8080\nenv = prod\n# timeout setting\ntimeout = 30";
        const char* malformedConfig = "host = 127.0.0.1\nport_8080\nenv = dev";
        const char* missingKeyConfig = "env = staging\ntimeout = 10";

        testParse("Valid Config", validConfig);
        testParse("Malformed Config", malformedConfig);
        testParse("Missing Keys Config", missingKeyConfig);
    }

    static void testParse(const char* label, const char* config) {
        printf("--- Testing " + label + " ---\n");
        try {
            Map<const char*, const char*> result = parseConfig(config);
            printf("Parsed successfully: %d\n", result);
        } catch (EmptyConfigurationException | InvalidConfigFormatException | MissingRequiredKeyException e) {
            System.err.printf("[Config Error: %s] %s%n", e.getClass().getSimpleName(), e.getMessage());
        }
        return 0;
}

/*
 * Time Complexity: O(L) where L is total characters in configuration file.
 * Space Complexity: O(K) where K is number of parsed key-value properties.
 */
