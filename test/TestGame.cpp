//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//
#include <gtest/gtest.h>

#include <iostream>

#include "../include/Game.h"
#include "../include/OldMaid.h"
#include "../include/Player.h"

TEST(GameTest, DealCardsThreePlayerTest) {
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
