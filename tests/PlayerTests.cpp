#include <gtest/gtest.h>
#include "Player.hpp"
#include <sstream>

using namespace MonopolyPlayer;

TEST(PlayerTests, Constructor) {
    Player player(0, "player", Token::cat, 200, true, 20, 3, true);
    EXPECT_EQ(player.getPlayerId(), 0);
    EXPECT_EQ(player.getName(), "player");
    EXPECT_EQ(player.getToken(), Token::cat);
    EXPECT_EQ(player.getBalance(), 200);
    ASSERT_TRUE(player.getIsBankrupt());
    EXPECT_EQ(player.getPosition(), 20);
    EXPECT_EQ(player.getInJailRounds(), 3);
    ASSERT_TRUE(player.getGetOutOfJailCard());
}

TEST(PlayerTests, DefaultConstructor) {
    Player player(0, "player", Token::cat);
    EXPECT_EQ(player.getPlayerId(), 0);
    EXPECT_EQ(player.getName(), "player");
    EXPECT_EQ(player.getToken(), Token::cat);
    EXPECT_EQ(player.getBalance(), 500);
    ASSERT_FALSE(player.getIsBankrupt());
    EXPECT_EQ(player.getPosition(), 0);
    EXPECT_EQ(player.getInJailRounds(), 0);
    ASSERT_FALSE(player.getGetOutOfJailCard());
}

TEST(PlayerTests, Setters) {
    Player player(0, "player", Token::cat);
    player.setBalance(200);
    player.setPosition(10);
    player.setInJailRounds(3);
    player.setGetOutOfJailCard(true);
    EXPECT_EQ(player.getPlayerId(), 0);
    EXPECT_EQ(player.getName(), "player");
    EXPECT_EQ(player.getToken(), Token::cat);
    EXPECT_EQ(player.getBalance(), 200);
    ASSERT_FALSE(player.getIsBankrupt());
    EXPECT_EQ(player.getPosition(), 10);
    EXPECT_EQ(player.getInJailRounds(), 3);
    ASSERT_TRUE(player.getGetOutOfJailCard());
}

TEST(PlayerTests, checkIfBankrupt) {
    Player player(0, "player", Token::cat);
    ASSERT_FALSE(player.checkIfBankrupt());
    player.setBalance(0);
    ASSERT_FALSE(player.checkIfBankrupt());
    player.setBalance(-1);
    ASSERT_TRUE(player.checkIfBankrupt());
}

TEST(PlayerTests, InputConstructor) {
    Player player;
    std::istringstream iss("1 5 200 0 20 3 1 player");
    iss >> player;
    EXPECT_EQ(player.getPlayerId(), 1);
    EXPECT_EQ(player.getName(), "player");
    EXPECT_EQ(player.getToken(), Token::cat);
    EXPECT_EQ(player.getBalance(), 200);
    ASSERT_FALSE(player.getIsBankrupt());
    EXPECT_EQ(player.getPosition(), 20);
    EXPECT_EQ(player.getInJailRounds(), 3);
    ASSERT_TRUE(player.getGetOutOfJailCard());
}

TEST(PlayerTests, Output) {
    Player player(1, "player", Token::cat);
    std::ostringstream oss;
    oss << player;
    ASSERT_EQ(oss.str(), "1 5 500 0 0 0 0 player\n");
}