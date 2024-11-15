#ifndef GOFISH_H
#define GOFISH_H

#include <vector>

#include "Game.h"

class OldMaid : public Game {
 public:
  /**
   * Create a game of Old Maid using a UI and a deck.
   * @param ui The UI for the game.
   * @param deck The deck for the game.
   */
  OldMaid(GameUI* ui, Deck* deck) : Game(ui, deck) {}

  virtual ~OldMaid() {}
  void dealCards(std::vector<Player*> p) override;
  void beforeTurn(unsigned int playerNum, unsigned int numPlayers) override;
  void afterTurn(Player* currentPlayer, std::vector<Player*>* players,
                 Card* played) override;
  bool turnOver() override;
  bool isOver() override;
};

#endif  // GOFISH_H
