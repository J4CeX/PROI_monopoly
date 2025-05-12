#include "OwnableField.hpp"

Player& OwnableField::getPlayer() const {
    if (!isOwned()) {
        throw std::runtime_error("Ownable field has not owner!");
    }
    return *owner;
}

void OwnableField::setPlayer(const std::unique_ptr<Player> newOwner) {

}