#pragma once
#include "EventField.hpp"

class CommunityChestField: public EventField {
    public:
        CommunityChestField(int position): EventField(position) {}
        CommunityChestField(const CommunityChestField &secCommunityChestField);
        CommunityChestField& operator=(const CommunityChestField &secCommunityChestField);
        ~CommunityChestField() = default;
};