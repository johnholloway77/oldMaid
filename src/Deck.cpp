//
// Created by jholloway on 11/10/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/Deck.h"

#include <random>
#ifdef __linux__
#include <algorithm>
#endif

Deck::~Deck() {
  std::for_each(deck.begin(), deck.end(), [](Card* c) { delete c; });
}

void Deck::shuffle() {
  std::random_device rd;
  std::seed_seq seed{rd(), rd(), rd(), rd()};
  std::mt19937_64 random_generator(seed);
  std::shuffle(deck.begin(), deck.end(), random_generator);
}

void Deck::addCard(Card* card) {
  deck.push_back(card);
}

Card* Deck::getCard() {
  if (!deck.empty()) {
    Card* c = deck.back();
    deck.pop_back();
    return c;
  }
  return nullptr;
}

unsigned int Deck::size() {
  return deck.size();
}

void Deck::create() {
  for (int s = 0; s < 4; s++) {
    for (int r = 0; r < 13; r++) {
      addCard(new Card((Card::Suit)s, (Card::Rank)r));
    }
  }
}
