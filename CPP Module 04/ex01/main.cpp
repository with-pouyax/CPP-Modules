#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
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

void cleanupArray(Animal** animals, int currentSize) {
    for (int i = 0; i < currentSize; i++) {
        delete animals[i];
        animals[i] = NULL;
    }
}

int main() {
    try {
        // Test 1: Basic Animal Array Test
        printTitle("Basic Animal Array Test");
        {
            const int arraySize = 4;
            Animal* animals[arraySize] = {NULL}; // we make an array of pointers to Animal objects and set all of them to NULL
            int currentSize = 0;                 // we keep track of the current size of the array

            try {
                // Create half dogs and half cats
                std::cout << GREEN << "Creating animals array..." << RESET << std::endl;
                for (int i = 0; i < arraySize; i++) {
                    if (i < arraySize / 2) { // if we still did not reach the half of the array
                        animals[i] = new Dog();
                    } else {                 // if we reached the half of the array
                        animals[i] = new Cat();
                    }
                    currentSize++;
                    std::cout << "Animal " << i << " type: " << animals[i]->getType() << std::endl;
                }

                // Make sounds of all animals
                std::cout << GREEN << "\nMaking all animals sound off:" << RESET << std::endl;
                for (int i = 0; i < arraySize; i++) {
                    std::cout << "Animal " << i << " (" << animals[i]->getType() << "): ";
                    animals[i]->makeSound();
                }

                // Clean up the array
                std::cout << GREEN << "\nCleaning up array..." << RESET << std::endl;
                cleanupArray(animals, arraySize);
            }
            catch (const std::bad_alloc& e) {
                std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
                
                // we could also call cleanupArray(animals, arraySize) here but like this is more professional practice
                cleanupArray(animals, currentSize);
                throw; // we gonna catch this in the outer catch block in main
            }
        }

        // Test 2: Deep Copy Test
        printTitle("Deep Copy Test");
        {
            Dog* originalDog = NULL;
            Dog* copyDog = NULL;

            try {
                std::cout << GREEN << "Testing Dog deep copy:" << RESET << std::endl;
                originalDog = new Dog();                              
                originalDog->getBrain()->setIdea(0, "I love bones!"); 
                
                std::cout << "\nCreating a copy of the dog..." << std::endl;
                copyDog = new Dog(*originalDog); // we are making a deep copy of the originalDog object using Dog class copy constructor                
                
                std::cout << "\nOriginal dog's first idea: " << originalDog->getBrain()->getIdea(0) << std::endl;
                std::cout << "Copy dog's first idea: " << copyDog->getBrain()->getIdea(0) << std::endl;
                
                std::cout << "\nChanging original dog's idea..." << std::endl;
                originalDog->getBrain()->setIdea(0, "I love playing fetch!");
                
                std::cout << "Original dog's first idea: " << originalDog->getBrain()->getIdea(0) << std::endl;
                std::cout << "Copy dog's first idea: " << copyDog->getBrain()->getIdea(0) << std::endl;

                // Clean up inside try block
                delete originalDog;
                originalDog = NULL;
                delete copyDog;
                copyDog = NULL;
            }
            // if any of new operations failed, we catch the exception and clean up the memory
            catch (const std::bad_alloc& e) {
                std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
                delete originalDog;  // Safe to delete NULL pointers
                delete copyDog;
                throw;
            }
        }

        // Test 3: Assignment Operator Test
        printTitle("Assignment Operator Test");
        {
            try {
                std::cout << GREEN << "Testing Cat assignment operator:" << RESET << std::endl;
                Cat cat1;                                    // we create a new Cat object
                cat1.getBrain()->setIdea(0, "I love fish!"); // we set the first idea of the cat's brain to "I love fish!"
                
                Cat cat2;                                    // we create a new Cat object
                std::cout << "Cat2's first idea before assignment: " << cat2.getBrain()->getIdea(0) << std::endl;
                cat2 = cat1;                                 // we assign the cat1 object to the cat2 object using the assignment operator
                
                std::cout << "\nCat1's first idea: " << cat1.getBrain()->getIdea(0) << std::endl;
                std::cout << "Cat2's first idea after assignment: " << cat2.getBrain()->getIdea(0) << std::endl;
                
                std::cout << "\nChanging Cat1's idea..." << std::endl;
                cat1.getBrain()->setIdea(0, "I love sleeping!");
                
                std::cout << "Cat1's first idea: " << cat1.getBrain()->getIdea(0) << std::endl;
                std::cout << "Cat2's first idea: " << cat2.getBrain()->getIdea(0) << std::endl;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
                throw;
            }
        }

        // Test 4: Subject's Required Test
        printTitle("Subject's Required Test");
        {
            const Animal* j = NULL;
            const Animal* i = NULL;

            try {
                j = new Dog();
                i = new Cat();
                delete j;
                delete i;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
                delete j;
                delete i;
                throw;
            }
        }

        // Test 5: Brain Ideas Array Test
        printTitle("Brain Ideas Array Test");
        {
            Dog* dog = NULL;
            try {
                dog = new Dog();
                Brain* brain = dog->getBrain();

                // Fill first 5 ideas
                brain->setIdea(0, "I want to chase squirrels");
                brain->setIdea(1, "Must protect the house");
                brain->setIdea(2, "Time for a walk?");
                brain->setIdea(3, "Food food food!");
                brain->setIdea(4, "I love my human");

                // Skip one slot (index 5)

                // Fill next 5 ideas
                brain->setIdea(6, "Ball is life");
                brain->setIdea(7, "Need to dig a hole");
                brain->setIdea(8, "Mailman is suspicious");
                brain->setIdea(9, "Belly rubs are the best");
                brain->setIdea(10, "Must catch my tail");

                // Print all ideas including the skipped one
                std::cout << GREEN << "Printing all ideas:" << RESET << std::endl;
                for (int i = 0; i <= 100; i++) 
                {
                    std::string idea = brain->getIdea(i);
                    std::cout << "Idea " << i << ": " << idea << std::endl;
                }

                // Proper cleanup
                delete dog;  // This will also delete the Brain since Dog's destructor handles it
                dog = NULL;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << RED << "Memory allocation failed: " << e.what() << RESET << std::endl;
                delete dog;  // Safe to delete NULL pointer
                throw;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << RED << "Program terminated due to exception: " << e.what() << RESET << std::endl;
        return 1;
    }

    return 0;
} 