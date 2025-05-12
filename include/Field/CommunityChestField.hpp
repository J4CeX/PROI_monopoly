#pragma once
#include "EventField.hpp"

class CommunityChestField: public EventField {
    public:
        CommunityChestField(int position): EventField(position) {}
        CommunityChestField(const CommunityChestField &secCommunityChestField);
        TYPE getInfo() const override { return TYPE::COMMUNITYCHESTFIELD; }
        CommunityChestField& operator=(const CommunityChestField &secCommunityChestField);
        ~CommunityChestField() = default;
};