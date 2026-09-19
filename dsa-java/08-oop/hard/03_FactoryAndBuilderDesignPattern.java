/*
 * Problem Statement:
 * Implement Creational Design Patterns:
 * 1. Abstract Factory Pattern: Cross-platform UI toolkit (Mac vs Windows Buttons and Checkboxes).
 * 2. Fluent Builder Pattern: HttpRequest builder with immutable state, method chaining,
 *    and mandatory field validation.
 * 
 * Asked in: Amazon, Microsoft, Apple, Airbnb, Square
 */

import java.util.HashMap;
import java.util.Map;

class FactoryAndBuilderDesignPattern {

    // --- PART 1: ABSTRACT FACTORY PATTERN ---
    interface Button { void render(); }
    interface Checkbox { void render(); }

    static class MacButton implements Button {
        public void render() { System.out.println("Rendering macOS rounded glass button."); }
    }
    static class MacCheckbox implements Checkbox {
        public void render() { System.out.println("Rendering macOS checkbox."); }
    }

    static class WinButton implements Button {
        public void render() { System.out.println("Rendering Windows Metro square button."); }
    }
    static class WinCheckbox implements Checkbox {
        public void render() { System.out.println("Rendering Windows Metro checkbox."); }
    }

    interface GUIFactory {
        Button createButton();
        Checkbox createCheckbox();
    }

    static class MacFactory implements GUIFactory {
        public Button createButton() { return new MacButton(); }
        public Checkbox createCheckbox() { return new MacCheckbox(); }
    }

    static class WinFactory implements GUIFactory {
        public Button createButton() { return new WinButton(); }
        public Checkbox createCheckbox() { return new WinCheckbox(); }
    }

    // --- PART 2: FLUENT BUILDER PATTERN ---
    static final class HttpRequest {
        private final String url;
        private final String method;
        private final Map<String, String> headers;
        private final String body;
        private final int timeoutMs;

        private HttpRequest(Builder builder) {
            this.url = builder.url;
            this.method = builder.method;
            this.headers = new HashMap<>(builder.headers);
            this.body = builder.body;
            this.timeoutMs = builder.timeoutMs;
        }

        public void execute() {
            System.out.printf("[%s] Request to %s | Headers: %s | Timeout: %dms%n",
                    method, url, headers, timeoutMs);
            if (body != null) System.out.println("Body: " + body);
        }

        public static class Builder {
            private String url;
            private String method = "GET"; // Default
            private final Map<String, String> headers = new HashMap<>();
            private String body;
            private int timeoutMs = 5000;

            public Builder url(String url) {
                this.url = url;
                return this;
            }

            public Builder method(String method) {
                this.method = method;
                return this;
            }

            public Builder addHeader(String key, String value) {
                this.headers.put(key, value);
                return this;
            }

            public Builder body(String body) {
                this.body = body;
                return this;
            }

            public Builder timeout(int timeoutMs) {
                this.timeoutMs = timeoutMs;
                return this;
            }

            public HttpRequest build() {
                if (url == null || url.trim().isEmpty()) {
                    throw new IllegalStateException("URL is a required parameter");
                }
                return new HttpRequest(this);
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 1. Abstract Factory Pattern ---");
        GUIFactory macFactory = new MacFactory();
        Button btn = macFactory.createButton();
        Checkbox chk = macFactory.createCheckbox();
        btn.render();
        chk.render();

        System.out.println("\n--- 2. Fluent Builder Pattern ---");
        HttpRequest req = new HttpRequest.Builder()
                .url("https://api.github.com/repos/frameforge")
                .method("POST")
                .addHeader("Authorization", "Bearer ghp_secret123")
                .addHeader("Content-Type", "application/json")
                .body("{\"name\": \"dsa-java\"}")
                .timeout(3000)
                .build();

        req.execute();
    }
}

/*
 * Time Complexity: O(1) for factories and builders.
 * Space Complexity: O(H) where H is number of headers configured on HTTP request.
 */
