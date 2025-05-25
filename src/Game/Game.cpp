#include "Game.hpp"

namespace Monopoly {
    Game::Game():
    turnCounter(0), currentPlayer(0), dice(0, 0),
    diceDubletCounter(0) {
        try {
            setFields();
        }
        catch (exception& exc) {
            cerr << "File Error! Corrupted fields.txt file! " << exc.what() << endl;
        }

        try {
            setEventCards();
        }
        catch (exception& exc) {
            cerr << "File error! Wrong EventCard type! " << exc.what() << endl;
        }
    }

    Game::Game(const Game& secGame) {
        turnCounter = secGame.turnCounter;
        currentPlayer = secGame.currentPlayer;
        dice = secGame.dice;
        diceDubletCounter = secGame.diceDubletCounter;
        players = secGame.players;
        chances = secGame.chances;
        communityChests = secGame.communityChests;
        for (const auto& field: secGame.fields) {
            fields.push_back(field->clone());
        }
    }

    Game::Game(Game&& secGame) {
        turnCounter = secGame.turnCounter;
        currentPlayer = secGame.currentPlayer;
        dice = secGame.dice;
        diceDubletCounter = secGame.diceDubletCounter;
        players = secGame.players;
        chances = secGame.chances;
        communityChests = secGame.communityChests;
        fields = move(secGame.fields);
    }

    Game& Game::operator=(const Game& secGame) {
        if (this != &secGame) {
            turnCounter = secGame.turnCounter;
            currentPlayer = secGame.currentPlayer;
            dice = secGame.dice;
            diceDubletCounter = secGame.diceDubletCounter;
            players = secGame.players;
            chances = secGame.chances;
            communityChests = secGame.communityChests;
            for (const auto& field: secGame.fields) {
                fields.push_back(field->clone());
            }
        }
        return *this;
    }

    Game& Game::operator=(Game&& secGame) {
        if (this != &secGame) {
            turnCounter = secGame.turnCounter;
            currentPlayer = secGame.currentPlayer;
            dice = secGame.dice;
            diceDubletCounter = secGame.diceDubletCounter;
            players = secGame.players;
            chances = secGame.chances;
            communityChests = secGame.communityChests;
            fields = move(secGame.fields);
        }
        return *this;
    }

    bool Game::canFieldBeBought() {
        size_t currentPosition = players[currentPlayer].getPosition();
        for (const auto& field: fields) {
            if (currentPosition == field->getPosition()) {
                TYPE currentType = field->getInfo();
                if (currentType == TYPE::STREET || currentType == TYPE::STATION || currentType == TYPE::UTILITY) {
                    return true;
                }
            }
        }
        return false;
    }

    void Game::rollDice() {
        // srand(time(NULL)); TO MUSI BYĆ W GUI !!!
        int first = rand() % 6 + 1;
        int second = rand() % 6 + 1;

        if (first == second) {
            if ((rand() % 6) != 0) {
                do {
                    second = rand() % 6 + 1;
                } while (second == first);
            }
        }
        dice.first = first;
        dice.second = second;
    }



    bool Game::isFinished() {
        int inGame = 0;
        for (const auto& player: players) {
            if (!player.getIsBankrupt()) {
                inGame++;
            }
        }
        return inGame > 1 ? false : true;
    }

    size_t Game::findNextPlayer() {
        currentPlayer = ++currentPlayer % players.size();
        return currentPlayer;
    }

    bool Game::addPlayer(Player& newPlayer) {
        if (players.size() < 4) {
            players.push_back(newPlayer);
            return true;
        }
        else {
            return false;
        }
    }

    bool Game::playerMortgageField(size_t& player, size_t& fieldPosition, bool unMortgage) {
        for (auto& field: fields) {
            if (field->getPosition() == fieldPosition) {
                if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get())) {
                    if (Street* street = dynamic_cast<Street*>(field.get())) {
                        if (street->getHouseCount() != 0) {
                            return false;
                        }
                    }
                    if (unMortgage) {
                        players[currentPlayer].setBalance(players[currentPlayer].getBalance() + ownableField->mortgage());
                    }
                    else {
                        players[currentPlayer].setBalance(players[currentPlayer].getBalance() - ownableField->unmortgage());
                    }
                    return true;
                }
            }
        }
        return false;
    }

    bool Game::playerBuysHouse(size_t& player, size_t& fieldPosition, bool sellsHouse) {

        return true;
    }

    void Game::buyOwnableField() {

    }

    bool Game::sellOwnableField(size_t& player, size_t& fieldPosition) {

        return true;
    }

    size_t Game::movePlayer() {
        rollDice();
        size_t currentPosition = players[currentPlayer].getPosition();
        size_t newPosition = (currentPosition + dice.first + dice.second) % 40;

        if (newPosition < currentPosition) {
            players[currentPlayer].setBalance(players[currentPlayer].getBalance() + 200);
        }

        players[currentPlayer].setPosition(newPosition);

        return newPosition;
    }

    void Game::useGetOutOfJailCard() {

    }

    void Game::setFields() {
        ifstream file("fields.txt");
        string fieldType;
        while (!file.eof()) {
            file >> fieldType;
            if (fieldType == "ChanceField") {
                ChanceField chanceField;
                file >> chanceField;
                pushField<ChanceField>(chanceField);
            }
            else if (fieldType == "CommunityChestField") {
                CommunityChestField communityChestField;
                file >> communityChestField;
                pushField<CommunityChestField>(communityChestField);
            }
            else if (fieldType == "GoToJail") {
                GoToJail goToJail;
                file >> goToJail;
                pushField<GoToJail>(goToJail);
            }
            else if (fieldType == "IncomeTax") {
                IncomeTax incomeTax;
                file >> incomeTax;
                pushField<IncomeTax>(incomeTax);
            }
            else if (fieldType == "Jail") {
                Jail jail;
                file >> jail;
                pushField<Jail>(jail);
            }
            else if (fieldType == "LuxuryTax") {
                LuxuryTax luxuryTax;
                file >> luxuryTax;
                pushField<LuxuryTax>(luxuryTax);
            }
            else if (fieldType == "Parking") {
                Parking parking;
                file >> parking;
                pushField<Parking>(parking);
            }
            else if (fieldType == "StartField") {
                StartField startField;
                file >> startField;
                pushField<StartField>(startField);
            }
            else if (fieldType == "Station") {
                Station station;
                file >> station;
                pushField<Station>(station);
            }
            else if (fieldType == "Street") {
                Street street;
                file >> street;
                pushField<Street>(street);
            }
            else if (fieldType == "Utility") {
                Utility utility;
                file >> utility;
                pushField<Utility>(utility);
            }
            else {
                throw;
            }
        }
    }

    void Game::setEventCards() {
        EventCardContainer generatedChances;
        EventCardContainer generatedCommunityChests;

        ifstream file("eventCards.txt");
        while(!file.eof()) {
            EventCard eventCard;
            file >> eventCard;
            if (eventCard.getCardType() == CardType::chance) {
                generatedChances.addCard(eventCard);
            }
            else if (eventCard.getCardType() == CardType::communityChest) {
                generatedCommunityChests.addCard(eventCard);
            }
            else {
                throw;
            }
        }

        chances = generatedChances;
        communityChests = generatedCommunityChests;
    }
}