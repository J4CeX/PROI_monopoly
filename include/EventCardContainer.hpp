#pragma once

#include <vector>
#include <random>
#include <algorithm>

#include "EventCard.hpp"

namespace Events {

class EventCardContainer {
	private:
    	std::vector<EventCard> cards_;

    public:
        EventCardContainer() = default;

        bool addCard(const EventCard& newCard);

        size_t length() const { return cards_.size(); };
        void shuffle();

        EventCard& operator[](int index);

        // Iterator for EventCards
        class Iterator {
            public:
                Iterator(std::vector<EventCard>::iterator it);
                EventCard operator*() const;
                EventCardContainer::Iterator& operator++();
                bool operator!=(const Iterator &other) const;

            private:
                std::vector<EventCard>::iterator current;
        };

        Iterator begin();
        Iterator end();

};

}
