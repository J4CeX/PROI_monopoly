#pragma once
#include "OwnableField.hpp"

class Station: public OwnableField {
    public:
        Station(int position, const std::string &name, int purchasePrice, int housePrice, int trespassingFee)
        : OwnableField(position, name, purchasePrice, trespassingFee) {}
        Station(const Station &secStation);
        Station& operator=(const Station &secStation);
        ~Station() = default;
};