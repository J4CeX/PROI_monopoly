#include "EventCardContainer.hpp"

// EventCard iterator implementation
EventCardContainer::Iterator::Iterator(std::vector<EventCard>::iterator it) : current(it) {}

EventCard EventCardContainer::Iterator::operator*() const {
    return *current;
}

EventCardContainer::Iterator& EventCardContainer::Iterator::operator++() {
    ++current;
    return *this;
}

bool EventCardContainer::Iterator::operator!=(const Iterator &other) const {
    return current != other.current;
}

// Begin and end functions
EventCardContainer::Iterator EventCardContainer::begin() {
    return Iterator(cards_.begin());
}

EventCardContainer::Iterator EventCardContainer::end() {
    return Iterator(cards_.end());
}
