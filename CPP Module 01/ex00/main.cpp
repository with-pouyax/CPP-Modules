#include "Zombie.hpp"

int main() {
    // HEAP ALLOCATION EXAMPLES
    std::cout << "--- Heap Allocation Examples ---" << std::endl;
    
    // Create a heap zombie that exists beyond the scope
    Zombie* heapZombie1 = newZombie("Heap_Zombie1");
    if (heapZombie1 == NULL) {
        std::cout << "Failed to create heap zombie" << std::endl;
        return 1;
    }
    
    // Create another heap zombie
    Zombie* heapZombie2 = newZombie("Heap_Zombie2");
    if (heapZombie2 == NULL) {
        std::cout << "Failed to create heap zombie" << std::endl;
        delete heapZombie1;
        return 1;
    }
    
    // We can use these zombies multiple times throughout the program
    heapZombie1->announce();
    heapZombie2->announce();
    
    // We can store heap zombies in containers
    Zombie* zombieArray[2] = {heapZombie1, heapZombie2};
    std::cout << "Using zombies from array:" << std::endl;
    zombieArray[0]->announce();
    zombieArray[1]->announce();
    
    // We control when to delete them
    delete heapZombie1; // First zombie is now destroyed
    std::cout << "First heap zombie deleted" << std::endl;
    
    // Second zombie still exists and can be used
    heapZombie2->announce();
    delete heapZombie2; // Finally delete the second zombie
    
    // STACK ALLOCATION EXAMPLES
    std::cout << "\n--- Stack Allocation Examples ---" << std::endl;
    
    // randomChump creates a zombie on the stack that is automatically destroyed
    std::cout << "Calling randomChump (zombie is created and destroyed within the function):" << std::endl;
    randomChump("Stack_Zombie1");
    
    // The zombie from randomChump no longer exists here
    std::cout << "After randomChump returns, its zombie no longer exists" << std::endl;
    
    // Call randomChump again to create another temporary zombie
    std::cout << "Calling randomChump again:" << std::endl;
    randomChump("Stack_Zombie2");
    
    std::cout << "Program ending" << std::endl;
    return 0;
} 
