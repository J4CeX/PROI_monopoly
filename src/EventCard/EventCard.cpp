#include "EventCard.hpp"

unsigned int EventCard::movementTarget(const unsigned int currentField, const unsigned int fieldCount) const {
    if (movement == MovementType::relativeForward) {
        return (currentField + distance) % fieldCount;
    } else if (movement == MovementType::relativeBackward) {
        return (currentField - distance) % fieldCount;
    } else if (movement == MovementType::absolute) {
        return distance % fieldCount;
    }
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
    is >> ec.id >> ec.type
       >> ec.movement >> ec.distance
       >> ec.bankBalance >> ec.eachPlayerBalance
       >> ec.perHouseBalance >> ec.perHotelBalance
       >> ec.goFieldCollectable >> ec.isGetOutOfJailFree;

    if (is) {
        ec.filled = true;
    }

    return is;
};

std::ostream& operator<<(std::ostream& os, const EventCard& ec) {
    os << ec.id << ec.type
       << ec.movement << ec.distance
       << ec.bankBalance << ec.eachPlayerBalance
       << ec.perHouseBalance << ec.perHotelBalance
       << std::noboolalpha
       << ec.goFieldCollectable << ec.isGetOutOfJailFree;

    return os;
};
