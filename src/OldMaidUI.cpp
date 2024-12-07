//
// Created by jholloway on 11/14/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/OldMaidUI.h"

#include <list>
#include <random>
#ifdef __linux__
#include <algorithm>
#endif

unsigned int OldMaidUI::requestCard(Player* p, std::list<Card*>* hand) {
  std::random_device random_device;
  std::mt19937_64 gen(random_device());
  std::uniform_int_distribution<> distribution(0, hand->size() - 1);

  int randomPickedCardIndex = distribution(gen);

  if (randomPickedCardIndex < hand->size()) {
    auto card_iterator = hand->begin();
    std::advance(card_iterator, randomPickedCardIndex);

    Card* card = *card_iterator;
    hand->erase(card_iterator);
    p->addCard(card);

    std::cout << p->name << " picked the card " << Card::getRank(card->rank)
              << " of " << Card::getSuit(card->suit) << " from their neighbour"
              << std::endl;

    return 0;
  }

  std::cerr << p->name << " tried to take a card from an player with empty hand"
            << std::endl;

  return 1;
}

void OldMaidUI::playFailed(Player* player) {
  std::cout << player->name << " failed to gain a new pair and discard cards"
            << std::endl;
  std::cout << player->name << " hand size has increased to "
            << player->getHand()->size() << " cards" << std::endl;
};

void OldMaidUI::playSucceeded(const std::string& playString, Player* player) {
  std::cout << playString;
  std::cout << player->name << " hand size has decreased to "
            << player->getHand()->size() << " cards" << std::endl;
};

void OldMaidUI::outOfGame(Player* player) {
  std::cout << player->name + " is out of the game" << std::endl;
}

void OldMaidUI::showGameOutcome(std::vector<Player*> players) {
  std::cout
      << "The following players successfully dealt their hands and succeeded: "
      << std::endl;

  std::for_each(players.begin(), players.end() - 1,
                [](Player* p) { std::cout << "\t" << p->name << std::endl; });

  Player* p = players.back();

  std::cout << p->name << " was the old maid!!" << std::endl;
}
