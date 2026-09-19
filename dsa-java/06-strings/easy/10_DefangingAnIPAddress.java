/**
 * Problem Statement:
 * Given a valid (IPv4) IP address, return a defanged version of that IP address.
 * A defanged IP address replaces every period "." with "[.]".
 * (LeetCode 1108: Defanging an IP Address).
 *
 * Example:
 * address = "1.1.1.1"         -> "1[.]1[.]1[.]1"
 * address = "255.100.50.0"     -> "255[.]100[.]50[.]0"
 *
 * Asked in: Amazon, Cisco, TCS, Infosys
 *
 * Approach:
 * - StringBuilder Character Traversal (O(N) Time, O(N) Space):
 *   Avoid `address.replaceAll("\\.", "[.]")` regex overhead, which compiles an internal regex pattern.
 *   Directly traverse `address.charAt(i)`:
 *   - If `ch == '.'`: append `"[.]"`
 *   - Else: append `ch`
 */
class DefangingAnIPAddress {

    public static String defangIPaddr(String address) {
        StringBuilder sb = new StringBuilder(address.length() + 6); // Exactly 3 periods replaced by 3 chars each (+6)

        for (int i = 0; i < address.length(); i++) {
            char ch = address.charAt(i);
            if (ch == '.') {
                sb.append("[.]");
            } else {
                sb.append(ch);
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 1108: Defanging an IP Address (StringBuilder) ===");

        String[] testIPs = { "1.1.1.1", "255.100.50.0", "192.168.1.1", "10.0.0.1" };

        for (String ip : testIPs) {
            System.out.printf("IP: %-15s ==> Defanged: %s%n", ip, defangIPaddr(ip));
        }
    }
}

/*
 * Time Complexity: O(N) - Linear pass across characters.
 * Space Complexity: O(N) - Pre-allocated StringBuilder.
 */
