#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class StartField: public FinancialField {
        public:
            StartField(int position): FinancialField(position, 200) {}
            TYPE getInfo() const override { return TYPE::STARTFIELD; }
            ~StartField() = default;
    };
}