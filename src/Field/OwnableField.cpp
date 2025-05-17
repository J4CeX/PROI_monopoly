#include "OwnableField.hpp"

namespace Fields {
    Player& OwnableField::getPlayer() const {
        if (!owned) {
            throw std::runtime_error("Ownable field has not owner!");
        }
        return *owner;
    }

    void OwnableField::setOwner(const std::unique_ptr<Player> newOwner) {
        if (owned == false) {
            owner = std::make_unique<Player>(*newOwner);
            owned = true;
        }
    }

    void OwnableField::removeOwner() {
        if (owned == true) {
            owner = nullptr;
            owned = false;
        }
    }

    void OwnableField::mortgage() {
        if (mortgaged == false && owned == true) {
            // dodaj do salda połowe wartości pola
            mortgaged = true;
        }
    }

    void OwnableField::unmortgage() {
        if (mortgaged == true && owned == true) {
            // odejmij od salda połowe wartości pola
            mortgaged = false;
        }
    }
}