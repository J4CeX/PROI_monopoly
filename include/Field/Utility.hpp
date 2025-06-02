#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Utility: public OwnableField {
        public:
            Utility() = default;
            Utility(int position, const std::string &name)
            : OwnableField(position, name, 150, 0) {}
            TYPE getInfo() const override { return TYPE::UTILITY; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Utility>(*this); }
            int getRent(int diceSum) const { return diceSum * 4; }
            ~Utility() = default;
            friend std::istream& operator>>(std::istream& is, Utility& utility) {
                is >> utility.position >> std::ws;
                std::getline(is, utility.name);
                return is;
            }
    };
}