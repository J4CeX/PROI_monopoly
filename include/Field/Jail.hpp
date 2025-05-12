#pragma once
#include "Field.hpp"

class Jail: public Field {
    public:
        Jail(int position): Field(position) {}
        Jail(const Jail &secJail);
        Jail& operator=(const Jail &secJail);
        ~Jail() = default;
};