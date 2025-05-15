#pragma once

#include <vector>
#include <random>

#include "EventCard.hpp"

class EventCardContainer {
    std::vector<EventCard> cards_;

    public:
        EventCardContainer() = default;

        bool addCard(const EventCard& newCard);

        size_t length() const { return cards_.size(); };
        void shuffle();

        // Iterator for EventCards
        class Iterator {
            public:
                Iterator(std::vector<EventCard>::iterator it);
                EventCard operator*() const;
                EventCardContainer& operator++();
                bool operator!=(const Iterator &other) const;

            private:
                std::vector<EventCard>::iterator current;
        };

        Iterator begin();
        Iterator end();

};
