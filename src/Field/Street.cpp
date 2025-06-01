#include "Field/Street.hpp"

namespace Fields {
    Street::Street(int position, int purchasePrice, int trespassingFee,
        int firstHouseRent, int secondHouseRent, int thirdHouseRent,
        int fourthHouseRent, int fifthHouseRent, const std::string &name, Color streetColor)
        : OwnableField(position, name, purchasePrice, trespassingFee),
            houseCount(0), color(streetColor) {
            housesRent[0] = trespassingFee;
            housesRent[1] = firstHouseRent;
            housesRent[2] = secondHouseRent;
            housesRent[3] = thirdHouseRent;
            housesRent[4] = fourthHouseRent;
            housesRent[5] = fifthHouseRent;
        }

    int Street::purchaseHouse() {
        if (houseCount < Capacity - 1) {
            trespassingFee = housesRent[++houseCount];
            return housePrice;
        }
        else {
            std::cerr << "purchaseHouse out of range error!" << std::endl;
            return 0;
        }
    }

    int Street::sellHouse() {
        if (houseCount > 0) {
            trespassingFee = housesRent[--houseCount];
            return housePrice;
        }
        else {
            std::cerr << "sellHouse out of range error!" << std::endl;
            return 0;
        }
    }
}