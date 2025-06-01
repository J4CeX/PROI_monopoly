#include <gtest/gtest.h>
#include "Game.hpp"
#include <fstream>
#include <string>

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
    EventCardContainer generatedChances;
    EventCardContainer generatedCommunityChests;
    std::ifstream file(eventCardsPath);
    if (!file.good()) {
        throw (std::invalid_argument("File error (tests): cannot open eventCards.txt file"));
    }
    EventCard eventCard;
    while(!file.eof()) {
        file >> eventCard;
        if (!file) {
            throw std::invalid_argument("File read error (tests): deserialization failed");
        }

        if (eventCard.getCardType() == CardType::chance) {
            generatedChances.addCard(eventCard);
        } else if (eventCard.getCardType() == CardType::communityChest) {
            generatedCommunityChests.addCard(eventCard);
        } else {
            throw (std::invalid_argument("File error (tests): wrong EventCard type"));
        }
    }
    ASSERT_EQ(game.getChances().length(), generatedChances.length());
    ASSERT_EQ(game.getCommunityChests().length(), generatedCommunityChests.length());
    EventCardContainer gameChances = game.getChances();
    EventCardContainer gameCommunityChests = game.getCommunityChests();
    for (int i = 0; i < generatedChances.length(); i++) {
        gameChances[i].getBankBalance() == generatedChances[i].getBankBalance();
        gameChances[i].getCardId() == generatedChances[i].getCardId();
        gameChances[i].getCardType() == generatedChances[i].getCardType();
        gameChances[i].getEachPlayerBalance() == generatedChances[i].getEachPlayerBalance();
        gameChances[i].getLocation() == generatedChances[i].getLocation();
        gameChances[i].getMovementType() == generatedChances[i].getMovementType();
        gameChances[i].getPerHotelBalance() == generatedChances[i].getPerHotelBalance();
        gameChances[i].getPerHouseBalance() == generatedChances[i].getPerHouseBalance();
        gameChances[i].getText() == generatedChances[i].getText();
        gameChances[i].isGetOutOfJailFree() == generatedChances[i].isGetOutOfJailFree();
        gameChances[i].isGoFieldCollectable() == generatedChances[i].isGoFieldCollectable();
    }
    for (int i = 0; i < generatedCommunityChests.length(); i++) {
        gameCommunityChests[i].getBankBalance() == generatedCommunityChests[i].getBankBalance();
        gameCommunityChests[i].getCardId() == generatedCommunityChests[i].getCardId();
        gameCommunityChests[i].getCardType() == generatedCommunityChests[i].getCardType();
        gameCommunityChests[i].getEachPlayerBalance() == generatedCommunityChests[i].getEachPlayerBalance();
        gameCommunityChests[i].getLocation() == generatedCommunityChests[i].getLocation();
        gameCommunityChests[i].getMovementType() == generatedCommunityChests[i].getMovementType();
        gameCommunityChests[i].getPerHotelBalance() == generatedCommunityChests[i].getPerHotelBalance();
        gameCommunityChests[i].getPerHouseBalance() == generatedCommunityChests[i].getPerHouseBalance();
        gameCommunityChests[i].getText() == generatedCommunityChests[i].getText();
        gameCommunityChests[i].isGetOutOfJailFree() == generatedCommunityChests[i].isGetOutOfJailFree();
        gameCommunityChests[i].isGoFieldCollectable() == generatedCommunityChests[i].isGoFieldCollectable();
    }
}