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

class FinalKeywordUseCases {

    // 4. Final class: Cannot be extended
    static final class ImmutableConfiguration {
        private final String env;
        private final int port;

        public ImmutableConfiguration(String env, int port) {
            this.env = env;
            this.port = port;
        }

        public String getEnv() { return env; }
        public int getPort() { return port; }
    }

    static class SecurityGateway {
        // 1. Final constant (compile-time constant)
        public static final String PROTOCOL_VERSION = "TLSv1.3";

        // 2. Blank final variable (assigned per object in constructor)
        private final String gatewayId;

        public SecurityGateway(String gatewayId) {
            this.gatewayId = gatewayId;
        }

        // 3. Final method: Subclasses cannot override security handshake
        public final void performSecurityHandshake() {
            System.out.println("Executing strict handshake on Gateway: " + gatewayId + " using " + PROTOCOL_VERSION);
        }

        public void handleTraffic() {
            System.out.println("Base traffic routing on " + gatewayId);
        }
    }

    static class CustomGateway extends SecurityGateway {
        public CustomGateway(String id) {
            super(id);
        }

        // Overriding normal method is allowed
        @Override
        public void handleTraffic() {
            System.out.println("Custom high-throughput traffic routing active.");
        }

        // Attempting to override performSecurityHandshake() would trigger a compiler error:
        // "cannot override final method from SecurityGateway"
    }

    public static void main(String[] args) {
        System.out.println("--- Final Keyword Demonstration ---");
        System.out.println("Protocol Constant: " + SecurityGateway.PROTOCOL_VERSION);

        CustomGateway gateway = new CustomGateway("GW-NORTH-01");
        gateway.performSecurityHandshake();
        gateway.handleTraffic();

        ImmutableConfiguration config = new ImmutableConfiguration("PRODUCTION", 8443);
        System.out.printf("Immutable Config: %s running on port %d%n", config.getEnv(), config.getPort());
    }
}

/*
 * Time Complexity: O(1) for constant accesses and method execution.
 * Space Complexity: O(1) heap allocation.
 */
