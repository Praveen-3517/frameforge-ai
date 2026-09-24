/*
 * Problem Statement:
 * Implement Creational Design Patterns:
 * 1. Abstract Factory Pattern: Cross-platform UI toolkit (Mac vs Windows Buttons and Checkboxes).
 * 2. Fluent Builder Pattern: HttpRequest builder with immutable state, method chaining,
 *    and mandatory field validation.
 * 
 * Asked in: Amazon, Microsoft, Apple, Airbnb, Square
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

// --- PART 1: ABSTRACT FACTORY PATTERN ---
    interface Button { void render(); }
    interface Checkbox { void render(); }

    static class MacButton implements Button {
        void render() { printf("Rendering macOS rounded glass button.\n"); }
    }
    static class MacCheckbox implements Checkbox {
        void render() { printf("Rendering macOS checkbox.\n"); }
    }

    static class WinButton implements Button {
        void render() { printf("Rendering Windows Metro square button.\n"); }
    }
    static class WinCheckbox implements Checkbox {
        void render() { printf("Rendering Windows Metro checkbox.\n"); }
    }

    interface GUIFactory {
        Button createButton();
        Checkbox createCheckbox();
    }

    static class MacFactory implements GUIFactory {
        Button createButton() { return new MacButton(); }
        Checkbox createCheckbox() { return new MacCheckbox(); }
    }

    static class WinFactory implements GUIFactory {
        Button createButton() { return new WinButton(); }
        Checkbox createCheckbox() { return new WinCheckbox(); }
    }

    // --- PART 2: FLUENT BUILDER PATTERN ---
    static const class HttpRequest {
        static const const char* url;
        static const const char* method;
        static const Map<const char*, const char*> headers;
        static const const char* body;
        static const int timeoutMs;

        static HttpRequest(Builder builder) {
            this.url = builder.url;
            this.method = builder.method;
            this.headers = new HashMap<>(builder.headers);
            this.body = builder.body;
            this.timeoutMs = builder.timeoutMs;
        }

        void execute() {
            printf("[%s] Request to %s | Headers: %s | Timeout: %dms\n",
                    method, url, headers, timeoutMs);
            if (body != NULL) printf("Body: %d\n", body);
        }

        class Builder {
            static const char* url;
            static const char* method = "GET"; // Default
            static const Map<const char*, const char*> headers = new HashMap<>();
            static const char* body;
            static int timeoutMs = 5000;

            Builder url(const char* url) {
                this.url = url;
                return this;
            }

            Builder method(const char* method) {
                this.method = method;
                return this;
            }

            Builder addHeader(const char* key, const char* value) {
                this.headers.put(key, value);
                return this;
            }

            Builder body(const char* body) {
                this.body = body;
                return this;
            }

            Builder timeout(int timeoutMs) {
                this.timeoutMs = timeoutMs;
                return this;
            }

            HttpRequest build() {
                if (url == NULL || url.trim().isEmpty()) {
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                }
                return new HttpRequest(this);
            }
        }
    }

    int main(void) {
        printf("--- 1. Abstract Factory Pattern ---\n");
        GUIFactory macFactory = new MacFactory();
        Button btn = macFactory.createButton();
        Checkbox chk = macFactory.createCheckbox();
        btn.render();
        chk.render();

        printf("\n--- 2. Fluent Builder Pattern ---\n");
        HttpRequest req = new HttpRequest.Builder()
                .url("https://api.github.com/repos/frameforge")
                .method("POST")
                .addHeader("Authorization", "Bearer ghp_secret123")
                .addHeader("Content-Type", "application/json")
                .body("{\"name\": \"dsa-java\"}")
                .timeout(3000)
                .build();

        req.execute();
        return 0;
}

/*
 * Time Complexity: O(1) for factories and builders.
 * Space Complexity: O(H) where H is number of headers configured on HTTP request.
 */
