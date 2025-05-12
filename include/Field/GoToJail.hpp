#pragma once
#include "Field.hpp"

class GoToJail: public Field {
    public:
        GoToJail(int position): Field(position) {}
        GoToJail(const GoToJail &secGoToJail);
        GoToJail& operator=(const GoToJail &secGoToJail);
        ~GoToJail() = default;
};