#pragma once

#include <string>
#include <iostream>

namespace Events {

enum class CardType { chance, communityChest };
enum class MovementType { relativeForward, relativeBackward, absolute };

class EventCard {
    MovementType movement;
    unsigned int distance;  // distance or position

    bool filled;

    public:
        // ID for GUI graphics use
        unsigned int id;
        CardType type;
        std::string text;

        int bankBalance;  // "collect", "pay"
        int eachPlayerBalance;  // "pay each player", "collect from each player"

        unsigned int perHouseBalance;  // "pay per house"
        unsigned int perHotelBalance;  // "pay per hotel"

        bool goFieldCollectable; // "collect"/"don't collect" if passing GO

        bool isGetOutOfJailFree;

        EventCard() = default;
        unsigned int movementTarget(const unsigned int currentField, const unsigned int fieldCount) const;

        friend std::istream& operator>>(std::istream& is, EventCard& ec);
        friend std::ostream& operator<<(std::ostream& os, const EventCard& ec);
};

}
