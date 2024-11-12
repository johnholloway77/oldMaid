//
// Created by jholloway on 11/11/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/Player.h"

#include <list>
#ifdef __linux__
#include <algorithm>
#endif

Player::~Player() {
  std::for_each(hand.begin(), hand.end(), [](Card* c) { delete c; });
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
