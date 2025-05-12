#pragma once
#include <iostream>

class Field {
    protected:
        std::string name;
    public:
        Field() = default;
        Field(const Field &secField);
        Field operator=(const Field &secField);
        virtual ~Field() {};
};