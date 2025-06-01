#include <gtest/gtest.h>
#include "Game.hpp"

using namespace Monopoly;

TEST(GameTests, Constructor) {
    Game game;
    ASSERT_EQ(game.getTurnCounter(), 0);
    ASSERT_EQ(game.getDice(), std::pair(0, 0));
    ASSERT_EQ(game.getDiceDoubleCounter(), 0);
    ASSERT_TRUE(game.isFilled());
    ASSERT_EQ(game.getPlayers().size(), 0);
    ASSERT_EQ(game.getChances().length(), 16);
    ASSERT_EQ(game.getCommunityChests().length(), 16);
    ASSERT_EQ(game.getFields().size(), 40);
}

TEST(GameTests, setEventCards) {
    Game game;
    ASSERT_EQ(game.getChances().length(), 16);
    ASSERT_EQ(game.getCommunityChests().length(), 16);

}