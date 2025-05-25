#pragma once
#include "Field.hpp"

namespace Fields {
    class Jail: public Field {
        public:
            Jail() = default;
            Jail(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::JAIL; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Jail>(*this); }
            ~Jail() = default;
            friend std::istream& operator>>(std::istream& is, Jail& jail) {
                is >> jail.position;
                return is;
            }
    };
}