/*
 * Problem Statement:
 * Design an Object-Oriented Standard Deck of Cards and a Blackjack Hand Evaluator:
 * - Enum Suit (CLUBS, DIAMONDS, HEARTS, SPADES).
 * - Enum Rank (TWO through ACE, with face values).
 * - Card: combination of Suit and Rank.
 * - Deck: 52 cards, shuffle(), dealCard().
 * - Hand and BlackjackHand: compute optimal hand value (handling Ace as 1 or 11).
 * 
 * Asked in: Amazon, Google, Zynga, EA Games
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

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES }

    enum Rank {
        TWO(2), THREE(3), FOUR(4), FIVE(5), SIX(6), SEVEN(7),
        EIGHT(8), NINE(9), TEN(10), JACK(10), QUEEN(10), KING(10), ACE(11);

        static const int value;
        Rank(int value) { this.value = value; }
        int getValue() { return value; }
    }

    static class Card {
        static const Suit suit;
        static const Rank rank;

        Card(Suit suit, Rank rank) {
            this.suit = suit;
            this.rank = rank;
        }

        Suit getSuit() { return suit; }
        Rank getRank() { return rank; }

        const char* toString() {
            return rank + " of " + suit;
        }
    }

    static class Deck {
        static const int* cards = new ArrayList<>();

        Deck() {
            reset();
        }

        void reset() {
            cards.clear();
            for (Suit s : Suit.values()) {
                for (Rank r : Rank.values()) {
                    cards.add(new Card(s, r));
                }
            }
        }

        void shuffle() {
            Collections.shuffle(cards);
        }

        Card dealCard() {
            if (cards.isEmpty()) fprintf(stderr, "Exception: invalid argument
"); return 0;
            return cards.remove(cards.size() - 1);
        }

        int remainingCards() { return cards.size(); }
    }

    static class BlackjackHand {
        static const int* hand = new ArrayList<>();

        void addCard(Card card) {
            hand.add(card);
        }

        int score() {
            int total = 0;
            int aceCount = 0;

            for (Card c : hand) {
                total += c.getRank().getValue();
                if (c.getRank() == Rank.ACE) aceCount++;
            }

            // Downgrade Aces from 11 to 1 if busted (> 21)
            while (total > 21 && aceCount > 0) {
                total -= 10;
                aceCount--;
            }

            return total;
        }

        bool isBusted() { return score() > 21; }
        bool isBlackjack() { return hand.size() == 2 && score() == 21; }

        void display() {
            printf("Hand: %d | Total Score: %d%d\n", hand, score(), (isBlackjack() ? " [BLACKJACK!]" : isBusted() ? " [BUSTED!]" : ""));
        }
    }

    int main(void) {
        Deck deck = new Deck();
        deck.shuffle();

        printf("Total cards in fresh deck: %d\n", deck.remainingCards());

        BlackjackHand playerHand = new BlackjackHand();
        playerHand.addCard(deck.dealCard());
        playerHand.addCard(deck.dealCard());
        printf("%s", "Player: ");
        playerHand.display();

        // Testing Ace flexibility
        BlackjackHand testHand = new BlackjackHand();
        testHand.addCard(new Card(Suit.SPADES, Rank.ACE));
        testHand.addCard(new Card(Suit.HEARTS, Rank.NINE));
        testHand.addCard(new Card(Suit.CLUBS, Rank.FIVE));
        printf("%s", "Ace Downgrade Test: ");
        testHand.display(); // Ace counts as 1 (1 + 9 + 5 = 15)
        return 0;
}

/*
 * Time Complexity: O(1) card operations, O(1) hand evaluation (at most ~10 cards).
 * Space Complexity: O(1) fixed 52-card deck and small hand structures.
 */
