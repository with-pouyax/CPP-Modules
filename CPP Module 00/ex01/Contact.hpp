#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <string>

class Contact {
    private:
        std::string _firstName;

    public:
        Contact();
        ~Contact();

        //setter
        void setFirstName(const std::string& firstName);
};

#endif