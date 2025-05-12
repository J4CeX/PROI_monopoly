#pragma once
#include <iostream>

class Field {
    protected:
        int position;
    public:
        Field(int position): position(position) {}
        Field(const Field &secField);
        int getPosition() { return position; }
        Field& operator=(const Field &secField);
        virtual ~Field() {};
};