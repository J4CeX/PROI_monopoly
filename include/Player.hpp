#pragma once

#include <string>

namespace Player {

// Current "Standard Edition" tokens
enum class Token {
    raceCar,
    topHat,
    thimble,
    scottishTerrier,
    sackOfMoney,
    cat,
    penguin,
    rubberDuck
};

class Player {
    private:
        unsigned int playerId;
        std::string name;

        bool isBankrupt;

        Token token;

        size_t position;

        unsigned int balance;

        int inJailRounds;
        bool hasGetOutOfJailCard;

    public:
        Player() = default;
};

}