#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class StartField: public Field {
        public:
            StartField(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::STARTFIELD; }
            ~StartField() = default;
    };
}