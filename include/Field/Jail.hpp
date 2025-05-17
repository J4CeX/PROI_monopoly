#pragma once
#include "Field.hpp"

namespace Fields {
    class Jail: public Field {
        public:
            Jail(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::JAIL; }
            ~Jail() = default;
    };
}