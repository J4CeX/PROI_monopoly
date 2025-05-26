#pragma once

#include <string>
#include <iostream>

namespace MonopolyPlayer {

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
		bool filled_;

        unsigned int playerId_;
        std::string name_;
        Token token_;

        int balance_;
        bool isBankrupt_;

        size_t position_;
        int inJailRounds_;
        bool hasGetOutOfJailCard_;

    public:
        Player() = default;
        Player(const unsigned int id, const std::string name, const Token token,
			   const int balance = 500, const bool bankrupt = false,
			   const size_t pos = 0, const int jailRounds = 0, const bool jailCard = false);

		unsigned int getPlayerId() const { return playerId_; };
		std::string getName() const { return name_; };
		Token getToken() const { return token_; };
		int getBalance() const { return balance_; };
		bool getIsBankrupt() const { return isBankrupt_; };
		size_t getPosition() const { return position_; };
		int getInJailRounds() const { return inJailRounds_; };
		bool getGetOutOfJailCard() const { return hasGetOutOfJailCard_; };

		int setBalance(const int currentBalance);
		size_t setPosition(const size_t currentPosition);
		int setInJailRounds(const int currentRounds);
		bool setGetOutOfJailCard(const bool hasCard);

	friend std::istream& operator>>(std::istream& is, Player& p);
	friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

}