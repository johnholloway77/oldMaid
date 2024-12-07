//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/Game.h"

#include <random>

#include "../include/OldMaidUI.h"
#ifdef __linux__
#include <algorithm>
#endif

Game::~Game() {
  // Any necessary cleanup, if required
}

void Game::addPlayer(Player* player) {
  players.push_back(player);
}

const std::vector<Player*>& Game::getPlayers() {
  return players;
}

const std::vector<Player*>& Game::getPlayersGoneOut() {
  return playersGoneOut;
}

void Game::start() {
  // std::cout << "Game::start()  has not been implemented!\n";
}

void Game::checkIfPlayerOut() {
  if (players.empty()) {
    return;
  }

  auto iterator =
      std::remove_if(players.begin(), players.end(), [&](Player* p) {
        if (p->getHand()->empty()) {
#ifdef DEBUGPRINT
//          std::cout << "\nGame::checkIfPlayerOut" << std::endl;
//
//          std::cout << p->name << " has " << p->getHand()->size() << " cards"
//                    << std::endl;
#endif
          playersGoneOut.push_back(p);

          if (ui != nullptr) {
            ui->outOfGame(p);
          }

          return true;
        }
        return false;
      });

  players.erase(iterator, players.end());

  if (players.size() == 1) {
    std::cout << "\nGame Over!!\n" << std::endl;

    Player* oldMaidPlayer = players.back();

    players.clear();

#ifdef DEBUGPRINT
    std::cout << "Players vector size " << players.size() << std::endl;
#endif

    playersGoneOut.push_back(oldMaidPlayer);
  }
}

bool Game::hasSet(std::list<Card*>* hand, unsigned int size) {
  std::unordered_map<Card::Rank, int> cardmap;

  std::for_each(hand->begin(), hand->end(),
                [&cardmap](const Card* c) { cardmap[c->rank]++; });

  return std::any_of(cardmap.begin(), cardmap.end(),
                     [size](const auto& pair) { return pair.second >= size; });
}
