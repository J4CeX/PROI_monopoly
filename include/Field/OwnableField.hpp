#pragma once
#include "Field.hpp"
#include "Player.hpp"
#include <memory>

namespace Fields {
    class OwnableField: public Field {
        protected:
            std::string name;
            int purchasePrice;
            int trespassingFee;
            bool owned;
            bool mortgaged;
            size_t owner;
        public:
            OwnableField(int position, const std::string &name, int purchasePrice, int trespassingFee)
                : Field(position), name(name), purchasePrice(purchasePrice), trespassingFee(trespassingFee),
                owned(false), mortgaged(false), owner(NULL) {}
            std::string getName() const { return name; }
            int getPurchasePrice() const { return purchasePrice; }
            bool isOwned() const { return owned; }
            bool isMortgaged() const { return mortgaged; }
            virtual TYPE getInfo() const = 0;
            size_t getOwner() const;
            int getRent() const { return trespassingFee; }
            int mortgage();
            int unmortgage();
            int setOwner(const size_t newOwner);
            int removeOwner();
            virtual ~OwnableField() = default;
    };
}