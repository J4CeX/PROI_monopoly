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
            OwnableField() = default;
            OwnableField(int position, const std::string &name, int purchasePrice, int trespassingFee)
                : Field(position), name(name), purchasePrice(purchasePrice), trespassingFee(trespassingFee),
                owned(false), mortgaged(false), owner(0) {}
            std::string getName() const { return name; }
            int getPurchasePrice() const { return purchasePrice; }
            virtual TYPE getInfo() const = 0;
            size_t getOwner() const;
            virtual int getRent() const { return trespassingFee; }
            bool isOwned() const { return owned; }
            bool isMortgaged() const { return mortgaged; }
            int mortgage();
            int unmortgage();
            int setOwner(const size_t newOwner);
            int removeOwner();
            void setTrespassingFee(int newRent) { trespassingFee = newRent; }
            virtual ~OwnableField() = default;
    };
}