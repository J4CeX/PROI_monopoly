#pragma once
#include "OwnableField.hpp"

namespace Fields {
    enum class Color {
        Brown,
        Lightblue,
        Pink,
        Orange,
        Red,
        Yellow,
        Green,
        Darkblue,
    };

    class Street: public OwnableField {
        private:
            static const int Capacity = 6;
            int housePrice;
            int houseCount;
            int housesRent[Capacity];
            Color color;
        public:
            Street(int position, const std::string &name, int purchasePrice, int trespassingFee,
                Color streetColor, int firstHouseRent, int secondHouseRent, int thirdHouseRent,
                int fourthHouseRent, int fifthHouseRent);
            int getHousePrice() const { return housePrice; }
            int getHouseCount() const { return houseCount; }
            TYPE getInfo() const override { return TYPE::STREET; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Street>(*this); }
            int purchaseHouse();
            int sellHouse();
            ~Street() = default;
    };
}