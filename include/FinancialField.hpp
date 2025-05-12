#pragma once
#include <Field.hpp>

class FinancialField: public Field {
    protected:
        int income;
    public:
    FinancialField(int position, int income): Field(position), income(income) {}
        FinancialField(const FinancialField &secFinancialField);
        FinancialField operator=(const FinancialField &secFinancialField);
        virtual ~FinancialField() = default;
};