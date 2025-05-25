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
            communityChests.shuffle();
            chances.shuffle();
            communityChestsCounter = communityChests.length();
            chancesCounter = chances.length();
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
        if (first == second) {
            diceDubletCounter++;
        }
        if (diceDubletCounter && players[currentPlayer].getInJailRounds()) {
            players[currentPlayer].setInJailRounds(0);
        }
        if (diceDubletCounter == 3) {
            players[currentPlayer].setPosition(10);
            players[currentPlayer].setInJailRounds(3);
            diceDubletCounter = 0;
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
        diceDubletCounter = 0;
        do {
            currentPlayer = ++currentPlayer % players.size();
        } while (players[currentPlayer].getIsBankrupt());
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

    int Game::playerMortgageField(size_t& player, size_t& fieldPosition, bool unMortgage) {
        for (auto& field: fields) {
            if (field->getPosition() == fieldPosition) {
                if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get())) {
                    if (Street* street = dynamic_cast<Street*>(field.get())) {
                        if (street->getHouseCount() != 0) {
                            return -1;
                        }
                    }
                    if (unMortgage && ownableField->isMortgaged()) {
                        players[player].setBalance(players[player].getBalance() + ownableField->mortgage());
                        return 1;
                    }
                    else if (!unMortgage && !ownableField->isMortgaged()) {
                        players[player].setBalance(players[player].getBalance() - ownableField->unmortgage());
                        return 2;
                    }
                    else {
                        return -2;
                    }
                }
            }
        }
        return -3;
    }

    int Game::playerBuysHouse(size_t& player, size_t& fieldPosition, bool sellsHouse) {
        for (auto& field: fields) {
            if (field->getPosition() == fieldPosition) {
                if (Street* street = dynamic_cast<Street*>(field.get())) {
                    if (sellsHouse && street->getHouseCount() > 0) {
                        players[player].setBalance(players[player].getBalance() + street->sellHouse());
                        return 1;
                    }
                    else if (!sellsHouse && street->getHouseCount() < 5) {
                        players[player].setBalance(players[player].getBalance() - street->purchaseHouse());
                        return 2;
                    }
                    else {
                        return -1;
                    }
                }
            }
        }
        return -2;
    }

    int Game::buyOwnableField() {
        for (auto& field: fields) {
            if (field->getPosition() == players[currentPlayer].getPosition()) {
                if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get())) {
                    if (ownableField->isOwned()) {
                        return -1;
                    }
                    else {
                        int price = players[currentPlayer].getBalance() - ownableField->getPurchasePrice();
                        if (price >= 0) {
                            ownableField->setOwner(currentPlayer);
                            players[currentPlayer].setBalance(price);
                            return 1;
                        }
                        return -2;
                    }
                }
            }
        }
        return -3;
    }

    bool Game::sellOwnableField(size_t& player, size_t& fieldPosition) {
        for (auto& field: fields) {
            if (field->getPosition() == fieldPosition) {
                if (Street* street = dynamic_cast<Street*>(field.get())) {
                    if (street->getHouseCount() > 0) {
                        return -1;
                    }
                }
                if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get())) {
                    if (ownableField->isOwned()) {
                        return -2;
                    }
                    else {
                        if (ownableField->getOwner() == player) {
                            players[player].setBalance(players[player].getBalance() + ownableField->getPurchasePrice());
                            ownableField->setOwner(player);
                            return 1;
                        }
                        return -3;
                    }
                }
            }
        }
        return -4;
    }

    size_t Game::movePlayer() {
        size_t currentPosition = players[currentPlayer].getPosition();
        size_t newPosition = (currentPosition + dice.first + dice.second) % 40;

        if (newPosition < currentPosition) {
            players[currentPlayer].setBalance(players[currentPlayer].getBalance() + 200);
        }

        players[currentPlayer].setPosition(newPosition);

        for (const auto& field: fields) {
            if (field->getPosition() == newPosition) {
                TYPE currentType = field->getInfo();
                if (currentType == TYPE::STREET) {

                }
                else if (currentType == TYPE::STATION) {

                }
                else if (currentType == TYPE::UTILITY) {

                }
                else if (currentType == TYPE::CHANCEFIELD) {
                    EventCard currentChance = chances[chancesCounter - 1];
                    executeEventCard(currentChance);
                    if (--chancesCounter == 0) {
                        chances.shuffle();
                        chancesCounter = chances.length();
                    }
                }
                else if (currentType == TYPE::COMMUNITYCHESTFIELD) {
                    EventCard currentCommunityChest = communityChests[communityChestsCounter - 1];
                    executeEventCard(currentCommunityChest);
                    if (--communityChestsCounter == 0) {
                        chances.shuffle();
                        communityChestsCounter = communityChests.length();
                    }
                }
                else if (currentType == TYPE::GOTOJAIL) {
                    players[currentPlayer].setPosition(10);
                    players[currentPlayer].setInJailRounds(3);
                }
                else if (currentType == TYPE::INCOMETAX || field->getInfo() == TYPE::LUXURYTAX) {
                    FinancialField* financialField = dynamic_cast<FinancialField*>(field.get());
                    int newBalance = players[currentPlayer].getBalance() - financialField->getIncome();
                }
                return players[currentPlayer].getPosition();
            }
        }
        return -1;
    }

    bool Game::useGetOutOfJailCard() {
        if (players[currentPlayer].getGetOutOfJailCard() && players[currentPlayer].getInJailRounds() > 0) {
            players[currentPlayer].setGetOutOfJailCard(false);
            players[currentPlayer].setInJailRounds(0);
            return true;
        }
        return false;
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

    void Game::executeEventCard(const EventCard& eventCard) {
        if (eventCard.getBankBalance() != 0) {
            players[currentPlayer].setBalance(players[currentPlayer].getBalance() + eventCard.getBankBalance());
        }
        else if (eventCard.getLocation() >= 0) {
            MovementType movType = eventCard.getMovementType();
            //
        }
    }
}