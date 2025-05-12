#pragma once
#include "Field.hpp"

namespace Fields {
    class GoToJail: public Field {
        public:
            GoToJail(int position): Field(position) {}
            GoToJail(const GoToJail &secGoToJail);
            TYPE getInfo() const override { return TYPE::GOTOJAIL; }
            GoToJail& operator=(const GoToJail &secGoToJail);
            ~GoToJail() = default;
    };
}