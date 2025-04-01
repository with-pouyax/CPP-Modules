#include "Zombie.hpp"
// return type of newZombie is Zombie* (pointer to Zombie) which means that the function will return an address of a Zombie object
// what is the benefit of using a pointer here?
// the benefit of using a pointer here is that we can return the address of the Zombie object that we create in the function
Zombie* newZombie(std::string name) {
    try {
        // If name is empty, provide a default name
        if (name.empty()) {
            name = "Unnamed Zombie";
        }
        return new Zombie(name);
    } catch (const std::bad_alloc& error) { //we refer to the error which is an object of type std::bad_alloc
        std::cerr << "Memory allocation failed: " << error.what() << std::endl; //what() is a member function of the std::bad_alloc class that returns a string describing the error
        return NULL;
    }
} 