#pragma once
#include "OwnableField.hpp"

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
        Street(const Street &secStreet);
        int getHousePrice() const { return housePrice; }
        int getHouseCount() const { return houseCount; }
        int getRent() const { return trespassingFee; }
        void purchaseHouse();
        void sellHouse();
        Street& operator=(const Street &secStreet);
        ~Street() = default;
};