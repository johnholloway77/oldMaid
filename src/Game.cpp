//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/Game.h"

#include <random>
#ifdef __linux__
#include <algorithm>
#endif

Game::~Game() {
  // Any necessary cleanup, if required
}

void Game::dealCards(std::vector<Player*> p) {
  std::random_device random_device;
  std::mt19937_64 gen(random_device());
  std::uniform_int_distribution<> distribution(0, 3);

  int tossed_queen = distribution(gen);

  while (deck->size() > 0) {
    std::for_each(players.begin(), players.end(),
                  [this, &tossed_queen](Player* p) {
                    Card* c = deck->getCard();

                    if (c->rank == Card::QUEEN && c->suit == tossed_queen) {
                      delete c;
                      return;
                    }
                    p->addCard(c);
                  });
  }
}

void Game::addPlayer(Player* player) {
  players.push_back(player);
}

std::vector<Player*> Game::getPlayers() {
  return players;
}

void Game::start() {}

void Game::checkIfPlayerOut() {}

bool Game::hasSet(std::list<Card*>* hand, unsigned int size) {
  return false;
}
