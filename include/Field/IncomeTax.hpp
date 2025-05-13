#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class IncomeTax: public FinancialField {
        public:
            IncomeTax(int position): FinancialField(position, -200) {}
            TYPE getInfo() const override { return TYPE::INCOMETAX; }
            ~IncomeTax() = default;
    };
}