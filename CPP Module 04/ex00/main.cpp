#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void testCorrectImplementation() {
    std::cout << "\n=== Testing Correct Implementation ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;
}

void testWrongImplementation() {
    std::cout << "\n=== Testing Wrong Implementation ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << wrongCat->getType() << " " << std::endl;
    wrongCat->makeSound(); //will output the WrongAnimal sound!
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;
}

int main() {
    testCorrectImplementation();
    testWrongImplementation();
    return 0;
} 