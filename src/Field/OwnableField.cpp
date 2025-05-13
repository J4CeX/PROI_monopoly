#include "OwnableField.hpp"

namespace Fields {
    Player& OwnableField::getPlayer() const {
        if (!isOwned()) {
            throw std::runtime_error("Ownable field has not owner!");
        }
        return *owner;
    }

    void OwnableField::setPlayer(const std::unique_ptr<Player> newOwner) {
        owner = std::make_unique<Player>(*newOwner);
        owned = true;
    }

    void OwnableField::mortgage() {
        if (mortgaged == false) {
            // dodaj do salda połowe wartości pola
            mortgaged = true;
        }
    }

    void OwnableField::unmortgage() {
        if (mortgaged == true) {
            // odejmij od salda połowe wartości pola
            mortgaged = false;
        }
    }
}