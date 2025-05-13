#pragma once
#include "Field.hpp"

namespace Fields {
    class EventField: public Field {
        public:
            EventField(int position): Field(position) {}
            virtual TYPE getInfo() const = 0;
            virtual ~EventField() = default;
    };
}