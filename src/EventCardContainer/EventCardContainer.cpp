#include "EventCardContainer.hpp"

namespace Events {

// EventCard iterator implementation
EventCardContainer::Iterator::Iterator(std::vector<EventCard>::iterator it) : current(it) {}

EventCard EventCardContainer::Iterator::operator*() const {
    return *current;
};

EventCardContainer::Iterator& EventCardContainer::Iterator::operator++() {
    ++current;
    return *this;
};

bool EventCardContainer::Iterator::operator!=(const Iterator &other) const {
    return current != other.current;
};

// Begin and end functions
EventCardContainer::Iterator EventCardContainer::begin() {
    return Iterator(cards_.begin());
};

EventCardContainer::Iterator EventCardContainer::end() {
    return Iterator(cards_.end());
};


// Container operations
void EventCardContainer::shuffle() {
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());

    std::shuffle(cards_.begin(), cards_.end(), randomGenerator);
};

bool EventCardContainer::addCard(const EventCard& newCard) {
    cards_.push_back(newCard);
    return true;
}

EventCard& EventCardContainer::operator[](int index) {
    try {
        return cards_[index];
    }
    catch (std::exception& exc) {
        std::cerr << "Out of index error! (EventCardContainer)" << std::endl;
    }
}
}
