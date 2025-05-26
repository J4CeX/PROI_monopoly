#pragma once
#include "Field.hpp"

namespace Fields {
    class EventField: public Field {
        public:
            EventField() = default;
            EventField(int position): Field(position) {}
            virtual TYPE getInfo() const = 0;
            virtual ~EventField() = default;
            friend std::istream& operator>>(std::istream& is, EventField& eventField) {
                is >> eventField.position;
                return is;
            }
    };
}