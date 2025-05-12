#pragma once
#include "EventField.hpp"

class ChanceField: public EventField {
    public:
        ChanceField(int position): EventField(position) {}
        ChanceField(const ChanceField &secChanceField);
        TYPE getInfo() const override { return TYPE::CHANCEFIELD; }
        ChanceField& operator=(const ChanceField &secChanceField);
        ~ChanceField() = default;
};