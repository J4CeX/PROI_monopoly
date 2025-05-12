#pragma once
#include "FinancialField.hpp"

class IncomeTax: public FinancialField {
    public:
        IncomeTax(int position): FinancialField(position, -200) {}
        IncomeTax(const IncomeTax &secIncomeTax);
        IncomeTax& operator=(const IncomeTax &secIncomeTax);
        ~IncomeTax() = default;
};