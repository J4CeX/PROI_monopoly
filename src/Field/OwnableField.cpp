#include "Field/OwnableField.hpp"
#include "Logger.hpp"

namespace Fields {
    size_t OwnableField::getOwner() const {
        if (!owned) {
            LOGI(1, "Attempt at reading owner of an unowned OwnableField", position);

            return 0;
        }
        return owner;
    }

    int OwnableField::setOwner(const size_t newOwner) {
        if (owned == false) {
            owner = newOwner;
            owned = true;

            LOGII(0, "OwnableField owner set", position, owner);

            return purchasePrice;
        }

        LOGI(2, "Attempted to change the owner of an owned OwnableField", position);
        return 0;
    }

    int OwnableField::removeOwner() {
        if (owned == true) {
            owner = 0;
            owned = false;

            LOGI(0, "OwnableField owner removed", position);

            return purchasePrice;
        }

        LOGI(2, "Attempted to remove the owner of an unowned OwnableField", position);
        return 0;
    }

    int OwnableField::mortgage() {
        if (mortgaged == false && owned == true) {
            mortgaged = true;

            LOGI(0, "OwnableField mortgaged", position);

            return purchasePrice / 2;
        }

        LOGI(2, "Attempted to mortgage an arleady mortgaged or unowned OwnableField", position);

        return 0;
    }

    int OwnableField::unmortgage() {
        if (mortgaged == true && owned == true) {
            mortgaged = false;
            return purchasePrice / 2;
        }

        LOGI(2, "Attempted to unmortgage an OwnableField that is not mortgaged or unowned", position);

        return 0;
    }
}