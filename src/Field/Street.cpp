#include "Street.hpp"

namespace Fields {
    Street::Street(int position, const std::string &name, int purchasePrice, int housePrice,
        int trespassingFee, int firstHouseRent, int secondHouseRent, int thirdHouseRent,
        int fourthHouseRent, int fifthHouseRent)
        : OwnableField(position, name, purchasePrice, trespassingFee),
        housePrice(housePrice), houseCount(0) {
            housesRent[0] = trespassingFee;
            housesRent[1] = firstHouseRent;
            housesRent[2] = secondHouseRent;
            housesRent[3] = thirdHouseRent;
            housesRent[4] = fourthHouseRent;
            housesRent[5] = fifthHouseRent;
        }

    void Street::purchaseHouse() {
        // wymagana klasa player
        if (houseCount < Capacity) {
            trespassingFee = housesRent[++houseCount];
        }
        else {
            std::cerr << "purchaseHouse out of range error!" << std::endl;
        }
        // może lepiej zwykły cout?
    }

    void Street::sellHouse() {
        // wymagana klasa player
        if (houseCount > 0) {
            trespassingFee = housesRent[--houseCount];
        }
        else {
            std::cerr << "sellHouse out of range error!" << std::endl;
        }
        // może lepiej zwykły cout?
    }
}