#pragma once
#include "Field.hpp"
#include "Player.hpp"
#include <memory>

class OwnableField: public Field {
    protected:
        std::string name;
        int purchasePrice;
        int trespassingFee;
        bool owned;
        bool mortgage;
        std::unique_ptr<Player> owner;
    public:
        OwnableField(int position, const std::string &name, int purchasePrice, int trespassingFee)
            : Field(position), name(name), purchasePrice(purchasePrice), trespassingFee(trespassingFee),
            owned(false), mortgage(false), owner(nullptr) {}
        OwnableField(const OwnableField &secOwnableField);
        std::string getName() const { return name; }
        int getPurchasePrice() const { return purchasePrice; }
        int getTrespassingFee() const { return trespassingFee; }
        bool isOwned() const { return owned; }
        bool isMortgage() const { return mortgage; }
        Player& getPlayer() const;
        void setPlayer(const std::unique_ptr<Player> newOwner);
        OwnableField& operator=(const OwnableField &secOwnableField);
        virtual ~OwnableField() = default;
};