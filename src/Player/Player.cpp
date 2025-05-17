#include "Player.hpp"

namespace Player {
// Serialization for Token
std::istream& operator>>(std::istream& is, Token& t) {
    unsigned int v;
    is >> v;

    if (!is) {
        return is;
    }

    if (v == 0) {
        t = Token::raceCar;
    } else if (v == 1) {
        t = Token::topHat;
    } else if (v == 2) {
        t = Token::thimble;
    } else if (v == 3) {
        t = Token::scottishTerrier;
    } else if (v == 4) {
        t = Token::sackOfMoney;
    } else if (v == 5) {
        t = Token::cat;
    } else if (v == 6) {
        t = Token::penguin;
    } else if (v == 7) {
        t = Token::rubberDuck;
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
};

std::ostream& operator<<(std::ostream& os, const Token& t) {
    if (t == Token::raceCar) {
		return os << 0;
	} else if (t == Token::topHat) {
		return os << 1;
	} else if (t == Token::thimble) {
		return os << 2;
	} else if (t == Token::scottishTerrier) {
		return os << 3;
	} else if (t == Token::sackOfMoney) {
		return os << 4;
	} else if (t == Token::cat) {
		return os << 5;
	} else if (t == Token::penguin) {
		return os << 6;
	} else if (t == Token::rubberDuck) {
		return os << 7;
	} else

    return os << 8;
};


// Player class implementation
Player::Player(const unsigned int id, const std::string name, const Token token,
			   const int balance, const bool bankrupt,
			   const size_t pos, const int jailRounds, const bool jailCard) :
		playerId_(id), name_(name), token_(token), balance_(balance), isBankrupt_(bankrupt),
		position_(pos), inJailRounds_(jailRounds), hasGetOutOfJailCard_(jailCard),
		filled_(true) {};

int Player::setBalance(const int currentBalance) {
	balance_ = currentBalance;
	return balance_;
};

size_t Player::setPosition(const size_t currentPosition) {
	position_ = currentPosition;
	return position_;
};

int Player::setInJailRounds(const int currentRounds) {
	inJailRounds_ = currentRounds;
	return inJailRounds_;
};

bool Player::setGetOutOfJailCard(const bool hasCard) {
	hasGetOutOfJailCard_ = hasCard;
	return hasGetOutOfJailCard_;
};

// Serialization for Player
std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.playerId_ << p.token_
	   << p.balance_
	   << std::noboolalpha << p.isBankrupt_
	   << p.position_ << p.inJailRounds_
	   << p.hasGetOutOfJailCard_
	   << p.name_ << std::endl;

	return os;
};

// Used friend function to avoid constructing a new object
// Then, the above use of private fields is for consistency with below
std::istream& operator>>(std::istream& is, Player& p) {
	is >> p.playerId_ >> p.token_
	   >> p.balance_ >> p.isBankrupt_
	   >> p.position_ >> p.inJailRounds_
	   >> p.hasGetOutOfJailCard_
	   >> std::skipws;

	std::getline(is, p.name_);

	if (is) {
		p.filled_ = true;
	}

	return is;
};

}