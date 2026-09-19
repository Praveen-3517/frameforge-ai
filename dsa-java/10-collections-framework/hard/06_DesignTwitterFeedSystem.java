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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

class DesignTwitterFeedSystem {

    private static int globalTimestamp = 0;

    static class Tweet {
        int id;
        int time;
        Tweet next;

        Tweet(int id) {
            this.id = id;
            this.time = globalTimestamp++;
            this.next = null;
        }
    }

    static class User {
        int id;
        Set<Integer> followed = new HashSet<>();
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
        private final Map<Integer, User> userMap = new HashMap<>();

        public void postTweet(int userId, int tweetId) {
            userMap.computeIfAbsent(userId, User::new).post(tweetId);
        }

        public List<Integer> getNewsFeed(int userId) {
            List<Integer> feed = new ArrayList<>();
            User user = userMap.get(userId);
            if (user == null) return feed;

            // Max-Heap ordered by timestamp (most recent tweet on top)
            PriorityQueue<Tweet> heap = new PriorityQueue<>((a, b) -> Integer.compare(b.time, a.time));

            // Seed heap with head tweet of every followed user
            for (int followeeId : user.followed) {
                User followee = userMap.get(followeeId);
                if (followee != null && followee.tweetHead != null) {
                    heap.offer(followee.tweetHead);
                }
            }

            // K-way merge: extract up to 10 most recent tweets
            int count = 0;
            while (!heap.isEmpty() && count < 10) {
                Tweet top = heap.poll();
                feed.add(top.id);
                count++;
                if (top.next != null) {
                    heap.offer(top.next);
                }
            }

            return feed;
        }

        public void follow(int followerId, int followeeId) {
            userMap.computeIfAbsent(followerId, User::new).follow(followeeId);
            userMap.computeIfAbsent(followeeId, User::new);
        }

        public void unfollow(int followerId, int followeeId) {
            User u = userMap.get(followerId);
            if (u != null) u.unfollow(followeeId);
        }
    }

    public static void main(String[] args) {
        Twitter twitter = new Twitter();

        System.out.println("--- Twitter Feed System (K-Way Merge Heap) ---");
        twitter.postTweet(1, 101);
        twitter.postTweet(1, 102);

        System.out.println("User 1 feed: " + twitter.getNewsFeed(1)); // [102, 101]

        twitter.postTweet(2, 201);
        twitter.follow(1, 2);
        System.out.println("User 1 feed after following User 2: " + twitter.getNewsFeed(1)); // [201, 102, 101]

        twitter.unfollow(1, 2);
        System.out.println("User 1 feed after unfollowing User 2: " + twitter.getNewsFeed(1)); // [102, 101]
    }
}

/*
 * Time Complexity: postTweet: O(1), getNewsFeed: O(F log F) where F is followed users count.
 * Space Complexity: O(U + T) where U is users count and T is total tweets stored.
 */
