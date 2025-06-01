#include <gtest/gtest.h>
#include "Game.hpp"
#include <fstream>
#include <string>
#include <vector>

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
        // gameChances[i].getText() == generatedChances[i].getText();
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
        // gameCommunityChests[i].getText() == generatedCommunityChests[i].getText();
        gameCommunityChests[i].isGetOutOfJailFree() == generatedCommunityChests[i].isGetOutOfJailFree();
        gameCommunityChests[i].isGoFieldCollectable() == generatedCommunityChests[i].isGoFieldCollectable();
    }
}

TEST(GameTests, setFields) {
    Game game;
    ASSERT_EQ(game.getFields().size(), 40);
    std::ifstream file(fieldsPath);
    if (!file.good()) {
        throw (std::invalid_argument("File error! Cannot open fields.txt file! "));
    }

    std::vector<fptr> fields;
    std::string fieldType;
    while (!file.eof()) {
        file >> fieldType;
        if (fieldType == "ChanceField") {
            ChanceField chanceField;
            file >> chanceField;
            fields.push_back(std::make_unique<ChanceField>(chanceField));
        }
        else if (fieldType == "CommunityChestField") {
            CommunityChestField communityChestField;
            file >> communityChestField;
            fields.push_back(std::make_unique<CommunityChestField>(communityChestField));
        }
        else if (fieldType == "GoToJail") {
            GoToJail goToJail;
            file >> goToJail;
            fields.push_back(std::make_unique<GoToJail>(goToJail));
        }
        else if (fieldType == "IncomeTax") {
            IncomeTax incomeTax;
            file >> incomeTax;
            fields.push_back(std::make_unique<IncomeTax>(incomeTax));
        }
        else if (fieldType == "Jail") {
            Jail jail;
            file >> jail;
            fields.push_back(std::make_unique<Jail>(jail));
        }
        else if (fieldType == "LuxuryTax") {
            LuxuryTax luxuryTax;
            file >> luxuryTax;
            fields.push_back(std::make_unique<LuxuryTax>(luxuryTax));
        }
        else if (fieldType == "Parking") {
            Parking parking;
            file >> parking;
            fields.push_back(std::make_unique<Parking>(parking));
        }
        else if (fieldType == "StartField") {
            StartField startField;
            file >> startField;
            fields.push_back(std::make_unique<StartField>(startField));
        }
        else if (fieldType == "Station") {
            Station station;
            file >> station;
            fields.push_back(std::make_unique<Station>(station));
        }
        else if (fieldType == "Street") {
            Street street;
            file >> street;
            fields.push_back(std::make_unique<Street>(street));
        }
        else if (fieldType == "Utility") {
            Utility utility;
            file >> utility;
            fields.push_back(std::make_unique<Utility>(utility));
        }
        else {
            throw (std::invalid_argument("File error! Corrupted fields.txt file! "));
        }
    }
    ASSERT_EQ(fields.size(), game.getFields().size());
    for (int i = 0; i < fields.size(); i++) {
        ASSERT_EQ(game.getFields()[i]->getInfo(), fields[i]->getInfo());
        ASSERT_EQ(game.getFields()[i]->getPosition(), fields[i]->getPosition());
    }
}