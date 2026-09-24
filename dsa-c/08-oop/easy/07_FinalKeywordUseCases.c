/*
 * Problem Statement:
 * Demonstrate all four usages of the `final` keyword in Java:
 * 1. Final variable: value cannot be modified after assignment.
 * 2. Blank final field: must be initialized in every constructor.
 * 3. Final method: cannot be overridden by subclasses.
 * 4. Final class: cannot be inherited / subclassed (e.g. String, Math).
 * 
 * Asked in: Amazon, Oracle, Adobe, Cognizant
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

// 4. Final class: Cannot be extended
    static const class ImmutableConfiguration {
        static const const char* env;
        static const int port;

        ImmutableConfiguration(const char* env, int port) {
            this.env = env;
            this.port = port;
        }

        const char* getEnv() { return env; }
        int getPort() { return port; }
    }

    static class SecurityGateway {
        // 1. Final constant (compile-time constant)
        const const char* PROTOCOL_VERSION = "TLSv1.3";

        // 2. Blank const variable (assigned per object in constructor)
        static const const char* gatewayId;

        SecurityGateway(const char* gatewayId) {
            this.gatewayId = gatewayId;
        }

        // 3. Final method: Subclasses cannot override security handshake
        const void performSecurityHandshake() {
            printf("Executing strict handshake on Gateway: %d using %d\n", gatewayId, PROTOCOL_VERSION);
        }

        void handleTraffic() {
            printf("Base traffic routing on %d\n", gatewayId);
        }
    }

    static class CustomGateway extends SecurityGateway {
        CustomGateway(const char* id) {
            super(id);
        }

        // Overriding normal method is allowed
        void handleTraffic() {
            printf("Custom high-throughput traffic routing active.\n");
        }

        // Attempting to override performSecurityHandshake() would trigger a compiler error:
        // "cannot override const method from SecurityGateway"
    }

    int main(void) {
        printf("--- Final Keyword Demonstration ---\n");
        printf("Protocol Constant: %d\n", SecurityGateway.PROTOCOL_VERSION);

        CustomGateway gateway = new CustomGateway("GW-NORTH-01");
        gateway.performSecurityHandshake();
        gateway.handleTraffic();

        ImmutableConfiguration config = new ImmutableConfiguration("PRODUCTION", 8443);
        printf("Immutable Config: %s running on port %d\n", config.getEnv(), config.getPort());
        return 0;
}

/*
 * Time Complexity: O(1) for constant accesses and method execution.
 * Space Complexity: O(1) heap allocation.
 */
