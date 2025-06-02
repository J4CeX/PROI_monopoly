#include <gtest/gtest.h>
#include "Game.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace Monopoly;

class TestGame : public Game {
    protected:
        int randomNumber() override {
            if (rollIndex < nextRolls.size()) {
                return nextRolls[rollIndex++];
            }
            return 1;
        }

    private:
        std::vector<int> nextRolls;
        size_t rollIndex = 0;

    public:
        TestGame() : Game() {}
        bool shuffleEventCards = false;
        void setNextRoll(int first, int second) {
            nextRolls = {first, second};
            rollIndex = 0;
        }
};


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

TEST(GameTests, AddPlayer) {
    Game game;
    Player firstPlayer(1, "test1", Token::cat);
    Player secondPlayer(2, "test2", Token::penguin);
    game.addPlayer(firstPlayer);
    game.addPlayer(secondPlayer);
    std::vector<Player> gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPlayerId(), 1);
    ASSERT_EQ(gamePlayers[0].getName(), "test1");
    ASSERT_EQ(gamePlayers[0].getToken(), Token::cat);
    ASSERT_EQ(gamePlayers[0].getBalance(), 500);
    ASSERT_EQ(gamePlayers[1].getPlayerId(), 2);
    ASSERT_EQ(gamePlayers[1].getName(), "test2");
    ASSERT_EQ(gamePlayers[1].getToken(), Token::penguin);
    ASSERT_EQ(gamePlayers[1].getBalance(), 500);
}

TEST(GameTests, rollDiceAndMovePlayer) {
    TestGame game;
    Player firstPlayer(1, "test1", Token::cat);
    Player secondPlayer(2, "test2", Token::penguin);
    game.addPlayer(firstPlayer);
    game.addPlayer(secondPlayer);
    std::vector<Player> gamePlayers;

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(2, 4);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 6);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(3, 5);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 8);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 11);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(4, 3);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 15);
}

TEST(GameTests, diceDouble) {
    TestGame game;
    Player firstPlayer(1, "test1", Token::cat);
    Player secondPlayer(2, "test2", Token::penguin);
    game.addPlayer(firstPlayer);
    game.addPlayer(secondPlayer);
    std::vector<Player> gamePlayers;

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 3);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 6);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(1, 1);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 8);
    game.findNextPlayer();

    // JAIL
    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(5, 5);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 10);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(2, 3);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 5);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 10);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(3, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 10);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 3);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 16);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 21);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
}

TEST(GameTests, GoOnOwnableFieldAndPurchaseItMortgageAndSell) {
    TestGame game;
    Player firstPlayer(1, "test1", Token::cat);
    Player secondPlayer(2, "test2", Token::penguin);
    game.addPlayer(firstPlayer);
    game.addPlayer(secondPlayer);
    std::vector<Player> gamePlayers;

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(3, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 5);

    // STATION
    OwnableField* ownableField = dynamic_cast<Station*>(game.getFields()[5].get());
    ASSERT_FALSE(ownableField->isOwned());
    ASSERT_EQ(gamePlayers[0].getBalance(), 500);
    ASSERT_EQ(game.buyOwnableField(), 1);
    gamePlayers = game.getPlayers();
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_EQ(ownableField->getOwner(), 0);
    ASSERT_EQ(gamePlayers[0].getBalance(), 300);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(3, 3);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 6);

    // STREET
    ownableField = dynamic_cast<Street*>(game.getFields()[6].get());
    ASSERT_FALSE(ownableField->isOwned());
    ASSERT_EQ(game.buyOwnableField(), 1);
    gamePlayers = game.getPlayers();
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_EQ(ownableField->getOwner(), 1);
    ASSERT_EQ(gamePlayers[1].getBalance(), 400);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(5, 1);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 12);

    // UTILITY
    ownableField = dynamic_cast<Utility*>(game.getFields()[12].get());
    ASSERT_FALSE(ownableField->isOwned());
    ASSERT_EQ(game.buyOwnableField(), 1);
    gamePlayers = game.getPlayers();
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_EQ(ownableField->getOwner(), 1);
    ASSERT_EQ(gamePlayers[1].getBalance(), 250);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    size_t position = 5;
    size_t playerIndex = 0;
    ASSERT_EQ(game.playerMortgageField(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ownableField = dynamic_cast<Station*>(game.getFields()[5].get());
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_TRUE(ownableField->isMortgaged());
    ASSERT_EQ(gamePlayers[0].getBalance(), 400);
    game.sellOwnableField(playerIndex, position);
    gamePlayers = game.getPlayers();
    ownableField = dynamic_cast<Station*>(game.getFields()[5].get());
    ASSERT_FALSE(ownableField->isOwned());
    ASSERT_FALSE(ownableField->isMortgaged());
    ASSERT_EQ(gamePlayers[0].getBalance(), 500);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    gamePlayers = game.getPlayers();

    position = 6;
    playerIndex = 1;
    ASSERT_EQ(game.playerMortgageField(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ownableField = dynamic_cast<Street*>(game.getFields()[6].get());
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_TRUE(ownableField->isMortgaged());
    ASSERT_EQ(gamePlayers[1].getBalance(), 300);
    game.playerMortgageField(playerIndex, position, true);
    gamePlayers = game.getPlayers();
    ownableField = dynamic_cast<Street*>(game.getFields()[6].get());
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_FALSE(ownableField->isMortgaged());
    ASSERT_EQ(gamePlayers[1].getBalance(), 250);

    position = 12;
    game.sellOwnableField(playerIndex, position);
    gamePlayers = game.getPlayers();
    ownableField = dynamic_cast<Utility*>(game.getFields()[12].get());
    ASSERT_FALSE(ownableField->isOwned());
    ASSERT_FALSE(ownableField->isMortgaged());
    ASSERT_EQ(gamePlayers[1].getBalance(), 400);

    position = 16;
    game.setNextRoll(3, 1);
    game.rollDice();
    ASSERT_EQ(game.buyOwnableField(), 1);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 16);
    ownableField = dynamic_cast<Street*>(game.getFields()[16].get());
    ASSERT_TRUE(ownableField->isOwned());
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    ASSERT_EQ(game.sellOwnableField(playerIndex, position), -1);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position, true), 1);
    ASSERT_EQ(game.sellOwnableField(playerIndex, position), 1);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getBalance(), 400);
}

TEST(GameTests, purchaseHouse) {
    TestGame game;
    Player firstPlayer(1, "test1", Token::cat);
    Player secondPlayer(2, "test2", Token::penguin);
    game.addPlayer(firstPlayer);
    game.addPlayer(secondPlayer);
    std::vector<Player> gamePlayers;

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    game.setNextRoll(4, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getPosition(), 6);

    Street* street = dynamic_cast<Street*>(game.getFields()[6].get());
    ASSERT_FALSE(street->isOwned());
    ASSERT_EQ(game.buyOwnableField(), 1);
    gamePlayers = game.getPlayers();
    ASSERT_TRUE(street->isOwned());
    ASSERT_EQ(street->getOwner(), 0);
    ASSERT_EQ(gamePlayers[0].getBalance(), 400);

    ASSERT_EQ(street->getRent(), 6);
    ASSERT_EQ(street->getHouseCount(), 0);
    size_t position = 6;
    size_t playerIndex = 0;
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 350);
    ASSERT_EQ(street->getRent(), 30);
    ASSERT_EQ(street->getHouseCount(), 1);

    game.findNextPlayer();
    ASSERT_EQ(game.getCurrentPlayerId(), 2);
    game.setNextRoll(4, 2);
    game.rollDice();
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[1].getPosition(), 6);
    ASSERT_EQ(gamePlayers[1].getBalance(), 470);
    ASSERT_EQ(gamePlayers[0].getBalance(), 380);
    ASSERT_EQ(game.buyOwnableField(), -1);
    game.findNextPlayer();

    ASSERT_EQ(game.getCurrentPlayerId(), 1);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 330);
    ASSERT_EQ(street->getRent(), 90);
    ASSERT_EQ(street->getHouseCount(), 2);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 280);
    ASSERT_EQ(street->getRent(), 270);
    ASSERT_EQ(street->getHouseCount(), 3);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 230);
    ASSERT_EQ(street->getRent(), 400);
    ASSERT_EQ(street->getHouseCount(), 4);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), 2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 180);
    ASSERT_EQ(street->getRent(), 550);
    ASSERT_EQ(street->getHouseCount(), 5);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position), -2);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 180);
    ASSERT_EQ(street->getRent(), 550);
    ASSERT_EQ(street->getHouseCount(), 5);
    ASSERT_EQ(game.playerBuyHouse(playerIndex, position, true), 1);
    gamePlayers = game.getPlayers();
    ASSERT_EQ(gamePlayers[0].getBalance(), 230);
    ASSERT_EQ(street->getRent(), 400);
    ASSERT_EQ(street->getHouseCount(), 4);
}