#pragma once
#include <Field.hpp>

class FinancialField: public Field {
    protected:
        int income;
    public:
        FinancialField() = default;
        FinancialField(const FinancialField &secFinancialField);
        FinancialField operator=(const FinancialField &secFinancialField);
        ~FinancialField() = default;
};