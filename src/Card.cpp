//
// "Copyright [2024] J. Holloway"
//

#include "../include/Card.h"

#include <string>
#include <vector>

std::string Card::getRank(const Card::Rank rank) {
  std::vector<std::string> ranks = {"ACE",  "TWO",   "THREE", "FOUR", "FIVE",
                                    "SIX",  "SEVEN", "EIGHT", "NINE", "TEN",
                                    "JACK", "QUEEN", "KING"};
  return ranks[rank];
}

std::string Card::getSuit(const Card::Suit suit) {
  std::vector<std::string> suits = {"CLUB", "DIAMOND", "SPADE", "HEART"};
  return suits[suit];
}
