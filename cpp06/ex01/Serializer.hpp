#ifndef SERIALIZED_HPP
#define SERIALIZED_HPP

#include <stdint.h>
#include <string>
#include "Data.hpp"

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer& Other);
        Serializer& operator=(const Serializer& Other);
        ~Serializer();
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif