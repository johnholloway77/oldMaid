//
// Created by jholloway on 11/10/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//

#include <gtest/gtest.h>

#include "../include/Deck.h"

TEST(DeckTest, ConstructorTest){

  Deck* d = new Deck();

  EXPECT_TRUE(d);

  delete d;

}

TEST(DeckTest, CreateDeckTest){

    Deck* d = new Deck();

    EXPECT_EQ(d->size(), 0);

    d->create();

    EXPECT_EQ(d->size(), 52);

    delete d;
}
