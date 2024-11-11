//
// "Copyright [2024] J. Holloway"
//

#include <gtest/gtest.h>

#include "../include/Card.h"

TEST(CardTest, ConstructorTest) {
  std::unique_ptr<Card> c(new Card(Card::SPADE, Card::ACE));

  EXPECT_TRUE(c);
}

TEST(CardTest, GetRankTest) {
  std::unique_ptr<Card> c(new Card(Card::SPADE, Card::ACE));

  EXPECT_EQ(Card::getRank(c->rank), "ACE");
}

TEST(CardTest, GetSuitTest) {
  std::unique_ptr<Card> c(new Card(Card::SPADE, Card::ACE));

  EXPECT_EQ(Card::getSuit(c->suit), "SPADE");
}
