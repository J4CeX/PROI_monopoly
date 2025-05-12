#pragma once
#include "Field.hpp"

class EventField: public Field {
    public:
        EventField(int position): Field(position) {}
        EventField(const EventField &secEventField);
        EventField& operator=(const EventField &secEventField);
        virtual ~EventField() = default;
};