#pragma once
#include "Field.hpp"

class OwnableField: public Field {
    public:
        OwnableField() = default;
        OwnableField(const OwnableField &secOwnableField);
        OwnableField operator=(const OwnableField &secOwnableField);
        virtual ~OwnableField() {};
};