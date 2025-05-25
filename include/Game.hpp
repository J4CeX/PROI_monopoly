#pragma once
#include <iostream>
#include <vector>
#include "Field/headers.hpp"
#include "Player.hpp"
#include "EventCardContainer.hpp"
#include <memory>
#include <cstdlib>
#include <fstream>

using namespace Fields;
using namespace Events;
using namespace MonopolyPlayer;
using namespace std;

namespace Monopoly {
    using fptr = unique_ptr<Field>;
    using pint = pair <int, int>;

    class Game {
        private:
            int turnCounter;
            size_t currentPlayer;
            pint dice;
            int diceDubletCounter;
            vector<fptr> fields;
            EventCardContainer chances;
            EventCardContainer communityChests;
            vector<Player> players;
            int chancesCounter;
            int communityChestsCounter;

            void setFields();
            void setEventCards();

            void executeEventCard(const EventCard& eventCard);

            void movePlayer(size_t newPosition, bool goFieldCollectable = true);

            template<typename T>
            void pushField(const T& field) { fields.push_back(make_unique<T>(field)); }
        public:
            Game();
            Game(const Game& secGame);
            Game(Game&& secGame);
            bool isFinished();
            void rollDice();
            size_t findNextPlayer();
            bool addPlayer(Player& newPlayer);
            bool checkIfBankrupt();
            int playerMortgageField(size_t& player, size_t& fieldPosition, bool unMortgage = false);
            int playerBuysHouse(size_t& player, size_t& fieldPosition, bool sellsHouse = false);
            int buyOwnableField();
            int sellOwnableField(size_t& player, size_t& fieldPosition);
            bool useGetOutOfJailCard();
            Game& operator=(const Game& secGame);
            Game& operator=(Game&& secGame);
            ~Game() = default;

            pint getDice() const { return dice; }
            int getTurnCounter() const { return turnCounter; }
            size_t getCurrentPlayer() const { return currentPlayer; }
            int getDiceDubletCounter() const { return diceDubletCounter; }
            const EventCardContainer& getChances() const { return chances; }
            const EventCardContainer& getCommunityChests() const { return communityChests; }
            const vector<Player>& getPlayers() const { return players; }
            const vector<fptr>& getFields() const {return fields; }
    };
}