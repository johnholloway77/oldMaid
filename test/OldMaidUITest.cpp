//
// Created by jholloway on 11/14/24.
// Copyright (c) [2024] John Holloway. All Rights Reserved.
//
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../include/Deck.h"
#include "../include/OldMaid.h"
#include "../include/OldMaidUI.h"

TEST(OldMaidUITest, DefaultConstructorTest) {
  std::unique_ptr<OldMaidUI> omUI(new OldMaidUI());

  EXPECT_TRUE(omUI);
}

TEST(OldMaidUITest, RequestCardTest) {
  std::string expectedOutput =
      "Player1 picked the card .* of .* from their neighbour\n";

  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");

  Deck* d(new Deck());

  d->create();
  d->shuffle();

  OldMaidUI* old_UI = new OldMaidUI();

  std::unique_ptr<OldMaid> om(new OldMaid(old_UI, d));

  om->addPlayer(p1);
  om->addPlayer(p2);

  om->dealCards(om->getPlayers());

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream capturedOutput;
  std::cout.rdbuf(capturedOutput.rdbuf());

  old_UI->requestCard(p1, p2->getHand());

  std::cout.rdbuf(original_stdout);

  EXPECT_THAT(capturedOutput.str(), ::testing::MatchesRegex(expectedOutput));

  delete p1;
  delete p2;
  delete d;
  delete old_UI;
}

TEST(OldMaidUITest, RequestCardTestFromEmptyHand) {
  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");

  std::string expectedOutput =
      p1->name + " tried to take a card from an player with empty hand\n";

  Deck* d(new Deck());

  OldMaidUI* old_UI = new OldMaidUI();

  std::unique_ptr<OldMaid> om(new OldMaid(old_UI, d));

  om->addPlayer(p1);
  om->addPlayer(p2);

  om->dealCards(om->getPlayers());

  std::streambuf* original_stderr = std::cerr.rdbuf();

  std::ostringstream capturedErrorMessage;
  std::cerr.rdbuf(capturedErrorMessage.rdbuf());

  old_UI->requestCard(p1, p2->getHand());

  std::cout.rdbuf(original_stderr);

  EXPECT_THAT(capturedErrorMessage.str(),
              ::testing::MatchesRegex(expectedOutput));

  delete p1;
  delete p2;
  delete d;
  delete old_UI;
}

TEST(OldMaidUITest, PlayFailedTest) {
  std::string expectedOutput =
      "Player1 failed to gain a new pair and discard cards\n"
      "Player1 hand size has increased to 3 cards\n";

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream discardedOutput;
  std::ostringstream capturedOutput;

  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");

  Deck* d(new Deck());
  d->create();
  d->shuffle();

  OldMaidUI* old_maid_ui(new OldMaidUI());
  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  Card* card1(new Card(Card::SPADE, Card::ACE));
  Card* card2(new Card(Card::SPADE, Card::KING));
  Card* card3(new Card(Card::SPADE, Card::QUEEN));
  Card* card4(new Card(Card::SPADE, Card::JACK));

  p1->addCard(card1);
  p1->addCard(card2);

  p2->addCard(card3);
  p2->addCard(card4);

  om->addPlayer(p1);
  om->addPlayer(p2);

  int player1CardsDealt = p1->getHand()->size();

  std::cout.rdbuf(discardedOutput.rdbuf());
  om->beforeTurn(0, om->getPlayers().size());

  std::cout.rdbuf(capturedOutput.rdbuf());
  om->duringTurn(0);
  std::cout.rdbuf(original_stdout);

  EXPECT_GT(p1->getHand()->size(), player1CardsDealt);
  EXPECT_EQ(expectedOutput, capturedOutput.str());

  delete p1;
  delete p2;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidUITest, PlaySucceededTest) {
  std::string expectedOutput =
      "Player1 discarded the following pair:\n\tThe ACE of .* and the ACE of "
      ".*\nPlayer1 hand size has decreased to 1 cards\n";

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream discardedOutput;
  std::ostringstream capturedOutput;

  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");

  Deck* d(new Deck());
  d->create();
  d->shuffle();

  OldMaidUI* old_maid_ui(new OldMaidUI());
  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  Card* card1(new Card(Card::SPADE, Card::ACE));
  Card* card2(new Card(Card::CLUB, Card::ACE));
  Card* card3(new Card(Card::DIAMOND, Card::ACE));
  Card* card4(new Card(Card::HEART, Card::ACE));

  p1->addCard(card1);
  p1->addCard(card2);

  p2->addCard(card3);
  p2->addCard(card4);

  om->addPlayer(p1);
  om->addPlayer(p2);

  std::cout.rdbuf(discardedOutput.rdbuf());
  om->beforeTurn(0, om->getPlayers().size());

  std::cout.rdbuf(capturedOutput.rdbuf());
  om->duringTurn(0);
  std::cout.rdbuf(original_stdout);

  // EXPECT_EQ(expectedOutput, capturedOutput.str());
  EXPECT_THAT(capturedOutput.str(), ::testing::MatchesRegex(expectedOutput));

  delete p1;
  delete p2;
  delete d;
  delete old_maid_ui;
}

TEST(OldMaidUITest, OutOfGameTest) {
  Player* p1 = new Player("OutOfGameTest_Player");

  OldMaidUI* omUI(new OldMaidUI());

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream capturedOutput;
  std::cout.rdbuf(capturedOutput.rdbuf());

  omUI->outOfGame(p1);

  std::cout.rdbuf(original_stdout);

  EXPECT_EQ(capturedOutput.str(), p1->name + " is out of the game\n");

  delete p1;
  delete omUI;
}

TEST(OldMaidUITest, OutOfGameIntegrationTest) {
  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream capturedOutput;
  std::cout.rdbuf(capturedOutput.rdbuf());

  Player* p1 = new Player("Player1");
  OldMaidUI* old_maid_ui = new OldMaidUI();
  Deck* d(new Deck());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_maid_ui, d));

  om->addPlayer(p1);

  om->start();

  EXPECT_EQ(om->getPlayers().size(), 1);

  om->checkIfPlayerOut();

  EXPECT_EQ(om->getPlayers().size(), 0);

#ifdef DEBUGPRINT
  EXPECT_EQ(capturedOutput.str(),
            "Game::start()  has not been implemented!\n"
            "\n"
            "Game::checkIfPlayerOut\n"
            "Player1 has 0 cards\n"
            "Player1 is out of the game\n");

#else
  EXPECT_EQ(capturedOutput.str(), p1->name + " is out of the game\n");
#endif

  std::cout.rdbuf(original_stdout);
  delete p1;
  delete old_maid_ui;
  delete d;
}

TEST(OldMaidUITest, ShowGameOutcomeTest) {
  std::string expectedOutput1 =
      "The following players successfully dealt their hands and succeeded: \n";
  std::string expectedOutput2 = " was the old maid!!\n";

  std::streambuf* original_stdout = std::cout.rdbuf();

  std::ostringstream capturedOutput;
  std::ostringstream capturedOutput2;
  std::cout.rdbuf(capturedOutput.rdbuf());

  Player* p1 = new Player("Player1");
  Player* p2 = new Player("Player2");
  Player* p3 = new Player("Player3");

  Deck* d(new Deck());
  OldMaidUI* old_ui(new OldMaidUI());

  d->create();
  d->shuffle();

  std::unique_ptr<OldMaid> om(new OldMaid(old_ui, d));

  om->addPlayer(p1);
  om->addPlayer(p2);
  om->addPlayer(p3);

  om->dealCards(om->getPlayers());

  for (auto player : om->getPlayers()) {
    EXPECT_GE(player->getHand()->size(), 16);
    EXPECT_LE(player->getHand()->size(), 18);
  }

#ifdef DEBUGPRINT

  for (auto player : om->getPlayers()) {
    std::cout << player->name << " has " << player->getHand()->size()
              << " cards" << std::endl;
  }

#endif

  while (!om->getPlayers().empty()) {
    for (int i = 0; i < om->getPlayers().size() - 1; i++) {
      if (om->isOver()) {
        break;
      }

      om->beforeTurn(i, om->getPlayers().size());

#ifdef DEBUGPRINT

      for (auto player : om->getPlayers()) {
        std::cout << player->name << " has " << player->getHand()->size()
                  << " cards" << std::endl;
      }
#endif
    }
  }

  std::cout.rdbuf(original_stdout);
  std::cout.rdbuf(capturedOutput2.rdbuf());

  old_ui->showGameOutcome(om->getPlayersGoneOut());

  std::cout.rdbuf(original_stdout);

  EXPECT_TRUE(capturedOutput2.str().find(expectedOutput1) != std::string::npos);

  EXPECT_TRUE(capturedOutput2.str().find(expectedOutput2) != std::string::npos);

  delete p1;
  delete p2;
  delete p3;
  delete d;
  delete old_ui;
}
