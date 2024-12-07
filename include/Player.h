#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <string>

#include "Card.h"

class Player {
 public:
  /**
   * Create a player for the game.
   * @param n Name of the player.
   */
  explicit Player(const std::string& n) : name(n) {}
  virtual ~Player();

  /**
   * Add a card to the player's hand.
   * @param c The card to add.
   */
  void addCard(Card* c);

  /**
   * Get a card from the player's hand.
   * @param index The index of the card in the player's hand.
   */
  Card* getCard(unsigned int index);

  /**
   * @return The cards in the player's hand.
   */
  std::list<Card*>* getHand();

  /**
   * @return The cards in the player has discarded in previous plays
   */
  std::list<Card*>* getDiscardedCards();

  /**
   * Take a card from another player's hand.
   * @param player The player from whom this player is taken a random card.
   */
  void takeCard(Player* player);

  /**
   * The player's name.
   */
  const std::string name;

 private:
  std::list<Card*> hand;
  unsigned int score = 0;

  /*
   *  Vector of cards no longer in play;
   */
  std::list<Card*> discardedCards;
};

#endif  // PLAYER_H
