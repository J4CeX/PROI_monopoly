#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class IncomeTax: public FinancialField {
        public:
            IncomeTax() = default;
            IncomeTax(int position): FinancialField(position, 200) {}
            TYPE getInfo() const override { return TYPE::INCOMETAX; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<IncomeTax>(*this); }
            ~IncomeTax() = default;
    };
}