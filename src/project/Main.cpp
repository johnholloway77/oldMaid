//
// Created by jholloway on 11/10/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include <iostream>
#include <string>

#include "../../include/OldMaid.h"
#include "../../include/OldMaidUI.h"
#include "../../include/Player.h"

#ifdef __linux__
#include <algorithm>
#include <limits>
#endif

int main(int argc, char** argv) {
  std::cout << "Please enter the number of players (between 2 and 8): ";

  std::vector<Player*> players;
  int numberOfPlayers;

  while (true) {
    if (std::cin >> numberOfPlayers) {
      if (numberOfPlayers >= 2 && numberOfPlayers <= 8) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
      } else {
        std::cout << "Out of range. Please enter an integer between 2 and 8: ";
      }
    } else {
      std::cout << "Not a valid integer. Please enter an int between 2 and 8: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  for (int i = 0; i < numberOfPlayers; i++) {
    std::string playerName;
    std::cout << "Please enter the name of Player " << i + 1 << ": ";

    while (true) {
      std::getline(std::cin, playerName);

      if (!playerName.empty() &&
          !std::all_of(playerName.begin(), playerName.end(), isspace)) {
        break;
      } else {
        std::cout << "Invalid player name. Please enter a valid name: ";
      }
    }

    players.push_back(new Player(playerName));
  }

  auto old_maid_ui(new OldMaidUI);
  auto deck(new Deck);

  auto old_maid_game(new OldMaid(old_maid_ui, deck));

  std::for_each(players.begin(), players.end(),
                [&old_maid_game](Player* p) { old_maid_game->addPlayer(p); });

  std::cout << "Beginning Old Maid game!" << std::endl;

  old_maid_game->start();

  delete old_maid_ui;
  delete deck;
  delete old_maid_game;
  std::for_each(players.begin(), players.end(), [](Player* p) { delete p; });

  return 0;
}
