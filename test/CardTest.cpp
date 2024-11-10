//
// "Copyright [2024] J. Holloway"
//

#include <gtest/gtest.h>

#include "../include/Card.h"

TEST(CardTest, ConstructorTest){

  Card *c = new Card(Card::SPADE, Card::ACE);

  EXPECT_TRUE(c);

  delete c;
}

TEST(CardTest, getRankTest){

  Card *c = new Card(Card::SPADE, Card::ACE);

  EXPECT_EQ(Card::getRank(c->rank), "ACE");

  delete c;

}

TEST(CardTest, getSuitTest){

  Card *c = new Card(Card::SPADE, Card::ACE);

  EXPECT_EQ(Card::getSuit(c->suit), "SPADE");

  delete c;
}