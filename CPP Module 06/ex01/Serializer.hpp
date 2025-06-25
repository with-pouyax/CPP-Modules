#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer {
private:

    Serializer();
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);   //uintptr_t is an unsigned integer type that is used to store a pointer
    static Data* deserialize(uintptr_t raw);
};

#endif // SERIALIZER_HPP 