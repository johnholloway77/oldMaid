//
// Created by jholloway on 11/10/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include <algorithm>
#include <random>

#include "../include/Deck.h"
#include "../include/Card.h"

Deck::~Deck(){
  std::for_each(deck.begin(), deck.end(), [](Card* c) {
    delete c;
  });
}

void Deck::shuffle() {
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(deck), std::end(deck), rng);
}

void Deck::addCard(Card* card){
  deck.push_back(card);
}

Card* Deck::getCard() {
  Card* c = deck.back();
  deck.pop_back();
  return c;
}

unsigned int Deck::size() {
  return deck.size();
}

void Deck::create(){
  for(int s = 0; s < 4; s++){
    for(int r = 0; r < 13; r++){
      addCard(new Card((Card::Suit)s, (Card::Rank)r));
    }
  }
}
