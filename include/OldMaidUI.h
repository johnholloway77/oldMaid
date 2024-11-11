#ifndef OLDMAIDUI_H
#define OLDMAIDUI_H

#include <list>
#include <vector>

#include "Card.h"
#include "GameUI.h"

class OldMaidUI : public GameUI {
 public:
  OldMaidUI() {}
  ~OldMaidUI() {}

  unsigned int requestCard(Player* p, std::list<Card*>* hand);
  void playFailed();
  void playSucceeded();
  void outOfGame(Player* player);
  void showGameOutcome(std::vector<Player*> players);
};

#endif  // OLDMAIDUI_H
