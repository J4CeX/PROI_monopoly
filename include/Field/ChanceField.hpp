#pragma once
#include "EventField.hpp"

namespace Fields {
    class ChanceField: public EventField {
        public:
            ChanceField(int position): EventField(position) {}
            TYPE getInfo() const override { return TYPE::CHANCEFIELD; }
            ~ChanceField() = default;
    };
}