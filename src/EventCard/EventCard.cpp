#include "EventCard.hpp"
#include "Logger.hpp"

namespace Events {

unsigned int EventCard::movementTarget(unsigned int currentField, unsigned int fieldCount) const {
    int out = 0;

    if (movement_ == MovementType::relativeForward) {
        out = (currentField + location_) % fieldCount;
    } else if (movement_ == MovementType::relativeBackward) {
        out = (signed)(currentField - location_);

        if (out < 0) {
            out += fieldCount;
        }
    } else { // if (movement_ == MovementType::absolute) {
        out = location_ % fieldCount;
    }

    return out;
}

// Serialization for MovementType
std::istream& operator>>(std::istream& is, MovementType& mt) {
    unsigned int t;
    is >> t;

    if (!is) {
        return is;
    }

    if (t == 0) {
        mt = MovementType::relativeForward;
    } else if(t == 1) {
        mt = MovementType::relativeBackward;
    } else if (t == 2) {
        mt = MovementType::absolute;
    } else {
        is.setstate(std::ios::failbit);

        LOG(3, "Attempted to deserialize an unspecified MovementType");
    }

    return is;
};

std::ostream& operator<<(std::ostream& os, const MovementType& mt) {
    if (mt == MovementType::relativeForward) {
        return os << 0;
    } else if (mt == MovementType::relativeBackward) {
        return os << 1;
    } else if (mt == MovementType::absolute) {
        return os << 3;
    }

    return os << 4;
};

// Serialization for CardType
std::istream& operator>>(std::istream& is, CardType& ct) {
    unsigned int t;
    is >> t;

    if (!is) {
        return is;
    }

    if (t == 0) {
        ct = CardType::chance;
    } else if (t == 1) {
        ct = CardType::communityChest;
    } else {
        is.setstate(std::ios::failbit);

        LOG(3, "Attempted to deserialize an unspecified CardType");
    }

    return is;
};

std::ostream& operator<<(std::ostream& os, const CardType& ct) {
    if (ct == CardType::chance) {
        return os << 0;
    } else if (ct == CardType::communityChest) {
        return os << 1;
    }

    return os << 2;
};

// Serialization for EventCard
std::istream& operator>>(std::istream& is, EventCard& ec) {
    is >> ec.cardId_ >> ec.type_
       >> ec.movement_ >> ec.location_
       >> ec.bankBalance_ >> ec.eachPlayerBalance_
       >> ec.perHouseBalance_ >> ec.perHotelBalance_
       >> ec.goFieldCollectable_ >> ec.isGetOutOfJailFree_
	   >> std::ws;

	std::getline(is, ec.text_);

    if (is) {
        ec.filled_ = true;

        LOG(0, "EventCard loaded with ID:", ec.cardId_);
    } else {
        LOG(3, "Attempted to deserialize an EventCard, but istream failed");
    }

    return is;
};

std::ostream& operator<<(std::ostream& os, const EventCard& ec) {
    os << ec.cardId_ << " " << ec.type_ << " "
       << ec.movement_ << " " << ec.location_ << " "
       << ec.bankBalance_ << " " << ec.eachPlayerBalance_ << " "
       << ec.perHouseBalance_ << " " << ec.perHotelBalance_ << " "
       << std::noboolalpha
       << ec.goFieldCollectable_ << " " << ec.isGetOutOfJailFree_ << " "
       << ec.text_ << std::endl;

    return os;
};

}
