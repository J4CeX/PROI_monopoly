#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class LuxuryTax: public FinancialField {
        public:
            LuxuryTax(int position): FinancialField(position, 100) {}
            TYPE getInfo() const override { return TYPE::LUXURYTAX; }
            ~LuxuryTax() = default;
    };
}