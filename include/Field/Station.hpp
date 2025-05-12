#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Station: public OwnableField {
        public:
            Station(int position, const std::string &name, int purchasePrice, int housePrice, int trespassingFee)
            : OwnableField(position, name, purchasePrice, trespassingFee) {}
            Station(const Station &secStation);
            TYPE getInfo() const override { return TYPE::STATION; }
            Station& operator=(const Station &secStation);
            ~Station() = default;
    };
}