#pragma once
#include "EventField.hpp"

namespace Fields {
    class CommunityChestField: public EventField {
        public:
            CommunityChestField(int position): EventField(position) {}
            TYPE getInfo() const override { return TYPE::COMMUNITYCHESTFIELD; }
            ~CommunityChestField() = default;
    };
}