/*
 * Problem Statement:
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow
 * another user, and is able to see the 10 most recent tweets in the user's news feed.
 * Implement the Twitter class:
 * - postTweet(userId, tweetId)
 * - getNewsFeed(userId): Retrieve 10 most recent tweet IDs (posted by user + followees).
 * - follow(followerId, followeeId)
 * - unfollow(followerId, followeeId)
 * (LeetCode 355: Design Twitter)
 * 
 * Asked in: Twitter/X, Amazon, Facebook/Meta, Microsoft
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

static int globalTimestamp = 0;

    static class Tweet {
        int id;
        int time;
        Tweet next;

        Tweet(int id) {
            this.id = id;
            this.time = globalTimestamp++;
            this.next = NULL;
        }
    }

    static class User {
        int id;
        Set<int> followed = new HashSet<>();
        Tweet tweetHead;

        User(int id) {
            this.id = id;
            follow(id); // Follow self so user sees their own tweets
        }

        void follow(int id) { followed.add(id); }
        void unfollow(int id) { if (id != this.id) followed.remove(id); }

        void post(int tweetId) {
            Tweet t = new Tweet(tweetId);
            t.next = tweetHead;
            tweetHead = t;
        }
    }

    static class Twitter {
        static const Map<int, User> userMap = new HashMap<>();

        void postTweet(int userId, int tweetId) {
            userMap.computeIfAbsent(userId, User::new).post(tweetId);
        }

        int* getNewsFeed(int userId) {
            int* feed = new ArrayList<>();
            User user = userMap.get(userId);
            if (user == NULL) return feed;

            // Max-Heap ordered by timestamp (most recent tweet on top)
            PriorityQueue<Tweet> heap = new PriorityQueue<>((a, b) -> int.compare(b.time, a.time));

            // Seed heap with head tweet of every followed user
            for (int followeeId : user.followed) {
                User followee = userMap.get(followeeId);
                if (followee != NULL && followee.tweetHead != NULL) {
                    heap.offer(followee.tweetHead);
                }
            }

            // K-way merge: extract up to 10 most recent tweets
            int count = 0;
            while (!heap.isEmpty() && count < 10) {
                Tweet top = heap.poll();
                feed.add(top.id);
                count++;
                if (top.next != NULL) {
                    heap.offer(top.next);
                }
            }

            return feed;
        }

        void follow(int followerId, int followeeId) {
            userMap.computeIfAbsent(followerId, User::new).follow(followeeId);
            userMap.computeIfAbsent(followeeId, User::new);
        }

        void unfollow(int followerId, int followeeId) {
            User u = userMap.get(followerId);
            if (u != NULL) u.unfollow(followeeId);
        }
    }

    int main(void) {
        Twitter twitter = new Twitter();

        printf("--- Twitter Feed System (K-Way Merge Heap) ---\n");
        twitter.postTweet(1, 101);
        twitter.postTweet(1, 102);

        printf("User 1 feed: %d\n", twitter.getNewsFeed(1)); // [102, 101]

        twitter.postTweet(2, 201);
        twitter.follow(1, 2);
        printf("User 1 feed after following User 2: %d\n", twitter.getNewsFeed(1)); // [201, 102, 101]

        twitter.unfollow(1, 2);
        printf("User 1 feed after unfollowing User 2: %d\n", twitter.getNewsFeed(1)); // [102, 101]
        return 0;
}

/*
 * Time Complexity: postTweet: O(1), getNewsFeed: O(F log F) where F is followed users count.
 * Space Complexity: O(U + T) where U is users count and T is total tweets stored.
 */
