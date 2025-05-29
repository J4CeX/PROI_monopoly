#pragma once

#include <string>
#include <iostream>

namespace Events {

enum class CardType { chance, communityChest };
enum class MovementType { relativeForward, relativeBackward, absolute };

class EventCard {
	private:
		bool filled_;

		MovementType movement_;
		unsigned int location_;  // distance or position

        // ID for GUI graphics use
        unsigned int cardId_;
        CardType type_;
        std::string text_;

        int bankBalance_;  // "collect", "pay"
        int eachPlayerBalance_;  // "pay each player", "collect from each player"

        unsigned int perHouseBalance_;  // "pay per house"
        unsigned int perHotelBalance_;  // "pay per hotel"

        bool goFieldCollectable_; // "collect"/"don't collect" if passing GO

        bool isGetOutOfJailFree_;

		public:
        EventCard():
			filled_(false),
			movement_(MovementType::relativeForward), location_(0),
			cardId_(0), type_(CardType::chance), text_(),
			bankBalance_(0), eachPlayerBalance_(0),
			perHouseBalance_(0), perHotelBalance_(0),
			goFieldCollectable_(true), isGetOutOfJailFree_(false) {};

		EventCard(const MovementType& mt, unsigned int loc,
				  unsigned int cId, const CardType& ct, const std::string& t,
				  int bb, int pb,
				  unsigned int phob, unsigned int phtb,
				  bool go, bool jail):
			movement_(mt), location_(loc),
			cardId_(cId), type_(ct), text_(t),
			bankBalance_(bb), eachPlayerBalance_(pb),
			perHouseBalance_(phob), perHotelBalance_(phtb),
			goFieldCollectable_(go), isGetOutOfJailFree_(jail) {
				if (text_.size() != 0) {
					filled_ = true;
				}
			};

		bool isFilled() const { return filled_; };
		MovementType getMovementType() const { return movement_; };
		unsigned int getLocation() const { return location_; };
		unsigned int getCardId() const { return cardId_; };
		CardType getCardType() const { return type_; };
		std::string getText() const { return text_; };
		int getBankBalance() const { return bankBalance_; };
		int getEachPlayerBalance() const { return eachPlayerBalance_; };
		unsigned int getPerHouseBalance() const { return perHouseBalance_; };
		unsigned int getPerHotelBalance() const { return perHotelBalance_; };
		bool isGoFieldCollectable() const { return goFieldCollectable_; };
		bool isGetOutOfJailFree() const { return isGetOutOfJailFree_; };

        unsigned int movementTarget(const unsigned int currentField, const unsigned int fieldCount) const;

        friend std::istream& operator>>(std::istream& is, EventCard& ec);
        friend std::ostream& operator<<(std::ostream& os, const EventCard& ec);
};

}
