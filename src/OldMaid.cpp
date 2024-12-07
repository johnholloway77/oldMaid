//
// Created by jholloway on 11/12/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/OldMaid.h"

#include <random>
#include <unordered_map>

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

#ifdef DEBUGPRINT

  if (*receivingPlayer) {
    std::cout << "Receiving Player Name: " << (*receivingPlayer)->name
              << std::endl;
  }

  if (*givingPlayer) {
    std::cout << "Giving Player name: " << (*givingPlayer)->name << std::endl;
  }

#endif

  ui->requestCard((*receivingPlayer), (*givingPlayer)->getHand());
  checkIfPlayerOut();
}

void OldMaid::duringTurn(unsigned int playerNum) {
  auto player = players.begin();
  std::advance(player, playerNum);

  while (hasSet((*player)->getHand(), 2)) {
    std::unordered_map<Card::Rank, Card*> cardMap;
    std::vector<Card*> toDiscard;

    for (auto iterator = (*player)->getHand()->begin();
         iterator != (*player)->getHand()->end();) {
      Card* c = *iterator;

      // find pairs of cards
      auto card_iterator = cardMap.find(c->rank);

      if (card_iterator != cardMap.end()) {
        Card* matchingCard = card_iterator->second;

        std::string success_string =
            (*player)->name + " discarded the following pair:\n\tThe " +
            Card::getRank(c->rank) + " of " + Card::getSuit(c->suit) +
            " and the " + Card::getRank(matchingCard->rank) + " of " +
            Card::getSuit(matchingCard->suit);

        std::cout << success_string << std::endl;

        cardMap.erase(c->rank);

        toDiscard.push_back(c);
        toDiscard.push_back(matchingCard);

        iterator = (*player)->getHand()->erase(iterator);
        (*player)->getHand()->erase(
            std::remove_if((*player)->getHand()->begin(),
                           (*player)->getHand()->end(),
                           [&c, &matchingCard](Card* cardPointer) {
                             return cardPointer == matchingCard;
                           }),
            (*player)->getHand()->end());

      } else {
        cardMap[c->rank] = c;
        ++iterator;
      }
    }

    std::for_each(toDiscard.begin(), toDiscard.end(), [player](Card* card) {
      (*player)->getDiscardedCards()->push_back(card);
    });

    std::cout << (*player)->name << " has " << (*player)->getHand()->size()
              << " cards in their hand" << std::endl;
  }
}

bool OldMaid::turnOver() {
  // Implementation of turnOver// or some other logic
  std::cout << "OldMaid::turnOver has not been implemented";
  return false;
}

bool OldMaid::isOver() {
  // Implementation of isOver

  // std::cout << "OldMaid::isOver has not been implemented";
  return (players.empty());  // or some other logic
}
