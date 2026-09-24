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

static class Event {
        static const const char* topic;
        static const const char* payload;

        Event(const char* topic, const char* payload) {
            this.topic = topic;
            this.payload = payload;
        }

        const char* getTopic() { return topic; }
        const char* getPayload() { return payload; }

        const char* toString() {
            return "[" + topic + "] " + payload;
        }
    }

    interface Subscriber {
        void onMessage(Event event);
        const char* getName();
    }

    static class EventBus {
        static const Map<const char*, int*> subscribers = new HashMap<>();

        void subscribe(const char* topic, Subscriber subscriber) {
            subscribers.computeIfAbsent(topic, k -> new ArrayList<>()).add(subscriber);
            printf("Subscriber '%s' registered for topic '%s'\n", subscriber.getName(), topic);
        }

        void unsubscribe(const char* topic, Subscriber subscriber) {
            int* subs = subscribers.get(topic);
            if (subs != NULL) {
                subs.remove(subscriber);
                printf("Subscriber '%s' unregistered from topic '%s'\n", subscriber.getName(), topic);
            }
        }

        void publish(Event event) {
            printf("\n>>> Publishing Event: %d\n", event);
            int* subs = subscribers.get(event.getTopic());
            if (subs == NULL || subs.isEmpty()) {
                printf("No active subscribers for topic: %d\n", event.getTopic());
                return;
            }

            for (Subscriber s : subs) {
                s.onMessage(event);
            }
        }
    }

    static class ConcreteSubscriber implements Subscriber {
        static const const char* name;

        ConcreteSubscriber(const char* name) {
            this.name = name;
        }

        void onMessage(Event event) {
            printf("  -> [%s] received message: '%s'\n", name, event.getPayload());
        }

        const char* getName() {
            return name;
        }
    }

    int main(void) {
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
        return 0;
}

/*
 * Time Complexity: O(1) for subscribe; O(K) for publish where K is subscriber count for the topic.
 * Space Complexity: O(T * K) where T is topic count and K is subscriber count.
 */
