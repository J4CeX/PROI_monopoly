#pragma once
#include "Field.hpp"

namespace Fields {
    class EventField: public Field {
        public:
            EventField(int position): Field(position) {}
            EventField(const EventField &secEventField);
            virtual TYPE getInfo() const = 0;
            EventField& operator=(const EventField &secEventField);
            virtual ~EventField() = default;
    };
}