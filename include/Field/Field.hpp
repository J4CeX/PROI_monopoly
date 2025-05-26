#pragma once
#include <iostream>
#include <memory>

namespace Fields {
    enum class TYPE {
        STREET,
        UTILITY,
        STATION,
        CHANCEFIELD,
        COMMUNITYCHESTFIELD,
        JAIL,
        GOTOJAIL,
        PARKING,
        STARTFIELD,
        INCOMETAX,
        LUXURYTAX
    };

    class Field {
        protected:
            int position;
        public:
            Field() = default;
            Field(int position): position(position) {}
            int getPosition() { return position; }
            virtual TYPE getInfo() const = 0;
            virtual std::unique_ptr<Field> clone() const = 0;
            virtual ~Field() = default;
    };
}