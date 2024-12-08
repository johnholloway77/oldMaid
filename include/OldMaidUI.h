#ifndef OLDMAIDUI_H
#define OLDMAIDUI_H

#include <list>
#include <string>
#include <vector>

#include "Card.h"
#include "GameUI.h"

class OldMaidUI : public GameUI {
 public:
  OldMaidUI() {}
  ~OldMaidUI() override {}

  unsigned int requestCard(Player* p, std::list<Card*>* hand) override;
  void playFailed(Player* player) override;
  void playSucceeded(const std::string& playString, Player* player) override;
  void outOfGame(Player* player) override;
  void showGameOutcome(std::vector<Player*> players) override;
};

#endif  // OLDMAIDUI_H
