#pragma once
#include "FinancialField.hpp"

namespace Fields {
    class StartField: public Field {
        public:
            StartField() = default;
            StartField(int position): Field(position) {}
            TYPE getInfo() const override { return TYPE::STARTFIELD; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<StartField>(*this); }
            ~StartField() = default;
            friend std::istream& operator>>(std::istream& is, StartField& startField) {
                is >> startField.position;
                return is;
            }
    };
}