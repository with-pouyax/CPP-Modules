#ifndef CONTACT_HPP
#define CONTACT_HPP
#include <string>

class Contact {
    private:
        std::string firstName;
        
    public:
        Contact();
        ~Contact();

        // setters methods
        void setFirstName(const std::string& firstName);
        
        //set contact
        void setContact(const Contact& contact);
        
};

#endif


