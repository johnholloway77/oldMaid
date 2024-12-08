//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//
#include <gtest/gtest.h>

#include <iostream>

#include "../include/Game.h"
#include "../include/OldMaid.h"
#include "../include/OldMaidUI.h"
#include "../include/Player.h"

TEST(OldMaidTest, DealCardsThreePlayerTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  om->dealCards(om->getPlayers());

  for (auto player : om->getPlayers()) {
    EXPECT_GE(player->getHand()->size(), 16);
    EXPECT_LE(player->getHand()->size(), 18);
  }

  delete p1;
  delete p2;
  delete p3;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidTest, HasSetOfZeroTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 0));

  delete p1;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidTest, HasSetOfOneTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());

  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));
  om->addPlayer(p1);

  EXPECT_FALSE(om->hasSet(p1->getHand(), 1));

  Card* c1 = new Card(Card::SPADE, Card::ACE);
  p1->addCard(c1);
  EXPECT_TRUE(om->hasSet(p1->getHand(), 1));

  delete p1;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidTest, HasSetOfTwoTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));
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
  delete old_maid_ui;
  delete d;
}

TEST(OldMaidTest, HasSetOfThreeTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));
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
  delete old_maid_ui;
}

TEST(OldMaidTest, CheckOutTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  // test branch coverage for checkIfOut when players.size() == 0
  om->checkIfPlayerOut();

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
  delete old_maid_ui;
}

TEST(OldMaidTest, CheckOutCardsDealtTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

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
  delete old_maid_ui;
}

TEST(OldMaidTest, IsOutTest) {
  Player* p1 = new Player("Player1_IsOutTest");
  Player* p2 = new Player("Player2_IsOutTest");

  Deck* d(new Deck());
  OldMaidUI* old_maid_ui(new OldMaidUI);

  d->create();
  d->shuffle();

  OldMaid* om(new OldMaid(old_maid_ui, d));

  om->addPlayer(p1);

  EXPECT_EQ(om->getPlayers().size(), 1);
  om->dealCards(om->getPlayers());

  om->addPlayer(p2);
  EXPECT_EQ(om->getPlayers().size(), 2);

  om->checkIfPlayerOut();

  EXPECT_EQ(p2->getHand()->size(), 0);

  EXPECT_EQ(om->getPlayers().size(), 0);

  EXPECT_TRUE(om->isOver());

  delete p1;
  delete p2;
  delete d;
  delete om;
  delete old_maid_ui;
}

TEST(OldMaidTest, GameOverTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());
  OldMaidUI* old_ui(new OldMaidUI());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_ui, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  om->dealCards(om->getPlayers());

  std::streambuf* original_stdout = std::cout.rdbuf();
  std::ostringstream discardedOutput;
  std::cout.rdbuf(discardedOutput.rdbuf());

  while (!om->getPlayers().empty()) {
    for (int i = 0; i < om->getPlayers().size() - 1; i++) {
      if (om->isOver()) {
        break;
      }

      om->beforeTurn(i, om->getPlayers().size());
    }
  }

  std::cout.rdbuf(original_stdout);

  EXPECT_TRUE(om->isOver());

  delete p1;
  delete p2;
  delete p3;
  delete d;
  delete old_ui;
}

TEST(OldMaidTest, DuringTurnTest) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player1");

  Deck* d(new Deck());

  d->create();
  d->shuffle();
  OldMaidUI* old_maid_ui(new OldMaidUI());
  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  om->addPlayer(p1);
  om->addPlayer(p2);

  om->dealCards(om->getPlayers());

  int player1CardsDealt = p1->getHand()->size();

  std::streambuf* original_stdout = std::cout.rdbuf();
  std::ostringstream discardedOutput;
  std::cout.rdbuf(discardedOutput.rdbuf());

  om->duringTurn(0);

  std::cout.rdbuf(original_stdout);

  EXPECT_LT(p1->getHand()->size(), player1CardsDealt);

  delete p1;
  delete p2;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidTest, StartTest) {
  Player* p1 = new Player("Player1");
  Player* p2(new Player("Player2"));
  OldMaidUI* old_maid_ui(new OldMaidUI());
  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  om->addPlayer(p1);
  om->addPlayer(p2);

  om->dealCards(om->getPlayers());

  EXPECT_EQ(om->getPlayers().size(), 2);
  EXPECT_EQ(om->getPlayersGoneOut().size(), 0);

  std::streambuf* original_stdout = std::cout.rdbuf();
  std::ostringstream discardedOutput;
  std::cout.rdbuf(discardedOutput.rdbuf());

  om->start();

  std::cout.rdbuf(original_stdout);

  EXPECT_EQ(om->getPlayers().size(), 0);
  EXPECT_EQ(om->getPlayersGoneOut().size(), 2);

  delete p1;
  delete p2;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidTest, HasSetTest) {
  Player* p1 = new Player("Player1");

  Deck* d(new Deck());
  OldMaidUI* old_ui(new OldMaidUI());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_ui, d));
  om->addPlayer(p1);

  om->dealCards(om->getPlayers());

  EXPECT_EQ(p1->getHand()->size(), 51);
  EXPECT_TRUE(om->hasSet(p1->getHand(), 2));

  delete p1;
  delete old_ui;
  delete d;
}
