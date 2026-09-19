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

import java.util.HashMap;
import java.util.Map;

class RobustConfigFileParser {

    static class EmptyConfigurationException extends Exception {
        public EmptyConfigurationException(String msg) { super(msg); }
    }

    static class InvalidConfigFormatException extends Exception {
        public InvalidConfigFormatException(String msg) { super(msg); }
    }

    static class MissingRequiredKeyException extends Exception {
        public MissingRequiredKeyException(String key) {
            super("Mandatory configuration key '" + key + "' was not found.");
        }
    }

    public static Map<String, String> parseConfig(String rawConfig)
            throws EmptyConfigurationException, InvalidConfigFormatException, MissingRequiredKeyException {

        if (rawConfig == null || rawConfig.trim().isEmpty()) {
            throw new EmptyConfigurationException("Config content cannot be empty.");
        }

        Map<String, String> configMap = new HashMap<>();
        String[] lines = rawConfig.split("\\r?\\n");

        for (int lineNum = 1; lineNum <= lines.length; lineNum++) {
            String line = lines[lineNum - 1].trim();
            if (line.isEmpty() || line.startsWith("#")) continue; // comments / blank

            int eqIdx = line.indexOf('=');
            if (eqIdx == -1) {
                throw new InvalidConfigFormatException("Line " + lineNum + ": Missing '=' separator in \"" + line + "\"");
            }

            String key = line.substring(0, eqIdx).trim();
            String value = line.substring(eqIdx + 1).trim();
            configMap.put(key, value);
        }

        // Validate mandatory keys
        String[] requiredKeys = {"host", "port"};
        for (String req : requiredKeys) {
            if (!configMap.containsKey(req)) {
                throw new MissingRequiredKeyException(req);
            }
        }

        return configMap;
    }

    public static void main(String[] args) {
        String validConfig = "host = 127.0.0.1\nport = 8080\nenv = prod\n# timeout setting\ntimeout = 30";
        String malformedConfig = "host = 127.0.0.1\nport_8080\nenv = dev";
        String missingKeyConfig = "env = staging\ntimeout = 10";

        testParse("Valid Config", validConfig);
        testParse("Malformed Config", malformedConfig);
        testParse("Missing Keys Config", missingKeyConfig);
    }

    private static void testParse(String label, String config) {
        System.out.println("--- Testing " + label + " ---");
        try {
            Map<String, String> result = parseConfig(config);
            System.out.println("Parsed successfully: " + result);
        } catch (EmptyConfigurationException | InvalidConfigFormatException | MissingRequiredKeyException e) {
            System.err.printf("[Config Error: %s] %s%n", e.getClass().getSimpleName(), e.getMessage());
        }
    }
}

/*
 * Time Complexity: O(L) where L is total characters in configuration file.
 * Space Complexity: O(K) where K is number of parsed key-value properties.
 */
