/*
 * Problem Statement:
 * Implement the Publisher-Subscriber (Observer) Pattern:
 * - EventBus / TopicBroker managing channels/topics.
 * - Subscriber / Observer interface receiving notifications.
 * - Producers publishing events to specific topics.
 * - Support topic subscription, unsubscription, and multi-cast message delivery.
 * 
 * Asked in: Uber, Twitter/X, Netflix, LinkedIn, Amazon
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class PubSubObserverPattern {

    static class Event {
        private final String topic;
        private final String payload;

        public Event(String topic, String payload) {
            this.topic = topic;
            this.payload = payload;
        }

        public String getTopic() { return topic; }
        public String getPayload() { return payload; }

        @Override
        public String toString() {
            return "[" + topic + "] " + payload;
        }
    }

    interface Subscriber {
        void onMessage(Event event);
        String getName();
    }

    static class EventBus {
        private final Map<String, List<Subscriber>> subscribers = new HashMap<>();

        public void subscribe(String topic, Subscriber subscriber) {
            subscribers.computeIfAbsent(topic, k -> new ArrayList<>()).add(subscriber);
            System.out.printf("Subscriber '%s' registered for topic '%s'%n", subscriber.getName(), topic);
        }

        public void unsubscribe(String topic, Subscriber subscriber) {
            List<Subscriber> subs = subscribers.get(topic);
            if (subs != null) {
                subs.remove(subscriber);
                System.out.printf("Subscriber '%s' unregistered from topic '%s'%n", subscriber.getName(), topic);
            }
        }

        public void publish(Event event) {
            System.out.println("\n>>> Publishing Event: " + event);
            List<Subscriber> subs = subscribers.get(event.getTopic());
            if (subs == null || subs.isEmpty()) {
                System.out.println("No active subscribers for topic: " + event.getTopic());
                return;
            }

            for (Subscriber s : subs) {
                s.onMessage(event);
            }
        }
    }

    static class ConcreteSubscriber implements Subscriber {
        private final String name;

        public ConcreteSubscriber(String name) {
            this.name = name;
        }

        @Override
        public void onMessage(Event event) {
            System.out.printf("  -> [%s] received message: '%s'%n", name, event.getPayload());
        }

        @Override
        public String getName() {
            return name;
        }
    }

    public static void main(String[] args) {
        EventBus bus = new EventBus();

        Subscriber emailService = new ConcreteSubscriber("EmailNotificationService");
        Subscriber auditLogger = new ConcreteSubscriber("AuditLogService");
        Subscriber analytics = new ConcreteSubscriber("AnalyticsEngine");

        bus.subscribe("ORDER_CREATED", emailService);
        bus.subscribe("ORDER_CREATED", auditLogger);
        bus.subscribe("USER_LOGIN", auditLogger);
        bus.subscribe("USER_LOGIN", analytics);

        bus.publish(new Event("ORDER_CREATED", "Order #9921 placed by user bob@example.com"));
        bus.publish(new Event("USER_LOGIN", "User alice@example.com logged in from IP 192.168.1.5"));

        // Unsubscribe audit logger from order topic
        bus.unsubscribe("ORDER_CREATED", auditLogger);
        bus.publish(new Event("ORDER_CREATED", "Order #9922 placed by user charlie@example.com"));
    }
}

/*
 * Time Complexity: O(1) for subscribe; O(K) for publish where K is subscriber count for the topic.
 * Space Complexity: O(T * K) where T is topic count and K is subscriber count.
 */
