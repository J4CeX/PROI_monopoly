#pragma once
#include <iostream>

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
            Field(int position): position(position) {}
            int getPosition() { return position; }
            virtual TYPE getInfo() const = 0;
            virtual ~Field() = default;
    };
}