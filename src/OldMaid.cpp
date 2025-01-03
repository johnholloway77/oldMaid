//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/OldMaid.h"

#include <random>
#include <unordered_map>

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
  int givingNum = static_cast<int>(playerNum) - 1 < 0
                      ? numPlayers - 1
                      : static_cast<int>(playerNum) - 1;

  auto givingPlayer = players.begin();
  std::advance(givingPlayer, givingNum);

  if (givingPlayer != players.end() && *givingPlayer) {
    auto givingHand = (*givingPlayer)->getHand();

    auto receivingPlayer = players.begin();
    std::advance(receivingPlayer, playerNum);

    ui->requestCard((*receivingPlayer), givingHand);
    checkIfPlayerOut();
  }
}

void OldMaid::duringTurn(unsigned int playerNum) {
  bool playSuccessful = false;
  std::string playString;

  auto player = players.begin();
  std::advance(player, playerNum);

  while (hasSet((*player)->getHand(), 2)) {
    if (isOver()) {
      return;
    }

    playSuccessful = true;

    std::unordered_map<Card::Rank, Card*> cardMap;
    std::vector<Card*> toDiscard;
    auto& hand = *(*player)->getHand();

    for (auto iterator = hand.begin(); iterator != hand.end();) {
      Card* c = *iterator;

      // find pairs of cards
      auto card_iterator = cardMap.find(c->rank);

      if (card_iterator != cardMap.end()) {
        Card* matchingCard = card_iterator->second;

        playString += (*player)->name +
                      " discarded the following pair:\n\tThe " +
                      Card::getRank(c->rank) + " of " + Card::getSuit(c->suit) +
                      " and the " + Card::getRank(matchingCard->rank) + " of " +
                      Card::getSuit(matchingCard->suit) + "\n";

        cardMap.erase(c->rank);

        toDiscard.push_back(c);
        toDiscard.push_back(matchingCard);

        iterator = hand.erase(iterator);

        auto matchingIterator =
            std::find(hand.begin(), hand.end(), matchingCard);
        if (matchingIterator != hand.end()) {
          hand.erase(matchingIterator);
        }

      } else {
        cardMap[c->rank] = c;
        ++iterator;
      }
    }

    std::for_each(toDiscard.begin(), toDiscard.end(), [player](Card* card) {
      (*player)->getDiscardedCards()->push_back(card);
    });
  }

  if (playSuccessful) {
    ui->playSucceeded(playString, (*player));

  } else {
    ui->playFailed(*player);
  }
}

bool OldMaid::isOver() {
  return (players.empty());
}

void OldMaid::start() {
  if (deck) {
    deck->create();
    deck->shuffle();

    if (!players.empty()) {
      dealCards(players);
    }
  }

  while (!isOver()) {
    for (int i = 0; i < players.size(); i++) {
      beforeTurn(i, getPlayers().size());
      duringTurn(i);
      checkIfPlayerOut();
    }
  }
}
