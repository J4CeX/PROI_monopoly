#pragma once
#include "OwnableField.hpp"

class Utility: public OwnableField {
    public:
        Utility(int position, const std::string &name, int purchasePrice, int trespassingFee)
        : OwnableField(position, name, purchasePrice, trespassingFee) {}
        Utility(const Utility &secUtility);
        Utility operator=(const Utility &secUtility);
        ~Utility() = default;
};