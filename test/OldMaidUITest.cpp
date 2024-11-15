//
// Created by jholloway on 11/14/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//
#include <gtest/gtest.h>

#include "../include/OldMaidUI.h"

TEST(OldMaidUITest, DefaultConstructorTest) {
  std::unique_ptr<OldMaidUI> omUI(new OldMaidUI());

  EXPECT_TRUE(omUI);
}

TEST(OldMaidUITest, OutOfGameTest) {
  Player* p1 = new Player("OutOfGameTest_Player");

  std::unique_ptr<OldMaidUI> omUI(new OldMaidUI());

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream capturedOutput;
  std::cout.rdbuf(capturedOutput.rdbuf());

  omUI->outOfGame(p1);

  std::cout.rdbuf(original_stdout);

  EXPECT_EQ(capturedOutput.str(), p1->name + " is out of the game\n");

  delete p1;
}
