#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Station: public OwnableField {
        public:
            Station(int position, const std::string &name)
            : OwnableField(position, name, 200, 50) {}
            TYPE getInfo() const override { return TYPE::STATION; }
            ~Station() = default;
    };
}