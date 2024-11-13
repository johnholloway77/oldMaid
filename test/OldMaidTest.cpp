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

    //    std::cout << player->name + " has this many cards: "
    //              << player->getHand()->size() << std::endl;
    //
    //    for (auto card : *player->getHand()) {
    //      std::cout << "\t Suit: " + Card::getSuit(card->suit) +
    //                       " Rank: " + Card::getRank(card->rank)
    //                << std::endl;
    //    }
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
