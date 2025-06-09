#include "Serializer.hpp"

//----------------OCF----------------
Serializer::Serializer() {} // Default constructor
Serializer::Serializer(const Serializer& other) { (void)other; } // Copy constructor
Serializer& Serializer::operator=(const Serializer& other) { (void)other; return *this; } // Copy assignment operator
Serializer::~Serializer() {} // Destructor
//-----------------------------------

//here we convert the pointer to an uintptr_t
uintptr_t Serializer::serialize(Data* ptr) {
    if (!ptr)
        return 0;
    //by reinterpret_cast we can convert the anything to anything we want
    //but we need to be careful with the type we are converting to because it can cause undefined behavior
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    if (raw == 0) //if the raw is 0 means that the pointer is NULL means that the pointer is not valid
        return NULL;
    //here we convert the uintptr_t to a Data* (pointer of type Data)
    return reinterpret_cast<Data*>(raw);
} 