//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//
#include <gtest/gtest.h>

#include <iostream>

#include "../include/Game.h"
#include "../include/OldMaid.h"
#include "../include/Player.h"

TEST(OldMaidTest, DealCardsThreePlayerTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  om->dealCards(om->getPlayers());

  for (auto player : om->getPlayers()) {
    EXPECT_GE(player->getHand()->size(), 16);
    EXPECT_LE(player->getHand()->size(), 18);

#ifdef DEBUGPRINT
    std::cout << "\nDealCardsThreePlayerTest" << std::endl;

    std::cout << player->name + " has this many cards: "
              << player->getHand()->size() << std::endl;

    for (auto card : *player->getHand()) {
      std::cout << "\t Suit: " + Card::getSuit(card->suit) +
                       " Rank: " + Card::getRank(card->rank)
                << std::endl;
    }
#endif
  }

  delete p1;
  delete p2;
  delete p3;
  delete d;
}

TEST(OldMaidTest, HasSetOfZeroTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 0));

  delete p1;
  delete d;
}

TEST(OldMaidTest, HasSetOfOneTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 1));

  Card* c1 = new Card(Card::SPADE, Card::ACE);
  p1->addCard(c1);
  EXPECT_TRUE(om->hasSet(p1->getHand(), 1));

  delete p1;
  delete d;
}

TEST(OldMaidTest, HasSetOfTwoTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 2));

  Card* c1 = new Card(Card::SPADE, Card::ACE);
  Card* c2 = new Card(Card::SPADE, Card::KING);
  Card* c3 = new Card(Card::SPADE, Card::QUEEN);
  Card* c4 = new Card(Card::SPADE, Card::JACK);

  p1->addCard(c1);
  p1->addCard(c2);
  p1->addCard(c3);
  p1->addCard(c4);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 2));

  Card* c5 = new Card(Card::DIAMOND, Card::ACE);

  p1->addCard(c5);

  EXPECT_TRUE(om->hasSet(p1->getHand(), 2));

  delete p1;

  delete d;
}

TEST(OldMaidTest, HasSetOfThreeTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 3));

  Card* c1 = new Card(Card::SPADE, Card::ACE);
  Card* c2 = new Card(Card::SPADE, Card::KING);
  Card* c3 = new Card(Card::SPADE, Card::QUEEN);
  Card* c4 = new Card(Card::SPADE, Card::JACK);

  p1->addCard(c1);
  p1->addCard(c2);
  p1->addCard(c3);
  p1->addCard(c4);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 2));

  Card* c5 = new Card(Card::DIAMOND, Card::ACE);

  p1->addCard(c5);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 3));

  Card* c6 = new Card(Card::HEART, Card::ACE);
  p1->addCard(c6);

  EXPECT_TRUE(om->hasSet(p1->getHand(), 3));

  delete p1;
  delete d;
}

TEST(OldMaidTest, CheckOutTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  EXPECT_EQ(om->getPlayers().size(), 3);

  om->checkIfPlayerOut();

  EXPECT_EQ(om->getPlayers().size(), 0);

  delete p1;
  delete p2;
  delete p3;
  delete d;
}

TEST(OldMaidTest, CheckOutCardsDealtTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  EXPECT_EQ(om->getPlayers().size(), 3);
  om->dealCards(om->getPlayers());

  om->checkIfPlayerOut();

  EXPECT_EQ(om->getPlayers().size(), 3);

  delete p1;
  delete p2;
  delete p3;
  delete d;
}

TEST(OldMaidTest, IsOutTest) {
  Player* p1 = new Player("Player1_IsOutTest");
  Player* p2 = new Player("Player2_IsOutTest");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);

  EXPECT_EQ(om->getPlayers().size(), 1);
  om->dealCards(om->getPlayers());

  om->addPlayer(p2);
  EXPECT_EQ(om->getPlayers().size(), 2);

  om->checkIfPlayerOut();

  EXPECT_EQ(p2->getHand()->size(), 0);

  EXPECT_EQ(om->getPlayers().size(), 1);
#ifdef DEBUGPRINT
  std::cout << "\nIsOutTest" << std::endl;
  std::cout << "players() size: " << om->getPlayers().size() << std::endl;
#endif

  EXPECT_TRUE(om->isOver());

  delete p1;
  delete p2;
  delete d;
}

TEST(OldMaidTest, BeforeTurnThreePlayerTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  om->dealCards(om->getPlayers());

  for (auto player : om->getPlayers()) {
    EXPECT_GE(player->getHand()->size(), 16);
    EXPECT_LE(player->getHand()->size(), 18);
  }

#ifdef DEBUGPRINT
  std::cout << "\nBeforeTurnThreePlayerTest" << std::endl;

  for (auto player : om->getPlayers()) {
    std::cout << player->name << " has " << player->getHand()->size()
              << " cards" << std::endl;
  }
#endif

  om->beforeTurn(0, om->getPlayers().size());

#ifdef DEBUGPRINT
  std::cout << "\nBeforeTurnThreePlayerTest" << std::endl;

  for (auto player : om->getPlayers()) {
    std::cout << player->name << " has " << player->getHand()->size()
              << " cards" << std::endl;
  }
#endif

  delete p1;
  delete p2;
  delete p3;
  delete d;
}

TEST(OldMaidTest, AfterTurnTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);

  om->afterTurn(p1, nullptr, nullptr);

  delete p1;
  delete d;
}

TEST(OldMaidTest, StartTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);

  om->start();

  delete p1;
  delete d;
}

TEST(OldMaidTest, TurnOverTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(nullptr, d));

  om->addPlayer(p1);

  EXPECT_FALSE(om->turnOver());

  delete p1;
  delete d;
}
