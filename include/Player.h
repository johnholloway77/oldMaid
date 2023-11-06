#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include "Card.h"

class Player {
 public:
    /**
    * Create a player for the game.
    * @param n Name of the player.
    */
    Player(const std::string& n) : name(n) {}
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
    * The player's name.
    */
    const std::string name;

 private:
    std::list<Card*> hand;
    unsigned int score = 0;
};

#endif // PLAYER_H
