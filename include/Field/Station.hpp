#pragma once
#include "OwnableField.hpp"

namespace Fields {
    class Station: public OwnableField {
        public:
            Station(int position, const std::string &name)
            : OwnableField(position, name, 200, 50) {}
            TYPE getInfo() const override { return TYPE::STATION; }
            std::unique_ptr<Field> clone() const override { return std::make_unique<Station>(*this); }
            ~Station() = default;
            friend std::istream& operator>>(std::istream& is, Station& station) {
                is >> station.position >> std::skipws;
                std::getline(is, station.name);
                return is;
            }
    };
}