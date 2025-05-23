#pragma once
#include "Field.hpp"

namespace Fields {
    class FinancialField: public Field {
        protected:
            int income;
        public:
            FinancialField(int position, int income): Field(position), income(income) {}
            int getIncome() const { return income; }
            virtual TYPE getInfo() const = 0;
            virtual ~FinancialField() = default;
            friend std::istream& operator>>(std::istream& is, FinancialField& financialField) {
                is >> financialField.position;
                return is;
            }
    };
}