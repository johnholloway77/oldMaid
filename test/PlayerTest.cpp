//
// Created by jholloway on 11/11/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include <gtest/gtest.h>

#include "../include/Deck.h"
#include "../include/Player.h"

TEST(PlayerTest, DefaultConstructorTest) {
  std::unique_ptr<Player> p(new Player("testPlayer"));

  EXPECT_TRUE(p);

  EXPECT_EQ(p->name, "testPlayer");
}

TEST(PlayerTest, AddCardTest) {
  std::unique_ptr<Player> p(new Player("testPlayer"));
  Card* c(new Card(Card::SPADE, Card::ACE));

  EXPECT_EQ(p->getHand()->size(), 0);

  p->addCard(c);
  EXPECT_EQ(p->getHand()->size(), 1);
}

TEST(PlayerTest, GetCardEmptyHand) {
  std::unique_ptr<Player> p(new Player("testPlayer"));
  Card* c = p->getCard(0);

  EXPECT_FALSE(c);
}

TEST(PlayerTest, GetCard) {
  std::unique_ptr<Player> p(new Player("testPlayer"));

  p->addCard(new Card(Card::SPADE, Card::ACE));
  Card* c = p->getCard(0);

  EXPECT_TRUE(c);

  delete c;
}

TEST(PlayerTest, GetCardIndexOutOfRange) {
  std::unique_ptr<Player> p(new Player("testPlayer"));

  p->addCard(new Card(Card::SPADE, Card::ACE));
  Card* c = p->getCard(1);

  EXPECT_FALSE(c);

  Card* c2 = p->getCard(0);
  delete c2;
}

TEST(PlayerTest, GetHandTest) {
  std::unique_ptr<Player> p(new Player("testPlayer"));
  const std::list<Card*>* hand = p->getHand();

  EXPECT_EQ(hand->size(), 0);

  p->addCard(new Card(Card::SPADE, Card::ACE));
  EXPECT_EQ(hand->size(), 1);
  /*
   * No need to delete card as its owner, p, will when destructor is called
   * by smart pointer
   */
}

TEST(PlayerTest, TakeCardTest) {
  Player* p1 = (new Player("TakeCardTest_Player1"));
  Player* p2 = (new Player("TakeCardTest_Player2"));
  Card* c(new Card(Card::SPADE, Card::ACE));

  EXPECT_EQ(p1->getHand()->size(), 0);
  EXPECT_EQ(p2->getHand()->size(), 0);

  p1->addCard(c);
  EXPECT_EQ(p1->getHand()->size(), 1);
  EXPECT_EQ(p2->getHand()->size(), 0);

  p2->takeCard(p1);
  EXPECT_EQ(p1->getHand()->size(), 0);
  EXPECT_EQ(p2->getHand()->size(), 1);

  delete p1;
  delete p2;
}
