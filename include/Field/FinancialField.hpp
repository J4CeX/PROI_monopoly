#pragma once
#include <Field.hpp>

class FinancialField: public Field {
    protected:
        int income;
    public:
        FinancialField(int position, int income): Field(position), income(income) {}
        FinancialField(const FinancialField &secFinancialField);
        int getIncome() const { return income; }
        virtual TYPE getInfo() const = 0;
        FinancialField& operator=(const FinancialField &secFinancialField);
        virtual ~FinancialField() = default;
};