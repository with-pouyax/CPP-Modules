#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
    private:
        Contact _contact[8];
        int _index;

    public:
        PhoneBook();
        ~PhoneBook();

        //setter
        void saveContact(const Contact& newContact);
};

#endif