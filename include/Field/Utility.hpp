#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Utility: public OwnableField {
        public:
            Utility(int position, const std::string &name, int purchasePrice, int trespassingFee)
            : OwnableField(position, name, purchasePrice, trespassingFee) {}
            TYPE getInfo() const override { return TYPE::UTILITY; }
            ~Utility() = default;
    };
}