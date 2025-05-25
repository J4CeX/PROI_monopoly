#pragma once
#include "EventField.hpp"

namespace Fields {
    class CommunityChestField: public EventField {
        public:
            CommunityChestField() = default;
            CommunityChestField(int position): EventField(position) {}
            TYPE getInfo() const override { return TYPE::COMMUNITYCHESTFIELD; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<CommunityChestField>(*this); }
            ~CommunityChestField() = default;
    };
}