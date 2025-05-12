#pragma once
#include "Field.hpp"
#include "Player.hpp"
#include <memory>

class OwnableField: public Field {
    protected:
        std::string name;
        int price;
        int trespassingFee;
        bool owned;
        bool mortgage;
        std::unique_ptr<Player> owner;
    public:
        OwnableField(int position, std::string name, int price, int trespassingFee)
            : Field(position), name(name), price(price), trespassingFee(trespassingFee),
            owned(false), mortgage(false), owner(nullptr) {}
        OwnableField(const OwnableField &secOwnableField);
        std::string getName() const { return name; }
        int getPrice() const { return price; }
        int getTrespassingFee() const { return trespassingFee; }
        bool isOwned() const { return owned; }
        bool isMortgage() const { return mortgage; }
        Player& getPlayer() const;
        void setPlayer(const std::unique_ptr<Player> newOwner);
        OwnableField& operator=(const OwnableField &secOwnableField);
        virtual ~OwnableField() {};
};