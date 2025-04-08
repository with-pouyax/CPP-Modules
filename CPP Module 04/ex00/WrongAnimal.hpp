#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal {
protected:
    std::string type;

public:
    // Orthodox Canonical Form
    WrongAnimal();
    WrongAnimal(const WrongAnimal& other);
    ~WrongAnimal();
    WrongAnimal& operator=(const WrongAnimal& other);

    // Member functions
    void makeSound() const;
    std::string getType() const;
};

#endif // WRONGANIMAL_HPP 