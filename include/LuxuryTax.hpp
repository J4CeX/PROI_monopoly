#pragma once
#include "FinancialField.hpp"

class LuxuryTax: public FinancialField {
    public:
        LuxuryTax(int position): FinancialField(position, -100) {}
        LuxuryTax(const LuxuryTax &secLuxuryTax);
        LuxuryTax operator=(const LuxuryTax &secLuxuryTax);
        ~LuxuryTax() = default;
};