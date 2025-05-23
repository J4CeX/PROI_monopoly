#pragma once
#include "Field.hpp"

namespace Fields {
    class GoToJail: public Field {
        public:
            GoToJail(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::GOTOJAIL; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<GoToJail>(*this); }
            ~GoToJail() = default;
            friend std::istream& operator>>(std::istream& is, GoToJail& goToJail) {
                is >> goToJail.position;
                return is;
            }
    };
}