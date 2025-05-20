#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Street: public OwnableField {
        private:
            static const int Capacity = 6;
            int housePrice;
            int houseCount;
            int housesRent[Capacity];
        public:
            Street(int position, const std::string &name, int purchasePrice, int housePrice,
                int trespassingFee, int firstHouseRent, int secondHouseRent, int thirdHouseRent,
                int fourthHouseRent, int fifthHouseRent);
            int getHousePrice() const { return housePrice; }
            int getHouseCount() const { return houseCount; }
            TYPE getInfo() const override { return TYPE::STREET; }
            int purchaseHouse();
            int sellHouse();
            ~Street() = default;
    };
}