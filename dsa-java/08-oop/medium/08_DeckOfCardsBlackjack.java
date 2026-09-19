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

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class DeckOfCardsBlackjack {

    enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES }

    enum Rank {
        TWO(2), THREE(3), FOUR(4), FIVE(5), SIX(6), SEVEN(7),
        EIGHT(8), NINE(9), TEN(10), JACK(10), QUEEN(10), KING(10), ACE(11);

        private final int value;
        Rank(int value) { this.value = value; }
        public int getValue() { return value; }
    }

    static class Card {
        private final Suit suit;
        private final Rank rank;

        public Card(Suit suit, Rank rank) {
            this.suit = suit;
            this.rank = rank;
        }

        public Suit getSuit() { return suit; }
        public Rank getRank() { return rank; }

        @Override
        public String toString() {
            return rank + " of " + suit;
        }
    }

    static class Deck {
        private final List<Card> cards = new ArrayList<>();

        public Deck() {
            reset();
        }

        public void reset() {
            cards.clear();
            for (Suit s : Suit.values()) {
                for (Rank r : Rank.values()) {
                    cards.add(new Card(s, r));
                }
            }
        }

        public void shuffle() {
            Collections.shuffle(cards);
        }

        public Card dealCard() {
            if (cards.isEmpty()) throw new IllegalStateException("Deck is empty");
            return cards.remove(cards.size() - 1);
        }

        public int remainingCards() { return cards.size(); }
    }

    static class BlackjackHand {
        private final List<Card> hand = new ArrayList<>();

        public void addCard(Card card) {
            hand.add(card);
        }

        public int score() {
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

        public boolean isBusted() { return score() > 21; }
        public boolean isBlackjack() { return hand.size() == 2 && score() == 21; }

        public void display() {
            System.out.println("Hand: " + hand + " | Total Score: " + score()
                    + (isBlackjack() ? " [BLACKJACK!]" : isBusted() ? " [BUSTED!]" : ""));
        }
    }

    public static void main(String[] args) {
        Deck deck = new Deck();
        deck.shuffle();

        System.out.println("Total cards in fresh deck: " + deck.remainingCards());

        BlackjackHand playerHand = new BlackjackHand();
        playerHand.addCard(deck.dealCard());
        playerHand.addCard(deck.dealCard());
        System.out.print("Player: ");
        playerHand.display();

        // Testing Ace flexibility
        BlackjackHand testHand = new BlackjackHand();
        testHand.addCard(new Card(Suit.SPADES, Rank.ACE));
        testHand.addCard(new Card(Suit.HEARTS, Rank.NINE));
        testHand.addCard(new Card(Suit.CLUBS, Rank.FIVE));
        System.out.print("Ace Downgrade Test: ");
        testHand.display(); // Ace counts as 1 (1 + 9 + 5 = 15)
    }
}

/*
 * Time Complexity: O(1) card operations, O(1) hand evaluation (at most ~10 cards).
 * Space Complexity: O(1) fixed 52-card deck and small hand structures.
 */
