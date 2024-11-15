//
// Created by jholloway on 11/14/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include "../include/OldMaidUI.h"

unsigned int OldMaidUI::requestCard(Player* p, std::list<Card*>* hand) {
  return 0;
}

void OldMaidUI::playFailed() {};

void OldMaidUI::playSucceeded() {};

void OldMaidUI::outOfGame(Player* player) {
  std::cout << player->name + " is out of the game" << std::endl;
}

void OldMaidUI::showGameOutcome(std::vector<Player*> players) {

};
