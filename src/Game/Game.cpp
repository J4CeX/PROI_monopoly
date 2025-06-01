#include "Game.hpp"

namespace Monopoly {
    Game::Game():
    turnCounter(0), currentPlayer(0), dice(0, 0),
    diceDoubleCounter(0), filled(false),
    randomDevice(), gen(randomDevice()), distribution(1, 6),
    isFinished(false) {
        try {
            setFields();
        }
        catch (std::exception& exc) {
            std::cerr << exc.what() << std::endl;
            return;
        }

        try {
            setEventCards();

            communityChests.shuffle();
            chances.shuffle();

            communityChestsCounter = communityChests.length();
            chancesCounter = chances.length();
        }
        catch (std::exception& exc) {
            std::cerr << exc.what() << std::endl;
            return;
        }

        filled = true;
    }

    Game::Game(const Game& secGame) {
        turnCounter = secGame.turnCounter;
        currentPlayer = secGame.currentPlayer;
        dice = secGame.dice;
        diceDoubleCounter = secGame.diceDoubleCounter;
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
        diceDoubleCounter = secGame.diceDoubleCounter;
        players = secGame.players;

        chances = secGame.chances;
        communityChests = secGame.communityChests;

        fields = std::move(secGame.fields);
    }

    Game& Game::operator=(const Game& secGame) {
        if (this != &secGame) {
            turnCounter = secGame.turnCounter;
            currentPlayer = secGame.currentPlayer;
            dice = secGame.dice;
            diceDoubleCounter = secGame.diceDoubleCounter;
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
            diceDoubleCounter = secGame.diceDoubleCounter;
            players = secGame.players;

            chances = secGame.chances;
            communityChests = secGame.communityChests;

            fields = std::move(secGame.fields);
        }
        return *this;
    }

    int Game::randomNumber() {
        return distribution(gen);
    }

    void Game::rollDice() {
        dice.first = randomNumber();
        dice.second = randomNumber();

        if (dice.first == dice.second) {
            diceDoubleCounter++;
        } else {
            diceDoubleCounter = 0; // only for doubles rolled in succession
        }

        if (diceDoubleCounter == 3) {
            players[currentPlayer].setPosition(10);
            players[currentPlayer].setInJailRounds(3);
            diceDoubleCounter = 0;
            return;
        }

        // If player in jail and rolled a dublet - get out of jail
        if (diceDoubleCounter > 0 && players[currentPlayer].getInJailRounds() > 0) {
            players[currentPlayer].setInJailRounds(0);
        }
        else if (players[currentPlayer].getInJailRounds() > 0) {
            players[currentPlayer].setInJailRounds(players[currentPlayer].getInJailRounds() - 1);
            return;
        }

        movePlayer((players[currentPlayer].getPosition() + dice.first + dice.second) % 40);
    }

    size_t Game::findNextPlayer() {
        players[currentPlayer].checkIfBankrupt();
        int inGame = 0;
        for (const auto& player: players) {
            if (!player.getIsBankrupt()) {
                inGame++;
            }
        }
        isFinished = inGame > 1 ? false : true;
        if (diceDoubleCounter > 0 && !players[currentPlayer].getIsBankrupt()) {
            return currentPlayer;
        }
        diceDoubleCounter = 0;
        do {
            currentPlayer = ++currentPlayer % players.size();
            if (currentPlayer == 0) {
                turnCounter++;
            }
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

    bool Game::checkIfPlayerIsBankrupt() {
        return (players[currentPlayer].checkIfBankrupt());
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

    int Game::playerBuyHouse(size_t& player, size_t& fieldPosition, bool sellsHouse) {
        for (auto& field: fields) {
            if (field->getPosition() == fieldPosition) {
                if (Street* street = dynamic_cast<Street*>(field.get())) {
                    if (sellsHouse && street->getHouseCount() > 0) {
                        players[player].setBalance(players[player].getBalance() + street->sellHouse());
                        return 1;
                    }
                    else if (!sellsHouse && street->getHouseCount() < 5) {
                        int newBalance = players[player].getBalance() - street->purchaseHouse();
                        if (newBalance >= 0) {
                            players[player].setBalance(newBalance);
                            return 2;
                        }
                        return -1;
                    }
                    else {
                        return -2;
                    }
                }
            }
        }
        return -3;
    }

    int Game::buyOwnableField() {
        for (auto& field: fields) {
            if (field->getPosition() == players[currentPlayer].getPosition()) {
                if (OwnableField* ownableField = dynamic_cast<OwnableField*>(field.get())) {
                    if (ownableField->isOwned()) {
                        return -1;
                    }
                    else {
                        int newBalance = players[currentPlayer].getBalance() - ownableField->getPurchasePrice();
                        if (newBalance >= 0) {
                            ownableField->setOwner(currentPlayer);
                            players[currentPlayer].setBalance(newBalance);
                            return 1;
                        }
                        return -2;
                    }
                }
            }
        }
        return -3;
    }

    int Game::sellOwnableField(size_t& player, size_t& fieldPosition) {
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
                            int price = ownableField->getPurchasePrice();
                            if (ownableField->isMortgaged()) {
                                price /= 2;
                            }
                            players[player].setBalance(players[player].getBalance() + price);
                            ownableField->removeOwner();
                            return 1;
                        }
                        return -3;
                    }
                }
            }
        }
        return -4;
    }

    void Game::movePlayer(size_t newPosition, bool goFieldCollectable) {
        if (goFieldCollectable) {
            size_t currentPosition = players[currentPlayer].getPosition();
            if (newPosition < currentPosition) {
                players[currentPlayer].setBalance(players[currentPlayer].getBalance() + 200);
            }
        }

        players[currentPlayer].setPosition(newPosition);

        for (const auto& field: fields) {
            if (field->getPosition() == newPosition) {
                TYPE currentType = field->getInfo();
                if (currentType == TYPE::STREET) {
                    if(Street* street = dynamic_cast<Street*>(field.get())) {
                        size_t fieldOwner = street->getOwner();
                        if (street->isOwned() && fieldOwner != currentPlayer) {
                            players[currentPlayer].setBalance(players[currentPlayer].getBalance() - street->getRent());
                            players[fieldOwner].setBalance(players[fieldOwner].getBalance() + street->getRent());
                        }
                    }
                }
                else if (currentType == TYPE::STATION) {
                    if (Station* station = dynamic_cast<Station*>(field.get())) {
                        size_t fieldOwner = station->getOwner();
                        if (station->isOwned() && fieldOwner != currentPlayer) {
                            int stationCount = 0;
                            for (const auto& stationField: fields) {
                                if (stationField->getInfo() == TYPE::STREET) {
                                    if (Station* station = dynamic_cast<Station*>(stationField.get())) {
                                        if (fieldOwner == station->getOwner()) {
                                            stationCount++;
                                        }
                                    }
                                }
                            }
                            int price = stationCount * 50;
                            players[currentPlayer].setBalance(players[currentPlayer].getBalance() - price);
                            players[fieldOwner].setBalance(players[fieldOwner].getBalance() + price);
                        }
                    }
                }
                else if (currentType == TYPE::UTILITY) {
                    if (Utility* utility = dynamic_cast<Utility*>(field.get())) {
                        size_t fieldOwner = utility->getOwner();
                        if (utility->isOwned() && fieldOwner != currentPlayer) {
                            int utilityCounter = 0;
                            for (const auto& utilityField: fields) {
                                if (utilityField->getInfo() == TYPE::UTILITY) {
                                    if (Utility* utility = dynamic_cast<Utility*>(utilityField.get())) {
                                        if (fieldOwner == utility->getOwner()) {
                                            utilityCounter++;
                                        }
                                    }
                                }
                            }
                            int price = dice.first + dice.second;
                            if (utilityCounter == 2) {
                                price *= 10;
                            }
                            else if (utilityCounter == 1) {
                                price *= 4;
                            }
                            players[currentPlayer].setBalance(players[currentPlayer].getBalance() - price);
                            players[fieldOwner].setBalance(players[fieldOwner].getBalance() + price);
                        }
                    }
                }
                else if (currentType == TYPE::CHANCEFIELD) {
                    EventCard currentChance = chances[chancesCounter - 1];
                    currentEvent = currentChance;
                    executeEventCard(currentChance);
                    if (--chancesCounter == 0) {
                        chances.shuffle();
                        chancesCounter = chances.length();
                    }
                }
                else if (currentType == TYPE::COMMUNITYCHESTFIELD) {
                    EventCard currentCommunityChest = communityChests[communityChestsCounter - 1];
                    currentEvent = currentCommunityChest;
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
                    if (FinancialField* financialField = dynamic_cast<FinancialField*>(field.get())) {
                        players[currentPlayer].setBalance(players[currentPlayer].getBalance() - financialField->getIncome());

                    }
                }
                break;
            }
        }
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
        std::ifstream file(fieldsPath);
        if (!file.good()) {
            throw (std::invalid_argument("File error! Cannot open fields.txt file! "));
        }

        std::string fieldType;
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
                throw (std::invalid_argument("File error! Corrupted fields.txt file! "));
            }
        }
    }

    void Game::setEventCards() {
        EventCardContainer generatedChances;
        EventCardContainer generatedCommunityChests;

        std::ifstream file(eventCardsPath);
        if (!file.good()) {
            throw (std::invalid_argument("File error: cannot open eventCards.txt file"));
        }

        while(!file.eof()) {
            EventCard eventCard;
            file >> eventCard;

            if (!file) {
                throw std::invalid_argument("File read error: deserialization failed");
            }

            if (eventCard.getCardType() == CardType::chance) {
                generatedChances.addCard(eventCard);
            } else if (eventCard.getCardType() == CardType::communityChest) {
                generatedCommunityChests.addCard(eventCard);
            } else {
                throw (std::invalid_argument("File error: wrong EventCard type"));
            }
        }

        chances = generatedChances;
        communityChests = generatedCommunityChests;
    }

    void Game::executeEventCard(const EventCard& eventCard) {
        // Settle balances
        players[currentPlayer].setBalance(players[currentPlayer].getBalance() + eventCard.getBankBalance());

        if (eventCard.getEachPlayerBalance() != 0) {
            int balanceDiff = 0;
            for (auto &player: players) {
                if (player.getPlayerId() != currentPlayer && !player.getIsBankrupt()) {
                    player.setBalance(player.getBalance() - eventCard.getEachPlayerBalance());
                    balanceDiff += eventCard.getEachPlayerBalance();
                }
            }

            players[currentPlayer].setBalance(players[currentPlayer].getBalance() + balanceDiff);
        }

        // Check for houses and hotels
        unsigned int houseHotelCost = 0;
        for (const auto& field: fields) {
            if (Street* street = dynamic_cast<Street*>(field.get())) {
                if (street->getOwner() == currentPlayer) {
                    if (street->getHouseCount() == 5) {  // 5 houses means exactly one hotel
                        houseHotelCost += eventCard.getPerHotelBalance();
                    } else {
                        houseHotelCost += eventCard.getPerHouseBalance() * street->getHouseCount();
                    }
                }
            }
        }

        // Handle Get Out Of Jail card
        if (eventCard.isGetOutOfJailFree()) {
            players[currentPlayer].setGetOutOfJailCard(true);
        }

        // Move the player
        if (eventCard.getLocation() != 0) {
            size_t targetField = eventCard.movementTarget(players[currentPlayer].getPosition(), fields.size());
            movePlayer(targetField, eventCard.isGoFieldCollectable());
        }
    }
}