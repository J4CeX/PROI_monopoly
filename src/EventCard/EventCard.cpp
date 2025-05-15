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


