#include "Contact.hpp"

// Constructor and destructor
Contact::Contact() : firstName("") {}
Contact::~Contact() {}

// setters methods
void Contact::setFirstName(const std::string& firstName) { this->firstName = firstName; }

// This does the same thing as: void Contact::setContact(const Contact& contact) { *this = contact; }
// But written in a more explicit way
void Contact::setContact(const Contact& contact) 
{
    this->firstName = contact.firstName;
}
