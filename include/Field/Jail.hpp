#pragma once
#include "Field.hpp"

class Jail: public Field {
    public:
        Jail(int position): Field(position) {}
        Jail(const Jail &secJail);
        TYPE getInfo() const override { return TYPE::JAIL; }
        Jail& operator=(const Jail &secJail);
        ~Jail() = default;
};