#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>

#include "Card.h"
#include "Deck.h"
#include "GameUI.h"
#include "Player.h"

class Game {
 public:
  /**
   * Deal cards to players.
   * @param p A collection of Player.
   */
  virtual void dealCards(std::vector<Player*> p) = 0;

  /**
   * Perform actions before a player's turn.
   * @param playerNum The index of the player whose turn it is.
   * @param numPlayers The number of players in the game.
   */
  virtual void beforeTurn(unsigned int playerNum, unsigned int numPlayers) = 0;

  /**
   * Perform actions after a player's turn.
   * @param playerNum The index of the player whose turn it is.
   * @param numPlayers The number of players in the game.
   */
  virtual void duringTurn(unsigned int playerNum) = 0;

  /**
   * Checks if the game is over.
   * @return TRUE if the game is over, FALSE otherwise.
   */
  virtual bool isOver() = 0;

  /**
   * Create a game with a specific deck and UI.
   * @param ui The UI to use for the game.
   * @param d The deck to use for the game.
   */
  Game(GameUI* ui, Deck* d) : deck(d), ui(ui) {}

  virtual ~Game();

  /**
   * Add a Player to the game.
   * @param player The Player to add to the game.
   */
  void addPlayer(Player* player);

  /**
   * Get the collection of players.
   * @return The collection of current players in the game.
   */
  const std::vector<Player*>& getPlayers();

  /**
   * Get the collection of players who are out of the game.
   * @return The collection of players no longer in the game.
   */
  const std::vector<Player*>& getPlayersGoneOut();

  /**
   * Start the game.
   */
  virtual void start() = 0;

  /**
   * Checks if a player has no more cards to play and
   * if so, removes the player from the game.
   */
  void checkIfPlayerOut();

  /**
   * Checks if a player has a set of matching cards.
   * Cards are considered matching if the rank is the same.
   * @param hand The player's hand of cards.
   * @param size The number of cards to be considered a set.
   */
  bool hasSet(std::list<Card*>* hand, unsigned int size);

 protected:
  /**
   * The collection of players in the game.
   */
  std::vector<Player*> players;

  /**
   * The collection of players who are out of the game.
   */
  std::vector<Player*> playersGoneOut;

  /**
   * The deck of cards for the game.
   */
  Deck* deck;

  /**
   * The UI for the game.
   */
  GameUI* ui;

  /**
   * The index of the player asking for a card.
   */
  unsigned int playerAsking = 0;
};

#endif  // GAME_H_INCLUDED
