#include "EventCardContainer.hpp"
#include "Logger.hpp"

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

    LOG(0, "EventCardContainer shuffled");
};

void EventCardContainer::addCard(const EventCard& newCard) {
    cards_.push_back(newCard);

    LOGI(0, "EventCard added to container:", newCard.getCardId());
}

EventCard& EventCardContainer::operator[](int index) {
    try {
        return cards_[index];
    }
    catch (...) {
        LOG(3, "Accessed EventCardContainer with a out-of-bounds index");
        throw;
    }
}
}
