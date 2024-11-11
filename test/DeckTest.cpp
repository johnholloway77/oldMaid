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

TEST(DeckTest, GetCardTest) {
  std::unique_ptr<Deck> d(new Deck());

  d->create();
  EXPECT_EQ(d->size(), 52);

  std::unique_ptr<Card> c(d->getCard());

  EXPECT_EQ(d->size(), 51);

  EXPECT_TRUE(c);

  EXPECT_TRUE((c->suit >= 0) && (c->suit <= 3));
  EXPECT_TRUE((c->rank >= 0) && (c->rank <= 13));

  std::cout << "Suit: " + Card::getSuit(c->suit) +
                   " Rank: " + Card::getRank(c->rank)
            << std::endl;
}
