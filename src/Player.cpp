//
// Created by jholloway on 11/11/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/Player.h"

#include <list>
#include <random>
#ifdef __linux__
#include <algorithm>
#endif

Player::~Player() {
  std::for_each(hand.begin(), hand.end(), [](Card* c) { delete c; });
  std::for_each(discardedCards.begin(), discardedCards.end(),
                [](Card* c) { delete c; });
}

void Player::addCard(Card* c) {
  if (c != nullptr) {
    hand.push_back(c);
  }
}

Card* Player::getCard(unsigned int index) {
  if (index < hand.size()) {
    auto card_iterator = hand.begin();
    std::advance(card_iterator, index);

    Card* card = *card_iterator;
    hand.erase(card_iterator);

    return card;
  }

  return nullptr;
}

std::list<Card*>* Player::getHand() {
  return &hand;
}

std::list<Card*>* Player::getDiscardedCards() {
  return &discardedCards;
}

void Player::takeCard(Player* otherPlayer) {
  std::random_device random_device;
  std::mt19937_64 gen(random_device());
  std::uniform_int_distribution<> distribution(
      0, otherPlayer->getHand()->size() - 1);
  int randomPickedCardIndex = distribution(gen);
  Card* c = otherPlayer->getCard(randomPickedCardIndex);
  if (c) {
    this->addCard(c);
  }
}
