#include "Field/OwnableField.hpp"
#include "Logger.hpp"

namespace Fields {
    size_t OwnableField::getOwner() const {
        if (!owned) {
            LOG(1, "Attempt at reading owner of an unowned OwnableField");

            return 0;
        }
        return owner;
    }

    int OwnableField::setOwner(const size_t newOwner) {
        if (owned == false) {
            owner = newOwner;
            owned = true;

            LOG(0, "OwnableField owner set");

            return purchasePrice;
        }

        LOG(2, "Attempted to change the owner of an owned OwnableField");
        return 0;
    }

    int OwnableField::removeOwner() {
        if (owned == true) {
            owner = 0;
            owned = false;

            LOG(0, "OwnableField owner removed");

            return purchasePrice;
        }

        LOG(2, "Attempted to remove the owner of an unowned OwnableField");
        return 0;
    }

    int OwnableField::mortgage() {
        if (mortgaged == false && owned == true) {
            mortgaged = true;

            LOG(0, "OwnableField mortgaged");

            return purchasePrice / 2;
        }

        LOG(2, "Attempted to mortgage an arleady mortgaged or unowned OwnableField");

        return 0;
    }

    int OwnableField::unmortgage() {
        if (mortgaged == true && owned == true) {
            mortgaged = false;
            return purchasePrice / 2;
        }

        LOG(2, "Attempted to unmortgage an OwnableField that is not mortgaged or unowned");

        return 0;
    }
}