#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

void printTitle(const std::string& title) {
    std::cout << YELLOW << "\n================================================" << RESET << std::endl;
    std::cout << YELLOW << "=== " << title << " ===" << RESET << std::endl;
    std::cout << YELLOW << "================================================" << RESET << std::endl;
}

int main() {
    
    // Testing Copy Construction and Assignment
    printTitle("Copy Construction and Assignment Tests");
    {
        //----------------Animal----------------
            std::cout << GREEN << "Testing Animal:" << RESET << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Animal originalAnimal;
            std::cout << "________________________________________________" << std::endl;

            std::cout << GREEN << "->" << RESET << std::endl;
            originalAnimal.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Copy Animal----------------
            std::cout << "Creating copy of Animal..." << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Animal copyAnimal(originalAnimal);
            std::cout << "________________________________________________" << std::endl;

            std::cout << GREEN << "->" << RESET << std::endl;
            copyAnimal.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Assignment Operator----------------
            std::cout << GREEN << "\nTesting assignment operator:" << RESET << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Animal anotherAnimal;
            std::cout << "________________________________________________" << std::endl;

            anotherAnimal = originalAnimal;
            std::cout << "________________________________________________" << std::endl;

            std::cout << GREEN << "->" << RESET << std::endl;
            anotherAnimal.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Dog----------------
            std::cout << GREEN << "\nTesting Dog:" << RESET << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Dog originalDog;
            std::cout << "________________________________________________" << std::endl;
            
            std::cout << GREEN << "->" << RESET << std::endl;
            originalDog.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Copy Dog----------------
            std::cout << "Creating copy of Dog..." << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Dog copyDog(originalDog);
            std::cout << "________________________________________________" << std::endl;
            
            std::cout << GREEN << "->" << RESET << std::endl;
            copyDog.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Assignment Operator----------------
            std::cout << GREEN << "\nTesting assignment operator:" << RESET << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Dog anotherDog;
            std::cout << "________________________________________________" << std::endl;
            
            anotherDog = originalDog;
            std::cout << "________________________________________________" << std::endl;

            std::cout << GREEN << "->" << RESET << std::endl;
            anotherDog.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Cat----------------
            std::cout << GREEN << "\nTesting Cat:" << RESET << std::endl;
            
            //----------------Original Cat----------------
            std::cout << "________________________________________________" << std::endl;
            Cat originalCat;
            std::cout << "________________________________________________" << std::endl;
            
            std::cout << GREEN << "->" << RESET << std::endl;
            originalCat.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;
            
            //----------------Copy Cat----------------
            std::cout << "Creating copy of Cat..." << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Cat copyCat(originalCat);
            std::cout << "________________________________________________" << std::endl;
            
            std::cout << GREEN << "->" << RESET << std::endl;
            copyCat.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            //----------------Assignment Operator----------------
            std::cout << GREEN << "\nTesting assignment operator:" << RESET << std::endl;
            std::cout << "________________________________________________" << std::endl;
            Cat anotherCat;
            std::cout << "________________________________________________" << std::endl;

            anotherCat = originalCat;
            std::cout << "________________________________________________" << std::endl;

            std::cout << GREEN << "->" << RESET << std::endl;
            anotherCat.makeSound();
            std::cout << GREEN << "->" << RESET << std::endl;

            std::cout << "________________________________________________" << std::endl;
            //----------------Destructor----------------
            std::cout << GREEN << "Destructor:" << RESET << std::endl;
    }

    // Subject's required tests
    printTitle("Subject's Required Tests");
    {
        const Animal* baseAnimal = NULL;
        const Animal* dogInstance = NULL;
        const Animal* catInstance = NULL;

        try {
            baseAnimal = new Animal();
            dogInstance = new Dog();
            catInstance = new Cat();

            std::cout << dogInstance->getType() << " " << std::endl;
            std::cout << catInstance->getType() << " " << std::endl;
            catInstance->makeSound();
            dogInstance->makeSound();
            baseAnimal->makeSound();

            delete baseAnimal;
            baseAnimal = NULL;
            delete dogInstance;
            dogInstance = NULL;
            delete catInstance;
            catInstance = NULL;
        }
        catch (const std::bad_alloc& e) {
            std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
            delete baseAnimal;
            baseAnimal = NULL;
            delete dogInstance;
            dogInstance = NULL;
            delete catInstance;
            catInstance = NULL;
        }
    }

    // Testing Wrong Animal Implementation
    printTitle("Wrong Animal Implementation Tests");
    {
        const WrongAnimal* wrongMeta = NULL;
        const WrongAnimal* wrongCat = NULL;

        try {
            wrongMeta = new WrongAnimal();
            wrongCat = new WrongCat();

            std::cout << wrongCat->getType() << " " << std::endl;
            wrongCat->makeSound();
            wrongMeta->makeSound();

            delete wrongMeta;
            wrongMeta = NULL;
            delete wrongCat;
            wrongCat = NULL;
        }
        catch (const std::bad_alloc& e) {
            std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
            delete wrongMeta;
            wrongMeta = NULL;
            delete wrongCat;
            wrongCat = NULL;
        }
    }

    // Testing Animal Array
    printTitle("Animal Array Tests");
    {
        const int arraySize = 4;
        Animal* animals[arraySize] = {NULL};

        try {
            std::cout << "Creating array of animals..." << std::endl;
            
            // Fill array with alternating Dogs and Cats
            for (int i = 0; i < arraySize; i++) {
                if (i % 2 == 0) {
                    animals[i] = new Dog();
                } else {
                    animals[i] = new Cat();
                }
            }

            // Make them all sound off
            std::cout << "\nMaking all animals sound off:" << std::endl;
            for (int i = 0; i < arraySize; i++) {
                std::cout << "Animal " << i + 1 << " (" << animals[i]->getType() << "): "; // we need to use -> to access the type of the animal because animals is a pointer to an Animal object
                animals[i]->makeSound();
            }

            // Clean up
            std::cout << "\nCleaning up array..." << std::endl;
            for (int i = 0; i < arraySize; i++) {
                delete animals[i];
                animals[i] = NULL;
            }
        }
        catch (const std::bad_alloc& e) {
            std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
            // Clean up any successfully allocated animals
            for (int i = 0; i < arraySize; i++) {
                delete animals[i];
                animals[i] = NULL;
            }
        }
    }

    return 0;
} 