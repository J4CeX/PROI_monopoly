#pragma once
#include "OwnableField.hpp"
#include "Logger.hpp"

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
            int housePrice = 50;
            int houseCount = 0;
            int housesRent[Capacity];
            Color color;
        public:
            Street() = default;
            Street(int position, int purchasePrice, int trespassingFee,
                int firstHouseRent, int secondHouseRent, int thirdHouseRent,
                int fourthHouseRent, int fifthHouseRent, const std::string &name, Color streetColor);
            int getHousePrice() const { return housePrice; }
            int getHouseCount() const { return houseCount; }
            TYPE getInfo() const override { return TYPE::STREET; }
            Color getColor() const { return color; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Street>(*this); }
            int purchaseHouse();
            int sellHouse();
            std::string save() const override;
            std::istream& loadSave(std::istream& is) override;
            ~Street() = default;
            friend std::istream& operator>>(std::istream& is, Street& street) {
                std::string curColor;
                is >> street.position >> street.purchasePrice >> street.housesRent[0]
                    >> street.housesRent[1] >> street.housesRent[2] >> street.housesRent[3]
                    >> street.housesRent[4] >> street.housesRent[5] >> curColor >> std::ws;
                street.trespassingFee = street.housesRent[0];
                if (curColor == "Brown") {
                    street.color = Color::Brown;
                }
                else if (curColor == "Lightblue") {
                    street.color = Color::Lightblue;
                }
                else if (curColor == "Pink") {
                    street.color = Color::Pink;
                }
                else if (curColor == "Orange") {
                    street.color = Color::Orange;
                }
                else if (curColor == "Red") {
                    street.color = Color::Red;
                }
                else if (curColor == "Yellow") {
                    street.color = Color::Yellow;
                }
                else if (curColor == "Green") {
                    street.color = Color::Green;
                }
                else if (curColor == "Darkblue") {
                    street.color = Color::Darkblue;
                }
                else {
                    LOG(2, "While deserializing Street Field: wrong color type for street!");
                }
                std::string curName;
                std::getline(is, curName);
                street.name = curName;
                return is;
            }
    };
}