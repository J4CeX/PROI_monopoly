#pragma once
#include <iostream>
#include <vector>
#include "Field.hpp"
#include "Player.hpp"
#include "EventCardContainer.hpp"

using namespace Fields;
using namespace Events;
using namespace MonopolyPlayer;
using namespace std;

namespace Monopoly {
    template<typename T>
    using ptr = unique_ptr<T>;
    using pint = pair <int, int>;

    class Game {
        private:
            int turnCounter;
            size_t currentPlayer;
            pint dice;
            int diceDubletCounter;
            vector<ptr<Field>> fields;
            EventCardContainer chances;
            EventCardContainer communityChests;
            vector<Player> players;

            bool canFieldBeBought();
            void rollDice();
        public:
            Game();
            Game(const Game& secGame);
            Game(Game&& secGame);
            bool isFinished();
            size_t findNextPlayer();
            bool mortgageField(size_t& player, size_t& field, bool unMortgage = false) const;
            bool boolplayerBuysHouse(size_t& player, size_t& field, bool sellsHouse = false) const;
            void buyOwnableField();
            void sellOwnableField();
            size_t movePlayer();
            void useGetOutOfJailCard();
            Game& operator=(const Game& secGame);
            Game& operator=(Game&& secGame);
            Field& operator[](int index) const;
            ~Game();

            pint getDice() const { return dice; }
            int getTurnCounter() const { return turnCounter; }
            size_t getCurrentPlayer() const { return currentPlayer; }
            int getDiceDubletCounter() const { return diceDubletCounter; }
            const EventCardContainer& getChances() const { return chances; }
            const EventCardContainer& getCommunityChests() const { return communityChests; }
            const vector<Player>& getPlayers() const { return players; }
    };
}