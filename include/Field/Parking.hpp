#pragma once
#include "Field.hpp"

namespace Fields {
    class Parking: public Field {
        public:
            Parking(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::PARKING; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Parking>(*this); }
            ~Parking() = default;
    };
}