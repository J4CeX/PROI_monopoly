#pragma once
#include "EventField.hpp"

class ChanceField: public EventField {
    public:
        ChanceField(int position): EventField(position) {}
        ChanceField(const ChanceField &secChanceField);
        ChanceField& operator=(const ChanceField &secChanceField);
        ~ChanceField() = default;
};