#include "Field/OwnableField.hpp"

namespace Fields {
    size_t OwnableField::getOwner() const {
        if (!owned) {
            return 0;
        }
        return owner;
    }

    int OwnableField::setOwner(const size_t newOwner) {
        // if (owned == false) {
            owner = newOwner;
            owned = true;
            
            return purchasePrice;
        // }
        
        // return 0;
    }

    int OwnableField::removeOwner() {
        if (owned == true) {
            owner = 0;
            owned = false;
            return purchasePrice;
        }
        return 0;
    }

    int OwnableField::mortgage() {
        if (mortgaged == false && owned == true) {
            mortgaged = true;
            return purchasePrice / 2;
        }
        return 0;
    }

    int OwnableField::unmortgage() {
        if (mortgaged == true && owned == true) {
            mortgaged = false;
            return purchasePrice / 2;
        }
        return 0;
    }

    std::string OwnableField::save() const {
        std::stringstream ss;
        ss << position << " " << owner << " " << (owned? 1: 0) << " " << (mortgaged? 1: 0);
        return ss.str();
    }

    std::istream& OwnableField::loadSave(std::istream& is) {
        is >> owner >> owned >> mortgaged;
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const OwnableField& ownableField) {
        os << ownableField.save();
        return os;
    }
}