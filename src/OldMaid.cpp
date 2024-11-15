//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/OldMaid.h"

#include <random>

#include "../include/Player.h"
#ifdef __linux__
#include <algorithm>
#endif

void OldMaid::dealCards(const std::vector<Player*> p) {
  std::random_device random_device;
  std::mt19937_64 gen(random_device());
  std::uniform_int_distribution<> distribution(0, 3);

  int tossed_queen = distribution(gen);

  while (deck->size() > 0) {
    std::for_each(players.begin(), players.end(),
                  [this, &tossed_queen](Player* p) {
                    if (deck->size() == 0) {
                      return;
                    }

                    Card* c = deck->getCard();

                    if (c->rank == Card::QUEEN && c->suit == tossed_queen) {
                      delete c;
                      return;
                    }
                    p->addCard(c);
                  });
  }
}

void OldMaid::beforeTurn(unsigned int playerNum, unsigned int numPlayers) {
  // Implementation of beforeTurn

  int givingNum = static_cast<int>(playerNum) - 1 < 0
                      ? numPlayers - 1
                      : static_cast<int>(playerNum) - 1;

  auto givingPlayer = players.begin();
  std::advance(givingPlayer, givingNum);

  auto receivingPlayer = players.begin();
  std::advance(receivingPlayer, playerNum);

  (*receivingPlayer)->takeCard((*givingPlayer));
}

void OldMaid::afterTurn(Player* currentPlayer, std::vector<Player*>* players,
                        Card* played) {
  // Implementation of afterTurn
}

bool OldMaid::turnOver() {
  // Implementation of turnOver// or some other logic
  return false;
}

bool OldMaid::isOver() {
  // Implementation of isOver
  return (players.size() == (unsigned)1);  // or some other logic
}
