#pragma once
#include "Field.hpp"

class Parking: public Field {
    public:
        Parking(int position): Field(position) {}
        Parking(const Parking &secParking);
        TYPE getInfo() const override { return TYPE::PARKING; }
        Parking& operator=(const Parking &secParking);
        ~Parking() = default;
};