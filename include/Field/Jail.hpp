#pragma once
#include "Field.hpp"

namespace Fields {
    class Jail: public Field {
        public:
            Jail(int position): Field(position) {}
            Jail(const Jail &secJail);
            TYPE getInfo() const override { return TYPE::JAIL; }
            Jail& operator=(const Jail &secJail);
            ~Jail() = default;
    };
}