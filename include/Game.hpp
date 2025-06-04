#pragma once

#include <iostream>
#include <vector>
#include "Field/headers.hpp"
#include "Player.hpp"
#include "EventCardContainer.hpp"
#include <memory>
#include <fstream>
#include <filesystem>

using namespace Fields;
using namespace Events;
using namespace MonopolyPlayer;

namespace Monopoly {
    using fptr = std::unique_ptr<Field>;
    using pint = std::pair<int, int>;

    class Game {
        private:
            bool filled;
            bool isFinished;
            bool shuffleEventCards_;

            // Randomness source
            std::random_device randomDevice;
            std::mt19937 gen;
            std::uniform_int_distribution<> distribution;

            EventCardContainer chances;
            EventCardContainer communityChests;

            std::vector<fptr> fields;

            std::vector<Player> players;
            size_t currentPlayer;

            pint dice;
            int diceDoubleCounter;

            int turnCounter;
            EventCard currentEvent;

            int chancesCounter;
            int communityChestsCounter;

            void setEventCards();
            void executeEventCard(const EventCard& eventCard);

            void setFields();
            template<typename T>
            void pushField(const T& field) { fields.push_back(std::make_unique<T>(field)); }

            void movePlayer(size_t newPosition, bool goFieldCollectable = true);

            virtual int randomNumber();

        public:
            Game(bool shuffleEventCards = true);
            Game(const Game& secGame);
            Game& operator=(const Game& secGame);
            Game(Game&& secGame);
            Game& operator=(Game&& secGame);
            ~Game() = default;

            // Constructed correctly
            bool isFilled() const { return filled; };

            // Event cards
            const EventCardContainer& getChances() const { return chances; }
            const EventCardContainer& getCommunityChests() const { return communityChests; }

            // Fields
            const std::vector<fptr>& getFields() const { return fields; }

            // Players
            const std::vector<Player>& getPlayers() const { return players; }
            bool addPlayer(Player& newPlayer);

            // Dice
            void rollDice();
            pint getDice() const { return dice; }
            int getDiceDoubleCounter() const { return diceDoubleCounter; }

            // Game loop
            int getTurnCounter() const { return turnCounter; }
            size_t findNextPlayer();
            size_t getCurrentPlayerId() const { return players[currentPlayer].getPlayerId(); }
            bool useGetOutOfJailCard();
            bool checkIfPlayerIsBankrupt();
            int playerMortgageField(size_t& player, size_t& fieldPosition, bool unMortgage = false);
            int playerBuyHouse(size_t& player, size_t& fieldPosition, bool sellHouse = false);
            int buyOwnableField();
            int sellOwnableField(size_t& player, size_t& fieldPosition);
            bool getIsFinished() { return isFinished; }
            const EventCard& getCurrentEvent() { return currentEvent; }

            bool save() const;
            bool load();

            friend std::ostream& operator<<(std::ostream& os, const Game& game);
            friend std::istream& operator>>(std::istream& is, Game& game);
    };
}