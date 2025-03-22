#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <string>

class Contact {
    private:
        std::string _firstName;
        std::string _lastName;
        std::string _nickName;
        std::string _phoneNumber;
        std::string _darkestSecret;


    public:
        Contact();
        ~Contact();

        //setter
        void setContact(
            const std::string& firstName,
            const std::string& lastName,
            const std::string& nickName,
            const std::string& phoneNumber,
            const std::string& darkestSecret);
            
        //display methods
        void displaySummary(int index) const;
        void displayDetails() const;
        
        //helper
        std::string truncateTo10(const std::string& str) const;
        bool isEmpty() const;
};

#endif