#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Utility: public OwnableField {
        public:
            Utility(int position, const std::string &name)
            : OwnableField(position, name, 150, 0) {}
            TYPE getInfo() const override { return TYPE::UTILITY; }
            int getRent(int diceSum) const { return diceSum * 4; }
            ~Utility() = default;
    };
}