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

            bool canFieldBeBought();
            void rollDice();

            void setFields();
            void setEventCards();

            template<typename T>
            void pushField(const T& field) { fields.push_back(make_unique<T>(field)); }
        public:
            Game();
            Game(const Game& secGame);
            Game(Game&& secGame);
            bool isFinished();
            size_t findNextPlayer();
            bool addPlayer(Player& newPlayer);
            bool playerMortgageField(size_t& player, size_t& field, bool unMortgage = false) const;
            bool playerBuysHouse(size_t& player, size_t& field, bool sellsHouse = false) const;
            void buyOwnableField();
            bool sellOwnableField(size_t& player, size_t& field);
            size_t movePlayer();
            void useGetOutOfJailCard();
            Game& operator=(const Game& secGame);
            Game& operator=(Game&& secGame);
            Field& operator[](int index) const;
            ~Game() = default;

            pint getDice() const { return dice; }
            int getTurnCounter() const { return turnCounter; }
            size_t getCurrentPlayer() const { return currentPlayer; }
            int getDiceDubletCounter() const { return diceDubletCounter; }
            const EventCardContainer getChances() const { return chances; }
            const EventCardContainer getCommunityChests() const { return communityChests; }
            const vector<Player> getPlayers() const { return players; }
    };
}