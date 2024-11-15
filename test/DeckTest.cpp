//
// Created by jholloway on 11/10/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include <gtest/gtest.h>

#include <iostream>

#include "../include/Card.h"
#include "../include/Deck.h"

TEST(DeckTest, ConstructorTest) {
  std::unique_ptr<Deck> d(new Deck());

  EXPECT_TRUE(d);
}

TEST(DeckTest, CreateDeckTest) {
  std::unique_ptr<Deck> d(new Deck());

  EXPECT_EQ(d->size(), 0);

  d->create();

  EXPECT_EQ(d->size(), 52);
}

TEST(DeckTest, GetCardEmptyDeckTest) {
  std::unique_ptr<Deck> d(new Deck());

  EXPECT_EQ(d->size(), (unsigned)0);
#ifdef DEBUGPRINT

  std::cout << "\nGetCardEmptyDeckTest:" << std::endl;
  std::cout << "deck size " << d->size() << std::endl;
#endif
  std::unique_ptr<Card> c(d->getCard());

  EXPECT_FALSE(c);
}

TEST(DeckTest, GetCardTest) {
  std::unique_ptr<Deck> d(new Deck());

  d->create();
  EXPECT_EQ(d->size(), 52);

  std::unique_ptr<Card> c(d->getCard());

  EXPECT_EQ(d->size(), 51);

  EXPECT_TRUE(c);

  EXPECT_TRUE((c->suit >= 0) && (c->suit <= 3));
  EXPECT_TRUE((c->rank >= 0) && (c->rank <= 13));

#ifdef DEBUGPRINT
  std::cout << "Suit: " + Card::getSuit(c->suit) +
                   " Rank: " + Card::getRank(c->rank)
            << std::endl;
#endif
}

TEST(DeckTest, RandomCardTest) {
  std::unique_ptr<Deck> d1(new Deck());
  std::unique_ptr<Deck> d2(new Deck());

  d1->create();
  EXPECT_EQ(d1->size(), 52);
  d2->create();
  EXPECT_EQ(d2->size(), 52);

  std::unique_ptr<Card> d1_c1(d1->getCard());
  std::unique_ptr<Card> d2_c1(d2->getCard());

  EXPECT_EQ(d1->size(), 51);
  EXPECT_EQ(d2->size(), 51);

  bool pickup1 = (Card::getSuit(d1_c1->suit) == Card::getSuit(d2_c1->suit)) &&
                 (Card::getRank(d1_c1->rank) == Card::getRank(d2_c1->rank));

  EXPECT_TRUE(pickup1);

#ifdef DEBUGPRINT
  std::cout << "\nRandomCardTest:" << std::endl;

  std::cout << "Card 1\n\tSuit: " + Card::getSuit(d1_c1->suit) +
                   " Rank: " + Card::getRank(d1_c1->rank)
            << std::endl
            << "Card 2\n\tSuit: " + Card::getSuit(d2_c1->suit) +
                   " Rank: " + Card::getRank(d2_c1->rank)
            << std::endl;
#endif

  d1->shuffle();
  d2->shuffle();

  /*
   * Because it is still possible to shuffle cards and get the same cards from
   * the top of the deck, it is best to test multiple pickups from the deck
   */

  std::unique_ptr<Card> d1_c2(d1->getCard());
  std::unique_ptr<Card> d2_c2(d2->getCard());

  bool pickup2 = (Card::getSuit(d1_c2->suit) == Card::getSuit(d2_c2->suit)) &&
                 (Card::getRank(d1_c2->rank) == Card::getRank(d2_c2->rank));

  EXPECT_EQ(d1->size(), 50);
  EXPECT_EQ(d2->size(), 50);

  std::unique_ptr<Card> d1_c3(d1->getCard());
  std::unique_ptr<Card> d2_c3(d2->getCard());

  bool pickup3 = (Card::getSuit(d1_c3->suit) == Card::getSuit(d2_c3->suit)) &&
                 (Card::getRank(d1_c3->rank) == Card::getRank(d2_c3->rank));

  std::unique_ptr<Card> d1_c4(d1->getCard());
  std::unique_ptr<Card> d2_c4(d2->getCard());

  bool pickup4 = (Card::getSuit(d1_c4->suit) == Card::getSuit(d2_c4->suit)) &&
                 (Card::getRank(d1_c4->rank) == Card::getRank(d2_c4->rank));

  std::unique_ptr<Card> d1_c5(d1->getCard());
  std::unique_ptr<Card> d2_c5(d2->getCard());

  bool pickup5 = (Card::getSuit(d1_c5->suit) == Card::getSuit(d2_c5->suit)) &&
                 (Card::getRank(d1_c5->rank) == Card::getRank(d2_c5->rank));

  std::unique_ptr<Card> d1_c6(d1->getCard());
  std::unique_ptr<Card> d2_c6(d2->getCard());

  bool pickup6 = (Card::getSuit(d1_c6->suit) == Card::getSuit(d2_c6->suit)) &&
                 (Card::getRank(d1_c6->rank) == Card::getRank(d2_c6->rank));

  /*
   * The odds of this randomly being true is 3.55 * 10^-9
   * (1/51 * 1/50 * 1/49 * 1/48 * 1/47)
   *
   * John likes those odds for a test
   */
  EXPECT_FALSE(pickup2 && pickup3 && pickup4 && pickup5 && pickup6);
#ifdef DEBUGPRINT
  std::cout << "\nRandomCardTest:" << std::endl;

  std::cout << "Deck 1 Card 6\n\tSuit: " + Card::getSuit(d1_c6->suit) +
                   " Rank: " + Card::getRank(d1_c6->rank)
            << std::endl
            << "Deck 2 Card 6\n\tSuit: " + Card::getSuit(d2_c6->suit) +
                   " Rank: " + Card::getRank(d2_c6->rank)
            << std::endl;
#endif
}
