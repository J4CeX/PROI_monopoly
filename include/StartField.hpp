#pragma once
#include "FinancialField.hpp"

class StartField: public FinancialField {
    public:
        StartField(int position): FinancialField(position, 200) {}
        StartField(const StartField &secStartField);
        StartField operator=(const StartField &secStartField);
        ~StartField() = default;
};